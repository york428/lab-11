cmake_minimum_required(VERSION 3.14)
project(lab_4)

set(CMAKE_CXX_STANDARD 17)

# Автоматически скачиваем и подключаем Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавляем ваши файлы
add_executable(lab_4 main.cpp)

# Привязываем библиотеки gtest и gtest_main к вашему проекту
target_link_libraries(lab_4 PRIVATE GTest::gtest GTest::gtest_main)