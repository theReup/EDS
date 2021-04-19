cmake_minimum_required(VERSION 3.19)
project(trinket)

set(CMAKE_CXX_STANDARD 14)

add_executable(trinket
        main.cpp
        SHA256.cpp
        SHA256.h
        src/rsa.cpp
        src/rsa.h
        src/base64.cpp
        src/base64.h
        src/tea/xtea.cpp
        src/tea/xtea.h
        src/utils/bigint.cpp
        src/utils/bigint.h
        src/utils/random.h
        src/utils/utility.h
        src/utils/types.h
        car.cpp car.h trinket.cpp trinket.h)