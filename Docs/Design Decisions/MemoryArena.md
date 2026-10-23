# MEMORY ARENA

## Goal

Preventing memory defragmentation when switch apps.

## Conditions

- Only one application running simultaneously.
- Menu is app 0.

## Alternatives

### Alternative 1: Fixed App Arena

Use a so called Fixed App Arena.
using a so called `placement new` memory from one app can be reused by the next active app.

```C++
constexpr size_t APP_ARENA_SIZE = 4096;
alignas(std::max_align_t)
std::byte g_appArena[APP_ARENA_SIZE];
Application* currentApp = nullptr;
```

Starting an app:

```
currentApp = new (g_appArena) SnakeGame();
```

Stop an app:

```C++
currentApp->~Application();
currentApp = nullptr;
```

Pros:

- No heap usage.
- No fragmentation.
- Memory usage = largest app only.
- Apps use completely normal member variables:

```C++
class SnakeGame : public Game
{
uint16_t score;
LedBuffer leds[300];
};
```

- Construction/destruction still works.
- Scales to 1000 apps.
- Need to know maximum app size.
- Must ensure arena is aligned.
- Need a size check:

```C++
static_assert(sizeof(SnakeGame) <= APP_ARENA_SIZE);
```

### Alternative 2: Union of all types (oldskool)

Old-school solution:

```C++
union AppStorage
{
    MenuApp menu;
    PongApp pong;
    SnakeApp snake;
    TetrisApp tetris;
};
```

Activate:

```C++
new (&storage.snake) SnakeApp();
```

Destroy:

```C++
storage.snake.~SnakeApp();
```

Pros:

- No heap.
- No fragmentation.
- Compile-time guaranteed size.

Cons:

- Every app type must be known here.
- Horrible when you reach 100+ apps.
- Impossible to maintain with 1000 apps.

### Alternative 3: Monotonic Arena Allocator

Create your own allocator:

```C++
class Arena
{
    uint8_t buffer[8192];
    size_t offset;
};
```

Apps allocate from it.
When app exits:

```C++
arena.Reset();
```

Pros:

- No fragmentation.
- Can still use new.

Cons:

- App code may accidentally hold pointers.
- More infrastructure.
- Harder to debug.
- Useful if apps need dynamic containers.

### Alternative 4: Use heap, but only once per app launch

```C++
Application* app = new SnakeGame();
...
delete app;
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

 
App code becomes stateless.

- Pros
- Maximum memory control.

Cons:

- Lots of boilerplate. Not pleasant for small games.

### Alternative choice

1: Fixed App Arena:
2: Union of all types: impossible to maintain for 100+ apps
3: Monotonic Arena Allocator: Useful for dynamic containers, but not used in Fraxis.
4: Use heap, but only once per app launch: Deterministic memory required
5: ECS/Data-Oriented: Overkill for Fraxis.

Thus alternative 1 is selected.

## Design (Fixed App Arena)

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
std::byte appArena[MAX_APP_SIZE];
```

Factory:

```C++
Application* CreateApp(
    EAppId id,
    void* memory)
{
    switch(id)
    {
        case EAppId::Pong:
            return new(memory) PongApp();
        case EAppId::Snake:
            return new(memory) SnakeApp();
        ...
    }
}
```

Changing app:

```C++
currentApp->~Application();
currentApp = CreateApp(newId, appArena);
```

Result:

- 1000 apps supported.
- No heap fragmentation.
- Normal member variables.
- Constructor/destructor support.
- RAM usage = largest app.
- Very common embedded-game architecture.

### Compute largest app size at compile time

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

constexpr size_t APP_ARENA_SIZE =
    MaxSize<
        PongApp,
        SnakeApp,
        TetrisApp,
        MemoryArenaApp,
        LedTesterApp
    >::value;
```

Diagnostics:

```C++
printf("PongApp       %u\n", sizeof(PongApp));
printf("SnakeApp      %u\n", sizeof(SnakeApp));
printf("MemoryArena   %u\n", sizeof(MemoryArenaApp));`
```

or

```C++
static_assert(sizeof(PongApp) < 2000);
```

Best solution:

```C++
constexpr ApplicationInfo apps[] =
{
    { "Pong",        sizeof(PongApp),        Create<PongApp> },
    { "Snake",       sizeof(SnakeApp),       Create<SnakeApp> },
    { "MemoryArena", sizeof(MemoryArenaApp), Create<MemoryArenaApp> },
};

constexpr size_t MAX_APP_SIZE =
    CalculateLargestApp(apps);

alignas(std::max_align_t)
std::byte appArena[MAX_APP_SIZE];
```
