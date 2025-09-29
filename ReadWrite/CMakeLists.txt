cmake_minimum_required(VERSION 3.29.3)
project(ReadWrite CXX)

# Указываем стандарт C++17 для поддержки std::thread
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем компилятор g++
set(CMAKE_CXX_COMPILER "g++")

# Добавляем исполняемый файл
add_executable(threaded_io src/main.cpp)

