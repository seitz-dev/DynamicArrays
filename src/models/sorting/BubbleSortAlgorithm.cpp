#include "../../../include/models/sorting/BubbleSortAlgorithm.h"
#include "./models/List.h"

List<int> BubbleSortAlgorithm::sort(List<int> &list) const {
    auto sorted = false;
    int lastIndexValue = list.getCount() - 1;

    while (!sorted) {
        sorted = true;
        for (int i = 0; i < lastIndexValue; i++) {
            if (list[i] > list[i + 1] && i + 1 <= lastIndexValue) {
                // swap
                list.swap(i, i + 1);
                sorted = false;
            }
        }

        lastIndexValue--;
    }

    return list;
}
