cmake_minimum_required(VERSION 3.30)
project(NGHUNG LANGUAGES CXX)

#Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN "doxygen")
  if(NOT TARGET ${DOXYGEN})
    add_custom_command(OUTPUT "Doxyfile" COMMAND ${DOXYGEN_EXECUTABLE} "Doxyfile" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/documents")
    add_custom_target(${DOXYGEN} DEPENDS "Doxyfile")
    set_target_properties(${DOXYGEN} PROPERTIES FOLDER "doxygen")
  endif()
endif()
 
#
# for debuging
# 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -march=native -flto=8 -fno-inline -g -DNDEBUG")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -march=native -flto=8 -fno-inline -g -DNDEBUG")

#
# aggressive optimization
#
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -flto=8 -g -DNDEBUG")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -march=native -flto=8 -g -DNDEBUG")

find_package(Boost 1.87 REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()


include_directories(include)

add_subdirectory(src)

option(BUILD_NGHUNG_TESTS "Build  NGHUNG tests" ON)
if (BUILD_NGHUNG_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()