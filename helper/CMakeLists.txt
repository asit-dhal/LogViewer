set(HELPER_SRCS
    src/appconfig.cpp
)
add_library(helper ${HELPER_SRCS})
target_include_directories(helper PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(helper
    Qt5::Core
)

include (CMakePrintHelpers)
cmake_print_properties(TARGETS helper PROPERTIES INTERFACE_INCLUDE_DIRECTORIES IMPORTED_LOCATION)
cmake_print_properties(TARGETS helper PROPERTIES INCLUDE_DIRECTORIES IMPORTED_LOCATION)
