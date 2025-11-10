#ifndef DYNAMICARRAYS_INSERTIONSORTALGORITHM_H
#define DYNAMICARRAYS_INSERTIONSORTALGORITHM_H
#include "SortAlgorithm.h"


class InsertionSortAlgorithm : public SortAlgorithm<int> {
public:
    List<int> sort(List<int> &list) const override;
};


#endif //DYNAMICARRAYS_INSERTIONSORTALGORITHM_H
