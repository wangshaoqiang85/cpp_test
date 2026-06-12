cmake_minimum_required(VERSION 3.26)
project(cppTest)

set(CMAKE_CXX_STANDARD 11)

add_executable(cppTest main.cpp
        daily/Day002TwoNumbers.cpp
        daily/day003lengthOfLongestSubstring.cpp
        daily/Day039CombinationSum.cpp
        daily/Day042TrapRainWater.cpp
)
