# TOOLS (CODE ANALYZERS & METRICS)

## Introduction

This document describes all tooling needed for developing.

## Microsoft VSCode

Used for the ESP build.

Extensions:

- Espressif IDF

All extensions are explained in more detailed later.

## Microsoft Visual Studio 2026

Used for the Simulator.

Extensions:

All extensions are explained in more detailed later.

## GitHub / GitLens

GitHub is used.

Link to repository: http://www.github.com/michelkeijzers/fraixis

Install Gitlens.

## VS Code Settings

See .vscode/c_cpp_properties.json

## Visual Studio

In project, select Compiler/general, set W4 (warnings) and Treat warnings as errors.

## clang-tidy, clang-format

clang-d is NOT used because it gives a lot of unknown (red underlined) include files which cannot be
fixed easily. Visual Studio already has good internal functionality for clang tidy.

clang-tidy is used on both VS Code and Visual Studio.

For VSCode:

Install clang-tidy and clang-format.

Files used are:

- .vscode/c_cpp_properties.json
- .vscode/settings.json: default intellisense (not clangd), formatter: clang-format
- .clang-format: .cpp, LLVM, indent 4, braces: Allman
- .clang-tidy: No Fuchsia (google related), treat warnings as errors.

For Visual Studio:

Install clang-tidy and clang-format.
Files clang-format and clang-tidy are used as above (same files).

### CodeMaid

For clean up.

### Espressif IDF

To be installed in VSCode only as it creates the ESP32 build.

### GitLens

For checking GIT history.

### SonarCube

On Visual Studio, install SonarCube.
It does not need to be connected toi a server.
Check the report (manually) via the menu Extensions/SonarCube/Show SonarCube Report.
It shows TODOs and other issues.

Suppress warnings/errors:

```
// NOSONAR
```

It is not possible to suppress specific warnings/errors, the suppression is for all sonar warnings/
errors in the same line.

###

Metrics / Code complexity
Method length: <= 50 physical lines
Cyclomatic complexity: <= 10 per method
Cognitive complexity : <= 15 per method
Parameters per method: <= 5 parameters
Nesting depth: <= 4 nested levels

MEMORY LEAKS
Visual Studio diagnostics, memory profile

ASan
Built in Visual Sutid /fsanitize-address
in ESP-IDF: component config->Heap memory debugging-> enable addrses santizer

Stackoverflow
Compile-time Stack safety gate
ESP
Add
-werror=frame-larget-than=256
This checks per function the stack usage.
Windows:
Compile as x86 / 32 bit.
Use 4 byte pointers to have same pointer length in ESP by using
/we6262 /analyze:stacksize 256
// Compile-time quality gate in M00_System
static_assert(sizeof(void) == 4, "Error: Simulator must be compiled as a 32-bit (x86) application!");
In Windows a tracker can be used, per (j)thread, checking the stack limits in the main loop of each RTOS task (jthread).
Prevent: use unique_ptr instead of long arrays, auto removal (which is needed for unit tests).
FORMATTING
Clang-Format
EditorConfig
Both on VSCode and Visual studio
for keeping same endof line styles etc

WOKWI
Uses .elf file to run.
GIT
Gitlens

UNIT TESTING
To be isntalled in Visual Studio only.
Implement in M75_UnitTests
Uses Google Test and GMock.
Shared mocks
dedicated mocks
OpenCppCoverage

This message contains information that may be privileged or confidential and is the property of the Capgemini Group. It is intended only for the person to whom it is addressed. If you are not the intended recipient, you are not authorized to read, print, retain, copy, disseminate, distribute, or use this message or any part thereof. If you receive this message in error, please notify the sender immediately and delete all copies of this message.
