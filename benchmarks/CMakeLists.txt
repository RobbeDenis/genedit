add_executable(
    genedit_bench 
    main.cpp
    random_bench.cpp
)

target_link_libraries(
    genedit_bench
    PRIVATE
        genedit_lib
        benchmark::benchmark_main
)