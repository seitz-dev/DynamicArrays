#pragma once
#include "SortAlgorithm.h"
#include "models/List.h"

class SelectionSortAlgorithm : public SortAlgorithm<int> {
public:
    List<int> sort(List<int> &list) const override;
};
