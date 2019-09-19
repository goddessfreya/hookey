# My version, use previous version at own risk
CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

PROJECT(Hookey)
SET(CMAKE_CXX_STANDARD 17) # no explicit compiler flags if possible
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(HOOKEY_NAME "Hookey")

ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/subhook)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -pthread -g -fexceptions -fstack-protector-all -flto -fPIC -march=native -fomit-frame-pointer")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-plt -mno-xop -mno-fma4 -mno-tbm")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -ldl -lstdc++ -lm -fuse-ld=gold")

ADD_LIBRARY(${HOOKEY_NAME} SHARED
	${CMAKE_SOURCE_DIR}/hookey.cpp
	${CMAKE_SOURCE_DIR}/hookey_impls.cpp
	${CMAKE_SOURCE_DIR}/hookey_steamapps.cpp
)
TARGET_LINK_LIBRARIES(${HOOKEY_NAME} subhook)
