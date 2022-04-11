# toxiproxy-cpp

This is a C++ client for [Toxiproxy](https://github.com/Shopify/toxiproxy).
The implementation is ported from the [Java Toxiproxy client](https://github.com/trekawek/toxiproxy-java). 

## Usage
To incorporate this client library in an existing CMake project,
one can embed the client library directly using [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html)
```
include(FetchContent)

FetchContent_Declare(
  toxiproxy
  GIT_REPOSITORY https://github.com/Bit-Quill/toxiproxy-cpp
)

# The client builds as a static library by default, to build it as a shared library set BUILD_TOXIPROXY_AS_SHARED to ON.
set(BUILD_TOXIPROXY_AS_SHARED ON CACHE INTERNAL "")

FetchContent_MakeAvailable(toxiproxy)

target_link_libraries(foo toxiproxy)
```

## Build
To build the library from source, run the following commands:
```
cmake -S . -G "Visual Studio 16 2019"
cmake --build . --config Release
```
