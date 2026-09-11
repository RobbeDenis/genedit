include(GoogleTest)

add_executable(
    genedit_test
    genedit_test.cpp
)

target_link_libraries(genedit_test PRIVATE
    genedit_lib
    GTest::gtest_main
)

gtest_discover_tests(genedit_test)