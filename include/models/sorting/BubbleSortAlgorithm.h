#ifndef DYNAMICARRAYS_BUBBLESORTALGORITHM_H
#define DYNAMICARRAYS_BUBBLESORTALGORITHM_H
#include "SortAlgorithm.h"
#include "models/List.h"

class BubbleSortAlgorithm final : public SortAlgorithm<int> {
public:
    List<int> sort(List<int> &list) const override;
};


#endif //DYNAMICARRAYS_BUBBLESORTALGORITHM_H
