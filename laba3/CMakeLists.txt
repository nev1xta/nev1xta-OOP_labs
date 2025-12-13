cmake_minimum_required(VERSION 3.10)
project(GeometryFigures VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Загрузка Google Test из GitHub с исправлениями
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0  # Используем более стабильную версию
)
FetchContent_MakeAvailable(googletest)

# Создание библиотеки с нашими классами
add_library(GeometryLib STATIC
    src/point.cpp
    src/figure.cpp
    src/vector_points.cpp
    src/vector_figure.cpp
    src/octagon.cpp
    src/pentagon.cpp
    src/hexagon.cpp
)

# Указание путей к заголовочным файлам
target_include_directories(GeometryLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Основное приложение
add_executable(geometry_figures src/main.cpp)
target_link_libraries(geometry_figures GeometryLib)

# Тесты
enable_testing()
add_executable(run_tests
    tests/test_point.cpp
    tests/test_figures.cpp
    tests/test_vectors.cpp
    tests/main_test.cpp
)
target_link_libraries(run_tests GeometryLib gtest_main)

# Добавление тестов в систему тестирования CMake
add_test(NAME GeometryTests COMMAND run_tests)