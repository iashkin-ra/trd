cmake_minimum_required(VERSION 3.28.3)
project(Algocode)

set(CMAKE_CXX_STANDARD 26)

add_compile_options(
        -Wall
        -Wextra
        -Wshadow
        -Wfloat-equal
        -Wformat=2
        -Wlogical-op
        -Wno-sign-compare
        -Wno-unused-result
)

# --- LAUNCH MODES ---

# Debug mode (maximum safety)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC")

# Release mode (minimum safety, maximum speed)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")

# RelWithDebInfo mode (for stress testing)
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g -fsanitize=address,undefined -fno-omit-frame-pointer")
