#pragma once
template<typename T> class List;

template<typename T>
class SortAlgorithm {
public:
    virtual List<T> sort(List<T>& list) const = 0;
    virtual ~SortAlgorithm() = default;
};
