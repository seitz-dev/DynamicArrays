#include "../../include/models/List.h"
#include <optional>

#include "../../include/models/sorting/parser/ValueSortParser.h"

template<typename T>
void List<T>::add(T item) {
    if (count >= capacity) {
        resize(getSize() * 2);
    }

    arr[count++] = item;
}

template<typename T>
int List<T>::getCount() const {
    return count;
}

template<typename T>
int List<T>::getSize() const {
    return capacity;
}

template<typename T>
std::optional<T> List<T>::findFirst(std::function<bool(T)> predicate) {
    for (int i = 0; i < getCount(); i++) {
        if (predicate(arr[i])) {
            return arr[i];
        }
    }

    return std::nullopt;
}

template<typename T>
std::optional<int> List<T>::findIndex(std::function<bool(T)> predicate) {
    for (int i = 0; i < getCount(); i++) {
        if (predicate(arr[i])) {
            return i;
        }
    }

    return std::nullopt;
}

template<typename T>
void List<T>::deleteAt(const int index) {
    resize(capacity + 1);

    List listCopy = copy();
    for (int i = index; i < count; i++) {
        arr[i] = access(i + 1);
    }

    count--;
    resize(capacity - 1);
}

template<typename T>
T *List<T>::toArray() {
    T array[count] = {};

    for (int i = 0; i < count; i++) {
        array[i] = arr[i];
    }

    return array;
}

template<typename T>
List<T> List<T>::reverse() {
    auto clone = copy();

    for (int i = 0; i < clone.getCount(); i++) {
        const auto length = getCount() - 1;
        auto value = arr[length - i];
        clone[i] = value;
    }

    return clone;
}

template<typename T>
List<T> List<T>::find(std::function<bool(T)> predicate) {
    List filteredList;

    for (int i = 0; i < getCount(); i++) {
        if (predicate(arr[i])) {
            filteredList.add(arr[i]);
        }
    }

    return filteredList;
}

template<typename T>
List<T> List<T>::copy() {
    List listCopy(capacity);

    for (int i = 0; i < count; i++) {
        listCopy.add(arr[i]);
    }

    return listCopy;
}

template<typename T>
List<T> List<T>::sort(const SortAlgorithm<T> &algorithm, const ValueSortParser<T> &sortParser) {
    auto clone = copy();
    clone.reduce();

    for (int i = 0; i < clone.getCount(); i++) {
        clone[i] = sortParser.determineNumericalValue(clone[i]);
    }

    return algorithm.sort(clone);
}

template<typename T>
void List<T>::insertAt(T value, int index) {
    resize(capacity + 2);

    List listCopy = copy();

    for (int i = index; i < count; i++) {
        arr[i + 1] = listCopy[i];
    }

    arr[index] = value;
    count++;
}

template<typename T>
void List<T>::resize(const int newSize) {
    capacity = newSize;
    T *clone = new T[capacity];

    // clone
    for (int i = 0; i < count; i++) {
        clone[i] = arr[i];
    }

    delete[] arr;
    arr = clone;
}

template<typename T>
void List<T>::reduce() {
    resize(count);
}
