#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

#include "../src/models/List.cpp"

TEST_CASE("Element can be looked up via direct array access or search.", "[list]") {
    auto testArray = List<int>();

    for (int i = 0; i < 99; i++) {
        testArray.add(rand());
    }

    testArray.add(-234);

    SECTION("Elements can be searched for") {
        BENCHMARK("find item at end of array of 100") {
            return testArray
                    .findFirst([](auto x) { return x == -234; });
        };

        REQUIRE(
            testArray
            .findFirst([](auto x){ return x == -234; })
        );
    }

    SECTION("Elements can be accessed directly via array access") {
        BENCHMARK("Access index 99 directly") {
            return testArray[99];
        };

        REQUIRE(testArray[99] == -234);
    }
}
