# libyou - Yet anOther Useless Library

## Building
| Command | Example | Output |
|--|--|--|
| `make build/<module>` | `make build/trees` | `target/libtrees.so` |
| `make build/<module>/debug` | `make build/trees/debug` | `target/libtrees-debug.so` |

##  Tests
| Action | Command (example with huffman/tests/enc_dec.cpp) | Output |
|--|--|--|
| Build test | `make build/huffman/tests/enc_dec` | `target/tests/huffman/enc_dec` |
| Run test | `make run/huffman/tests/enc_dec` | exit code |
| Debug test | `make debug/huffman/tests/enc_dec` | `gdb` session |
| Memcheck test | `make memcheck/huffman/tests/enc_dec` | leak report |

## Folder Structure
Each module (e.g. `linalg`) has its own `include/`, `src/`, and `tests/`
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
