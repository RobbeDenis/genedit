include(GoogleTest)

add_executable(
    core_test
    core_test.cpp
)

target_link_libraries(core_test PRIVATE
    genedit_lib
    GTest::gtest_main
)

gtest_discover_tests(core_test)