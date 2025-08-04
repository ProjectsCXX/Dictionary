# Подключаем GoogleTest (через FetchContent — удобно и просто)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(DictionaryTest DictionaryTest.cpp)
target_link_libraries(DictionaryTest PRIVATE gtest_main
                                              DictionaryLib)
target_include_directories(DictionaryTest PRIVATE include ${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include )

# Регистрируем тесты
include(GoogleTest)
gtest_discover_tests(DictionaryTest)


add_executable(
  DictionaryHandleTests
  main.cpp
)

target_link_libraries(
  DictionaryHandleTests
  DictionaryLib
)
