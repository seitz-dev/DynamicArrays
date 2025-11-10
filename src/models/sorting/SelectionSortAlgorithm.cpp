#include "models/sorting/SelectionSortAlgorithm.h"
#include "models/List.h"

List<int> SelectionSortAlgorithm::sort(List<int> &list) const {
    auto swapIndex = list.getCount() - 1;
    auto highestNumberIndex = 0;

    while (swapIndex > 0) {
        for (int i = 0; i < swapIndex + 1; i++) {
            if (list[i] > list[highestNumberIndex]) {
                highestNumberIndex = i;
            }
        }

        list.swap(highestNumberIndex, swapIndex);
        swapIndex--;
        highestNumberIndex = 0;
    }

    return list;
}
