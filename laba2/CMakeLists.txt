  cmake_minimum_required(VERSION 3.10)
  project(lab2)

  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  # Загрузка Google Test из GitHub
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
  )
  FetchContent_MakeAvailable(googletest)

  # Создание библиотеки с нашими классами
  add_library(Five_lib STATIC 
    src/customVector.cpp 
    src/Five.cpp
  )

  # Указание путей к заголовочным файлам
  target_include_directories(Five_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

  # Основное приложение
  add_executable(main_app main.cpp)
  target_link_libraries(main_app Five_lib)

  # Тесты
  enable_testing()
  add_executable(tests tests/FiveTest.cpp)
  target_link_libraries(tests Five_lib gtest_main)

  # Добавление тестов в систему тестирования CMake
  add_test(NAME FiveTests COMMAND tests)