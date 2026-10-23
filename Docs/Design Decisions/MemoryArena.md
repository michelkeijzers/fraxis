# MEMORY ARENA

## Goal

Preventing memory defragmentation when switch applications.

## Conditions

- Only one application running simultaneously.
- Menu is application 0.

## Alternatives

### Alternative 1: Fixed Application Arena

Use a so called Fixed Application Arena.
using a so called `placement new` memory from one application can be reused by the next active application.

```C++
constexpr size_t APPLICATION_ARENA_SIZE = 4096;
alignas(std::max_align_t)
std::byte g_applicationArena[APPLICATION_ARENA_SIZE];
Application* currentApplication = nullptr;
```

Starting an application:

```
currentApplication = new (g_applicationArena) SnakeGame();
```

Stop an application:

```C++
currentApplication->~Application();
currentApplication = nullptr;
```

Pros:

- No heap usage.
- No fragmentation.
- Memory usage = largest application only.
- Applications use completely normal member variables:

```C++
class SnakeGame : public Game
{
uint16_t score;
LedBuffer leds[300];
};
```

- Construction/destruction still works.
- Scales to 1000 applications.
- Need to know maximum application size.
- Must ensure arena is aligned.
- Need a size check:

```C++
static_assert(sizeof(SnakeGame) <= APPLICATION_ARENA_SIZE);
```

### Alternative 2: Union of all types (oldskool)

Old-school solution:

```C++
union ApplicationStorage
{
    MenuApplication menu;
    PongApplication pong;
    SnakeApplication snake;
    TetrisApplication tetris;
};
```

Activate:

```C++
new (&storage.snake) SnakeApplication();
```

Destroy:

```C++
storage.snake.~SnakeApplication();
```

Pros:

- No heap.
- No fragmentation.
- Compile-time guaranteed size.

Cons:

- Every application type must be known here.
- Horrible when you reach 100+ applications.
- Impossible to maintain with 1000 applications.

### Alternative 3: Monotonic Arena Allocator

Create your own allocator:

```C++
class Arena
{
    uint8_t buffer[8192];
    size_t offset;
};
```

Applications allocate from it.
When application exits:

```C++
arena.Reset();
```

Pros:

- No fragmentation.
- Can still use new.

Cons:

- Application code may accidentally hold pointers.
- More infrastructure.
- Harder to debug.
- Useful if applications need dynamic containers.

### Alternative 4: Use heap, but only once per application launch

```C++
Application* application = new SnakeGame();
...
delete application;
```

Pros:

- Easy.

Cons:

- After thousands of launches:
  Pong
  Snake
  Menu
  Tetris
  Tool
  Demo
  ...

heap fragmentation can appear.
ESP-IDF heap is decent, but if the goal is deterministic memory, I would not choose this.

### Alternative 5: ECS / Data-Oriented

Store all state externally:

```C++
struct SnakeState
{
...
};
```

 
Application code becomes stateless.

- Pros
- Maximum memory control.

Cons:

- Lots of boilerplate. Not pleasant for small games.

### Alternative choice

1: Fixed Application Arena:
2: Union of all types: impossible to maintain for 100+ applications
3: Monotonic Arena Allocator: Useful for dynamic containers, but not used in Fraxis.
4: Use heap, but only once per application launch: Deterministic memory required
5: ECS/Data-Oriented: Overkill for Fraxis.

Thus alternative 1 is selected.

## Design (Fixed Application Arena)

### Including factory

```C++
class Application
{
public:
    virtual void Start() = 0;
    virtual void Tick() = 0;
    virtual void Stop() = 0;
};
```

Single arena:

```C++
alignas(16)
std::byte applicationArena[MAX_APPLICATION_SIZE];
```

Factory:

```C++
Application* CreateApplication(
    EApplicationId id,
    void* memory)
{
    switch(id)
    {
        case EApplicationId::Pong:
            return new(memory) PongApplication();
        case EApplicationId::Snake:
            return new(memory) SnakeApplication();
        ...
    }
}
```

Changing application:

```C++
currentApplication->~Application();
currentApplication = CreateApplication(newId, applicationArena);
```

Result:

- 1000 applications supported.
- No heap fragmentation.
- Normal member variables.
- Constructor/destructor support.
- RAM usage = largest application.
- Very common embedded-game architecture.

### Compute largest application size at compile time

```C++
template<typename... Ts>
struct MaxSize;

template<typename T>
struct MaxSize<T>
{
    static constexpr size_t value = sizeof(T);
};

template<typename T, typename U, typename... Rest>
struct MaxSize<T, U, Rest...>
{
    static constexpr size_t value =
        sizeof(T) > MaxSize<U, Rest...>::value
        ? sizeof(T)
        : MaxSize<U, Rest...>::value;
};

constexpr size_t APPLICATION_ARENA_SIZE =
    MaxSize<
        PongApplication,
        SnakeApplication,
        TetrisApplication,
        MemoryArenaApplication,
        LedTesterApplication
    >::value;
```

Diagnostics:

```C++
printf("PongApplication       %u\n", sizeof(PongApplication));
printf("SnakeApplication      %u\n", sizeof(SnakeApplication));
printf("ApplicationArena   %u\n", sizeof(ApplicationArenaApplication));`
```

or

```C++
static_assert(sizeof(PongApplication) < 2000);
```

Best solution:

```C++
constexpr ApplicationInfo applications[] =
{
    { "Pong",        sizeof(PongApplication),        Create<PongApplication> },
    { "Snake",       sizeof(SnakeApplication),       Create<SnakeApplication> },
    { "MemoryArena", sizeof(MemoryArenaApplication), Create<ApplicationsArenaApplication> },
};

constexpr size_t MAX_APPLICATION_SIZE =
    CalculateLargestApplication(applications);

alignas(std::max_align_t)
std::byte applicationsArena[MAX_APPLICATION_SIZE];
```
