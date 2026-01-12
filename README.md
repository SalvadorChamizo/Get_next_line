# Get_next_line

Short C library that implements `get_next_line(int fd)`: a buffered line reader which returns the next line (including the trailing `\n` when present) from a file descriptor. The implementation is POSIX-oriented, handles partial reads and variable `BUFFER_SIZE`, and includes an optional bonus variant supporting multiple simultaneous file descriptors.

## Key Features
- Return the next line from a file descriptor as a heap-allocated `char *`.
- Preserve the trailing newline character when present.
- Robust handling of partial `read()` results and arbitrary `BUFFER_SIZE` values.
- Bonus variant provides per-file-descriptor state for concurrent descriptors (`bns/`).
- Minimal, dependency-free C (C99) suitable for embedding in other C projects.

## Tech Stack
- Language: C (C99)
- Target platform: POSIX-compliant systems (Linux, macOS)
- Tooling: `gcc` / `clang`, `make` (optional)

## Architecture & Design
- Buffered iterative reader: repeatedly `read()`s into a fixed-size buffer, appends into a growing string, and stops when a newline or EOF is reached.
- Memory ownership: `get_next_line` returns a `malloc`'d string — the caller is responsible for `free()`.
- Layout:
	- `src/` — single-fd implementation and helpers (`get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`).
	- `bns/` — bonus multi-fd implementation and helpers (`get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h`).

## Getting Started

Prerequisites
- POSIX-compatible OS (Linux, macOS)
- `gcc` or `clang`
- `make` (optional)

Installation
- Clone the repository into your workspace (assumed already present).

Notes
- This repository provides library sources but does not include a top-level `main` in the library directories. To build an executable, compile a small runner (example `main.c`) together with the library sources. The examples below assume you will create or provide such a runner.

Build (single-fd variant)
Create an example `main.c` (see Usage section), then compile:
```sh
gcc -std=c99 -Wall -Wextra -Werror -D BUFFER_SIZE=32 \
	-I src \
	src/get_next_line.c src/get_next_line_utils.c main.c -o gnl
```

Build (bonus multi-fd variant)
```sh
gcc -std=c99 -Wall -Wextra -Werror -D BUFFER_SIZE=32 \
	-I bns \
	bns/get_next_line_bonus.c bns/get_next_line_utils_bonus.c main.c -o gnl_bonus
```

Suggested Makefile targets (optional): `make` to build `gnl`/`gnl_bonus`, `make clean` to remove binaries.

## Usage
- API: `char *get_next_line(int fd);`
	- Returns a `malloc`'d string containing the next line (including `\n` when present).
	- Returns `NULL` on EOF or error.
	- Caller must `free()` the returned pointer.

Example runner (`main.c`)
```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h" /* or get_next_line_bonus.h */

int main(int argc, char **argv)
{
		if (argc < 2) {
				fprintf(stderr, "Usage: %s path/to/file\n", argv[0]);
				return 1;
		}
		int fd = open(argv[1], O_RDONLY);
		if (fd < 0) {
				perror("open");
				return 1;
		}
		char *line;
		while ((line = get_next_line(fd)) != NULL) {
				printf("%s", line);
				free(line);
		}
		close(fd);
		return 0;
}
```

## What I Learned / Technical Challenges
- Managing heap allocations across successive reads without leaks.
- Correctly handling partial `read()` results, EOF, and error semantics.
- Implementing per-file-descriptor state safely for the bonus variant.

## Future Improvements
- Add a repository `Makefile` and automated tests (unit tests or a test harness).
- Provide clearer error signaling so callers can distinguish EOF from read errors.
- Offer a thread-safe or reentrant API wrapper.
- Add benchmarks for different `BUFFER_SIZE` values and large-file performance.

## Author & Contact
- Author: schamizo
- Contact: salvadorchamizo@gmail.com
