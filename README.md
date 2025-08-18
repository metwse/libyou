# libyou - Yet anOther Useless Library

## Building
| Command | Example | Output |
|--|--|--|
| `make build/<module>` | `make build/collections` | `target/libcollections.so` |
| `make build/<module>/debug` | `make build/collections/debug` | `target/libcollections-debug.so` |

##  Tests
| Action | Command (example with collections/it_works.cpp) | Output |
|--|--|--|
| Build test | `make build/collections/tests/it_works` | `target/tests/collections/it_works` |
| Run test | `make run/collections/tests/it_works` | exit code |
| Debug test | `make debug/collections/tests/it_works` | `gdb` session |
| Memcheck test | `make memcheck/collections/tests/it_works` | leak report |

## Folder Structure
Each module (e.g. `collections`) has its own `include/`, `src/`, and `tests/`
directories.

```py
<module>/
  include/   # Public headers
  src/       # Implementation
  tests/     # Integration tests
target/      # Build outputs
Makefile     # Build system
```
## Docs
Run `make docs` for auto-generate Doxygen. Documentations located at
`target/docs/`.

## Dependencies
- GNU Make (≥ 4)
- g++ (`C++17`)
- gdb (optional, for `debug`)
- valgrind (optional, for `memcheck`)
- bear (optional, for `compile_commands.json`)
