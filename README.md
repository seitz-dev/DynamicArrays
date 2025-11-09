# DynamicArrays

A high-performance C++20 library providing a generic, dynamically-resizable list implementation with built-in sorting algorithms and advanced functional programming capabilities.

## Overview

DynamicArrays is a header-based and template-driven library that offers a type-safe, efficient alternative to fixed-size arrays and provides a versatile `List<T>` container with functional programming paradigms. It includes implementations of fundamental sorting algorithms and a flexible parser system for customizable sorting behavior.

## Features

### Core Features

- **Generic List Container** (`List<T>`): A dynamically-resizable, template-based list supporting any data type
- **Intelligent Memory Management**: Automatic resizing with efficient capacity management to minimize memory reallocations
- **Functional Programming Support**: Higher-order functions for filtering, mapping, and searching
- **Type-Safe Operations**: Full compile-time type checking with C++20 features

### List Operations

- **add(item)** - O(1) amortized: Add elements to the end of the list
- **insertAt(item, index)** - O(n): Insert an element at a specific index
- **deleteAt(index)** - O(n): Remove an element at a specific index
- **findFirst(predicate)** - O(n): Find the first element matching a condition, returns `std::optional<T>`
- **findIndex(predicate)** - O(n): Find the index of the first matching element
- **find(predicate)** - O(n): Find all elements matching a condition, returns a new `List<T>`
- **reverse()** - O(n): Create a reversed copy of the list
- **copy()** - O(n): Create a deep copy of the list
- **operator[]** - O(1): Random access to elements with bounds checking
- **toString()** - O(n): Convert list to string representation

### Sorting Algorithms

The library includes multiple sorting algorithm implementations:

#### Bubble Sort Algorithm
- **Time Complexity**: O(n²)
- **Space Complexity**: O(1)
- **Best Use Case**: Small datasets or nearly-sorted data
- **Implementation**: `BubbleSortAlgorithm`

#### Selection Sort Algorithm
- **Time Complexity**: O(n²)
- **Space Complexity**: O(1)
- **Best Use Case**: When memory writes need to be minimized
- **Implementation**: `SelectionSortAlgorithm`

#### Extensible Algorithm Framework
- Implement `SortAlgorithm<T>` interface to create custom sorting algorithms
- Plugin architecture allows seamless addition of new algorithms (Quick Sort, Merge Sort, etc.)

### Parsing System

The library includes a flexible parser system for customizing sorting behavior:

- **ValueSortParser<T>**: Base parser interface for sort value extraction
- **IntSortParser**: Specialized parser for integer sorting logic

## Installation

### Requirements

- C++20 compiler (GCC 10+, Clang 10+, MSVC 19.23+)
- CMake 3.20 or higher
- Catch2 3.0+ (for testing, optional)
- Git (for version control and fetching vcpkg)

### Quick Start with vcpkg (Recommended)

```bash
# Install vcpkg if you don't have it
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat  # or ./bootstrap-vcpkg.sh on Linux/macOS

# Install dependencies
.\vcpkg install catch2:x64-windows  # or your appropriate triplet

# Clone and build DynamicArrays
git clone https://github.com/seitz-dev/DynamicArrays.git
cd DynamicArrays
mkdir build
cd build

# Configure with vcpkg toolchain
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release

# Run tests
.\tests\Release\DynamicArraysTests.exe
```

### Manual Build (Without Tests)

If you prefer not to install vcpkg or Catch2, you can build just the main library:

```bash
git clone https://github.com/seitz-dev/DynamicArrays.git
cd DynamicArrays
mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release

# Run the main executable
.\Release\DynamicArrays.exe
```

## Usage Examples

### Basic List Operations

```cpp
#include "models/List.h"

// Create a list
List<int> numbers;

// Add elements
numbers.add(5);
numbers.add(2);
numbers.add(8);
numbers.add(3);

// Access elements
std::cout << numbers[0] << std::endl;  // Output: 5

// Get list properties
std::cout << "Count: " << numbers.getCount() << std::endl;     // Output: 4
std::cout << "Capacity: " << numbers.getSize() << std::endl;   // Output: capacity value
```

### Finding Elements

```cpp
// Find first element greater than 3
auto result = numbers.findFirst([](int x) { return x > 3; });
if (result.has_value()) {
    std::cout << "Found: " << result.value() << std::endl;
}

// Find index of first element equal to 8
auto index = numbers.findIndex([](int x) { return x == 8; });
if (index.has_value()) {
    std::cout << "Element at index " << index.value() << ": " 
              << numbers[index.value()] << std::endl;
}

// Find all elements greater than 3 (returns new List)
List<int> filtered = numbers.find([](int x) { return x > 3; });
std::cout << filtered.toString() << std::endl;  // Output: [5, 8]
```

### List Manipulation

```cpp
// Insert at specific index
numbers.insertAt(10, 1);  // Inserts 10 at index 1

// Delete at specific index
numbers.deleteAt(2);

// Reverse the list
List<int> reversed = numbers.reverse();

// Copy the list
List<int> copy = numbers.copy();

// Convert to string
std::string str = numbers.toString();  // Output: "[5, 10, 2, 3]"
```

### Sorting

```cpp
#include "models/sorting/BubbleSortAlgorithm.h"
#include "models/sorting/parser/IntSortParser.h"

// Create algorithm and parser
BubbleSortAlgorithm bubbleSort;
IntSortParser parser;

// Sort the list
List<int> sorted = numbers.sort(bubbleSort, parser);
std::cout << sorted.toString() << std::endl;
```

### Memory Management

```cpp
// Check allocated vs. consumed memory
printSize(numbers);
// Output:
// Allocated size: 8 | Count: 4
// Allocated memory: 32 bytes | Consuming memory: 16 bytes
```

