#ifndef DYNAMICARRAYS_LIST_H
#define DYNAMICARRAYS_LIST_H
#include <functional>
#include <optional>
#include <sstream>
#include <stdexcept>

#include "sorting/parser/ValueSortParser.h"

template<typename T>
class SortAlgorithm;

template<typename T>
class List {
    T *arr;
    int count;
    int capacity;

    void resize(int);

    void reduce();

    /**
     * Provides a getter for indexes outside the List's current count, if the capacity allows it.
     * @param index The index to be retrieved
     * @return The array's value at the index.
     */
    T access(int index) {
        if (index < 0 || index >= capacity) {
            throw std::out_of_range("Index out of range");
        }

        return arr[index];
    }

public:
    List(const int size = 1) : arr(new T[size]), count(0), capacity(size) {
    }

    List(const T *array, const int size) : arr(new T[size]), count(static_cast<int>(size)),
                                           capacity(static_cast<int>(size)) {
        for (size_t i = 0; i < size; ++i) {
            arr[i] = array[i];
        }
    }

    List(std::initializer_list<T> array) : arr(new T[array.size()]), count(array.size()), capacity(array.size()) {
        int i = 0;
        for (const T &val: array) {
            arr[i++] = val;
        }
    }

    T &operator[](int index) {
        if (index < 0 || index >= count)
            throw std::out_of_range("Index out of range");
        return arr[index];
    }

    operator std::string() const {
        return toString();
    }

    bool operator==(List<T> &otherList) const {
        if (otherList.getCount() != getCount()) {
            return false;
        }

        for (int i = 0; i < otherList.getCount(); i++) {
            if (otherList[i] != arr[i]) {
                return false;
            }
        }

        return true;
    }

    /**
     * Adds an item to the end of an array.
     * @param item Item to be added
     */
    void add(T item);

    /**
     * Returns the number of elements in the list.
     * @return Number of elements in list
    */
    int getCount() const;

    /**
     * Returns the total allocated size of the list
     * @return The current allocated size of the list
     */
    int getSize() const;

    /**
     * Finds the first element matching the condition and returns its value.
     * @return A match, if found, otherwise no value.
     */
    std::optional<T> findFirst(std::function<bool(T)>);

    /**
     * Finds the first element's index matching the condition, returning the index.
     * @return The index of the first match found, otherwise, no value.
     */
    std::optional<int> findIndex(std::function<bool(T)>);

    /**
     * Finds all elements in an array and returns a new filtered list.
     * @return A new filtered list with all elements matching the condition provided.
     */
    List<T> find(std::function<bool(T)>);

    /**
     * Returns a clone of the list.
     * @return A clone of the list.
     */
    List<T> copy();

    List<T> sort(const SortAlgorithm<T> &, const ValueSortParser<T> &);

    /**
     * Inserts a value at the specified index.
     */
    void insertAt(T, int);

    /**
     * Deletes a value at the specified index.
     */
    void deleteAt(int);

    T *toArray();

    List<T> reverse();

    std::string toString() {
        std::stringstream ss;
        ss << "[";

        for (int i = 0; i < getCount(); i++) {
            ss << arr[i];
            if ((i + 1) != getCount()) {
                ss << ", ";
            }
        }

        ss << "]";
        return ss.str();
    }
};


#endif //DYNAMICARRAYS_LIST_H
