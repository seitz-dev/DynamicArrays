#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

#include "../src/models/List.cpp"

TEST_CASE("Happy path integer list insertion", "[lists]") {
    auto list = List<int>(1);
    const auto values = GENERATE(
        50, 23, 1, 999, 123512, 4522345, -23, -234
    );

    REQUIRE_NOTHROW(list.add(values));
}

TEST_CASE("Happy path string list insertion", "[lists]") {
    auto list = List<std::string>(2);
    const auto values = GENERATE("hi", "hello world", "", "whatever",
                                 "111111111111111111111111111111", "asdasdsad");

    REQUIRE_NOTHROW(list.add(values));
}

TEST_CASE("Happy path double list insertion", "[lists]") {
    auto list = List<double>(2);
    const auto values = GENERATE(2.0, 9.0, 2123.021, 2123.2123, 0.23, 0.64, 21.22);

    REQUIRE_NOTHROW(list.add(values));
}

TEST_CASE("Benchmark integer list insertion", "[lists][benchmark]") {
    List<int> list(1);

    auto *nums = new int[100000000];
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < 100000000; i++)
        nums[i] = rand() % 1000; // 0–999

    BENCHMARK("add integer to list") {
        return list.add(123);
    };

    BENCHMARK("add 100 integers to list") {
        for (int i = 0; i < 100; i++) {
            list.add(nums[i]);
        }
    };

    BENCHMARK("add 1 M integers to list") {
        for (int i = 0; i < sizeof(nums); i++) {
            list.add(nums[i]);
        }
    };

    delete[] nums;
}
