# Integrate GoogleTest.
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Download and make GoogleTest Avaliable
FetchContent_MakeAvailable(googletest)

set(SRC_FILES 
    ../include/utility/utils.h
    ../include/utility/optimization_utils.h
    ../include/errors/errno.h
    ../include/containers/list.h
)

# add test executable
add_executable(
    test_NGHUNG
    main.cpp
    test_utils.cpp
    test_optimization_utils.cpp
    test_errors.cpp
    test_list.cpp
    ${SRC_FILES}

)

# include Google Test headers explicityly for IntelliSense
target_include_directories( 
    test_NGHUNG
    PRIVATE 
        ${googletest_SOURCE_DIR}/googletest/include
        ${SOURCE_DIR}/include
        )


target_link_libraries(
    test_NGHUNG
    PRIVATE 
        gtest 
        GTest::gtest_main
)


# Enable google test discovery
include(GoogleTest)
gtest_discover_tests(test_NGHUNG)