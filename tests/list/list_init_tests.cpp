#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/generators/catch_generators.hpp>
#include "../include/models/List.h"

TEST_CASE("Integer list construction with desired capacity", "[lists]") {
    const auto values = GENERATE(
        1, 2, 3, 4, 10, 25, 128, 300, 512, 1024, 8192, 16921
    );

    REQUIRE_NOTHROW(List<int>(values));
};

TEST_CASE("Integer list construction from various arrays", "[lists]") {
    const auto values = GENERATE(
        std::vector{1, 2, 3},
        std::vector{10, 20},
        std::vector{5},
        std::vector{1, 4, 6, 2, 3, 7, 3, 1, 2, 7, 12, 2351, 5242, 22532, 2902}
    );

    REQUIRE_NOTHROW(List(values.data(), values.size()));
}

TEST_CASE("Negative capacity value construction", "[lists]") {
    auto values = GENERATE(-1, -5, -25, -30, -999999, 1*-9);

    REQUIRE_THROWS(List<int>(values));
}

TEST_CASE("Integer construction benchmarks", "[lists][benchmark]") {
    BENCHMARK("integer list construction, assigned size of 8192") {
        return List<int>(8192);
    };

    BENCHMARK("integer list construction, initial size of 2") {
        return List<int>(2);
    };
}
