#include <iostream>
#include <span>

#include "src/models/List.cpp"
#include "include/models/sorting/BubbleSortAlgorithm.h"
#include "include/models/sorting/parser/IntSortParser.h"
#include "models/sorting/SelectionSortAlgorithm.h"

template<typename T>
void printSize(List<T> list) {
    std::cout << "Allocated size: " << list.getSize() << " | Count: " << list.getCount() << std::endl;
    std::cout << "Allocated memory: " << (list.getSize() * 32) / 8 << " bytes. | Consuming memory: " << (
        list.getCount() * 32) / 8 << " bytes." << std::endl;
}

int main() {
    List<int> numbers;
    numbers.add(2);

    printSize(numbers);

    numbers.add(4);
    numbers.add(2);

    printSize(numbers);

    numbers.add(5);
    numbers.add(3);

    std::cout << numbers.toString() << std::endl;

    const auto result = numbers.findFirst([](auto x) {
        return x == 5;
    });

    const auto result2 = numbers.findIndex([](auto x) {
        return x == 3;
    });

    if (result.has_value()) {
        std::cout << "Found: " << result.value() << std::endl;
    }

    if (result.has_value()) {
        std::cout << "Found: " << numbers[result2.value()] << " at index: " << result2.value() << std::endl;
    }

    auto moreThan3List = numbers.find([](const int x) {
        return x > 3;
    });

    numbers.insertAt(12, 4);

    std::cout << "More than 3: " << moreThan3List.toString() << std::endl;
    std::cout << numbers.toString() << std::endl;

    numbers.insertAt(-1, 0);

    std::cout << "Inserted '-1' to beginning." << std::endl;
    std::cout << numbers.toString() << std::endl;

    // delete new index
    numbers.deleteAt(0);
    std::cout << "Deleted 0th index." << std::endl;
    std::cout << numbers.toString() << std::endl;

    // reverse array
    auto reversedArray = numbers.reverse();
    std::cout << "Reversed array." << std::endl;
    std::cout << reversedArray.toString() << std::endl;

    // bubble sort array
    auto bubbleSortedArray = reversedArray.sort(BubbleSortAlgorithm(), IntSortParser());
    std::cout << "Bubble sorted array." << std::endl;
    std::cout << bubbleSortedArray.toString() << std::endl;

    // selection sort array
    auto selectionSortedArray = reversedArray.sort(SelectionSortAlgorithm(), IntSortParser());
    std::cout << "Selection sorted array." << std::endl;
    std::cout << selectionSortedArray.toString() << std::endl;

    printSize(reversedArray);
    return 0;
}
