Monitor24

Every message has

- time stamp
- source layer
- type: info, debug, warning, error, diagnostics

System 1

- Initial
  - reset reasonv
  - uptime
  - firmware version
  - hardware version
  - chip revision
  - cpu frequency
    Tasks, per task
- fixed:
  - name
  - priority
  - core
  - stack memory
- last watchdog timestamp
- # watchdog messages sent
- task state
- stack memory used
- calculated
  - per message type:
    - type
    - amoun
    - per second
  - max watchdog interval index
  - max watchdog interval time
  - stack memory used max
  - stack memory used percentage
  - stack memory used max percentage
  - warning when >90%
    queues
- queue Name
- message name
- filled
- fixed:
  - capacity
- calculated:
  - per message type:
    - type
    - amount total
    - amount rejected, warning
    - amount dropped, warning
    - per second
  - filled max
  - filled percentage
  - filled max percentage
  - warning when >90%

Memory

- heap free
- largest free block
- interne ram
- externe ram
- calculated:
  - free heap min
  - free heap percentage
  - free heap min percentage
  - warning when <10%
  - largest free block min

Application

- active app
- State
- calculated
  -time in state
