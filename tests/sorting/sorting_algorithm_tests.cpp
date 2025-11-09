#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

#include "../src/models/List.cpp"
#include "models/sorting/BubbleSortAlgorithm.h"
#include "models/sorting/SelectionSortAlgorithm.h"
#include "models/sorting/parser/IntSortParser.h"

TEST_CASE("Sorting algorithms work expectedly.") {
    auto list = List({1, 3, 2, 6, 1, 2, 1, 12});
    auto expectedList = List({1, 1, 1, 2, 2, 3, 6, 12});
    const auto integerValueParser = IntSortParser();

    auto garbageArray = List<int>();
    for (int i = 0; i < 1000; i++) {
        garbageArray.add(rand());
    }

    SECTION("Bubble sort algorithm with integer value parser") {
        const auto bubbleSortAlgorithm = BubbleSortAlgorithm();

        REQUIRE(list.sort(bubbleSortAlgorithm, integerValueParser) == expectedList);

        BENCHMARK("bubble sort algorithm sort, modest array size") {
            return list.sort(bubbleSortAlgorithm, integerValueParser);
        };

        BENCHMARK("bubble sort with 1000 items") {
            return garbageArray.sort(bubbleSortAlgorithm, integerValueParser);
        };
    }

    SECTION("Selection sort algorithm with integer value parser") {
        const auto selectionSortAlgorithm = SelectionSortAlgorithm();

        REQUIRE(list.sort(selectionSortAlgorithm, integerValueParser) == expectedList);

        BENCHMARK("selection sort algorithm sort, modest array size") {
            return list.sort(selectionSortAlgorithm, integerValueParser);
        };

        BENCHMARK("selection sort with 1000 items") {
            return garbageArray.sort(selectionSortAlgorithm, integerValueParser);
        };
    }
}
