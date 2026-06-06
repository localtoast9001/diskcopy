# Copilot Instructions for diskcopy

## Project Purpose
- This project is a C++ utility to read floppy disks into a virtual disk image.
- Keep behavior focused on reliable disk-copy workflows and explicit handling of read errors.

## Build and Output
- Build from `src/` using `make`.
- The build output binary must be `../out/diskcopy` (relative to `src/`).
- Keep `out/` as generated build output only.

## Language and Tooling
- Use C++17-compatible code.
- Keep compiler compatibility with `g++` and flags used in `src/Makefile`.
- Header include path is provided via `../inc` in the Makefile.
- Use `.cpp` for C++ source files and `.hpp` for C++ header files.
- Use `.c` for purely C source files and `.h` for purely C header files.

## Code Guidelines
- Prefer clear, explicit logic over clever abstractions.
- Handle error paths carefully for I/O operations and propagate meaningful error information.
- Avoid introducing external dependencies unless clearly necessary.
- Keep functions small and focused when possible.
- At the start of each source and header file, include a C-style doc header comment that contains the copyright notice and the file name.
- Put the copyright line first and include `All rights reserved.`.
- Use this format for C/C++ files:
	```
	/**
	 * Copyright (c) Jon Rowlett. All rights reserved.
	 * File: foo.hpp
	 */
	```
- All functions, except private class members, must have doc comments in both the header file and the source file.
- When declaring functions, place each parameter on its own line.
- Use lower snake_case for class names, member names, and variable names.
- Order include directives alphabetically within groups, with standard library includes first and project includes after.
- If a class is not a template, do not put bodies of virtual functions in header files; declare them in the header and define them in the source file.
- All header files must include both `#pragma once` and a unique include-guard macro (`#ifndef` / `#define` / `#endif`).
- Include-guard macro names must start with `__` and end with `__`, with the file name in all caps including extension in the middle; replace any characters that are not valid identifier characters with `_` when composing the macro name.
- Example: for `foo.h`, the include-guard macro name is `__FOO_H__`.

## Repository Conventions
- Keep edits minimal and scoped to the task.
- Do not commit generated files from `out/`.
- Preserve existing project layout (`inc/`, `src/`, `out/`).
