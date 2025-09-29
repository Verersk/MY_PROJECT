cmake_minimum_required(VERSION 3.29.3)
project(ThreadedIO CXX)

# Указываем стандарт C++17 для поддержки std::thread
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем компилятор g++
set(CMAKE_CXX_COMPILER "g++")

set(SOURCES
    src/main.cpp
    lib/tread.cpp
)

# Добавляем исполняемый файл
add_executable(threaded_io ${SOURCES})

target_include_directories(threaded_io PRIVATE
	${CMAKE_SOURCE_DIR}/lib
)

# Линкуем библиотеку для потоков
find_package(Threads REQUIRED)
target_link_libraries(threaded_io PRIVATE Threads::Threads)
