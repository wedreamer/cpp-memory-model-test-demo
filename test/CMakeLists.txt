include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
    unit_tests
    orderly.cpp
    atom.cpp
    visible.cpp
)

target_link_libraries(unit_tests
    PRIVATE
    gtest_main
)

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(unit_tests
    PROPERTIES
    LABELS "unit"
    DISCOVERY_TIMEOUT # how long to wait (in seconds) before crashing
    250
)
