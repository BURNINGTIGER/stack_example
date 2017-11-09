[![Build Status](https://travis-ci.org/BURNINGTIGER/stack_example.svg?branch=master)](https://travis-ci.org/BURNINGTIGER/stack_example)

```
cmake -H. -B_builds -DBUILD_TESTS=ON -DBUILD_EXAMPLES=ON
cmake --build _builds
cmake --build _builds --target test -- ARGS=--verbose
_builds/example
```
