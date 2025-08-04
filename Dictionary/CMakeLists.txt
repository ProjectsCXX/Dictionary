cmake_minimum_required(VERSION 3.16)

project(Dictionary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library (DictionaryLib
               src/dictionary.cpp
               src/handleconsoleoperations.cpp)      # Создаем библиотеку с набором cpp

target_include_directories(DictionaryLib PUBLIC include)

# Тесты
enable_testing()
add_subdirectory(tests)