## Architecture

### Class Hierarchy

```
List<T>
├── Core Data Structure
│   ├── T* arr (dynamic array)
│   ├── int count (number of elements)
│   └── int capacity (allocated capacity)
├── Operations
│   ├── add()
│   ├── find*()
│   └── sort()
└── Utilities
    ├── resize()
    ├── reduce()
    └── toString()

SortAlgorithm<T> (Abstract Base)
├── BubbleSortAlgorithm
└── SelectionSortAlgorithm

ValueSortParser<T> (Abstract Base)
├── IntSortParser
└── Custom implementations
```

### Dynamic Resizing Strategy

The list uses a growth factor strategy for resizing:
- Initial capacity: 1 element
- When capacity is reached, the array is resized (typically doubling)
- When elements are removed, the array may be reduced to save memory
- This provides O(1) amortized insertion

## Benchmarks

Run the following to obtain performance benchmarks:

```bash
cd build
.\tests\Release\DynamicArraysTests.exe --benchmark-samples 100
```

### Expected Performance (Catch2 Benchmarks)

The following benchmarks are measured on a system with MSVC 19.43 (Visual Studio 2022) in Release mode:

| Benchmark | Array Size | Mean Time | Low Mean | High Mean | Std Dev |
|-----------|-----------|-----------|----------|-----------|---------|
| **Sorting - Bubble Sort** |
| Modest array (8 elements) | 8 | 128.8 ns | 115.9 ns | 150.1 ns | 82.9 ns |
| Large array | 1000 | 583.0 μs | 570.7 μs | 601.1 μs | 75.4 μs |
| **Sorting - Selection Sort** |
| Modest array (8 elements) | 8 | 137.9 ns | 125.8 ns | 158.0 ns | 77.6 ns |
| Large array | 1000 | 497.6 μs | 490.1 μs | 508.9 μs | 46.7 μs |
| **List Operations** |
| Direct array access | 100 | 0.93 ns | 0.91 ns | 0.96 ns | 0.13 ns |
| Find item at end | 100 | 144.2 ns | 138.9 ns | 150.4 ns | 29.3 ns |
| Add single integer | N/A | 302.7 ns | 2.4 ns | 1.8 μs | 2.99 μs |
| Add 100 integers | 100 | 289 ns | 280.5 ns | 299.9 ns | 48.7 ns |
| Add 1M integers | 1M | 27.5 ns | 26.5 ns | 28.8 ns | 5.8 ns |
| **List Construction** |
| Initial size 2 | 2 | 27.9 ns | 25.3 ns | 31.6 ns | 15.5 ns |
| Assigned size 8192 | 8192 | 3.8 μs | 3.7 μs | 4.1 μs | 0.92 μs |

### Key Performance Observations

1. **Direct Array Access**: Extremely fast at ~0.93 ns (essentially free after compiler optimizations)
2. **Sorting Algorithms**: Selection Sort is ~17% faster than Bubble Sort for 1000 items (497.6 μs vs 583.0 μs)
3. **Adding Elements**: Amortized O(1) addition is consistent at ~300 ns per element
4. **Scaling**: The 1M addition benchmark shows efficient memory management with minimal per-element overhead

## Testing

The library includes comprehensive unit tests using Catch2:

```bash
# Run all tests
ctest

# Run specific test
ctest -R "Sorting algorithms"

# Run with verbose output
ctest --verbose
```

### Test Coverage

- List initialization and basic operations
- Element insertion and deletion
- Functional operations (find, filter, map)
- Sorting algorithm correctness
- Edge cases and boundary conditions
- Memory management and resizing

## Performance Characteristics

### Time Complexity

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| add() | O(1) amortized | May trigger resize |
| access [i] | O(1) | Constant-time access |
| insertAt() | O(n) | Requires shifting elements |
| deleteAt() | O(n) | Requires shifting elements |
| find() | O(n) | Linear search |
| sort() | Depends on algorithm | O(n²) for Bubble/Selection |
| reverse() | O(n) | Creates new list |
| copy() | O(n) | Deep copy of all elements |

### Space Complexity

| Feature | Complexity | Notes |
|---------|-----------|-------|
| List<T> storage | O(n) | Where n is capacity |
| sort() | O(1) or O(n) | In-place or new list depending on algorithm |
| find() | O(m) | Where m is number of matches |

## Design Patterns

- **Strategy Pattern**: Sorting algorithms implement `SortAlgorithm<T>` interface
- **Parser Pattern**: `ValueSortParser<T>` provides customizable sort logic
- **Template Method Pattern**: Common operations in base `SortAlgorithm` class
- **Functional Programming**: Lambda-based predicates for searching and filtering

## Future Enhancements

- Additional sorting algorithms (Quick Sort, Merge Sort, Heap Sort)
- Iterator support for STL compatibility
- Move semantics for better performance
- Parallel sorting implementations
- Advanced data structures (Binary Search Tree, Graph representations)
- Comparison with STL containers

## Contributing

Contributions are welcome! Please ensure:

1. All tests pass
2. New features include unit tests
3. Code follows the existing style
4. Benchmark regressions are documented

## License

[Include your license information here]

## Author

Project by seitz-dev

## Related Projects

- For production code, consider using `std::vector<T>` from the C++ Standard Library
- This project is primarily educational, demonstrating data structure implementation and algorithmic patterns

---

**Note**: This library is designed for educational purposes and to demonstrate fundamental data structures and algorithms. For production systems, it's recommended to use battle-tested containers from the C++ Standard Library such as `std::vector<T>`, `std::list<T>`, and STL sorting functions.
