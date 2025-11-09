#ifndef DYNAMICARRAYS_INTSORTPARSER_H
#define DYNAMICARRAYS_INTSORTPARSER_H
#include "ValueSortParser.h"


class IntSortParser : public ValueSortParser<int> {
public:
    int determineNumericalValue(int val) const override {
        return val;
    }
};


#endif //DYNAMICARRAYS_INTSORTPARSER_H
