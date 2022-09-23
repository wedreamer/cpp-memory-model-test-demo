add_library(orderly)

target_sources(orderly
    PRIVATE
    orderly.cpp
)

# target_include_directories(example
# PUBLIC
# ${CMAKE_CURRENT_LIST_DIR}
# )

# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(orderly
        PUBLIC
        "--coverage"
    )
    target_link_options(orderly
        INTERFACE
        "--coverage"
    )
endif()
