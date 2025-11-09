#ifndef DYNAMICARRAYS_VALUESORTPARSER_H
#define DYNAMICARRAYS_VALUESORTPARSER_H


template<typename T>
class ValueSortParser {
public:
    virtual ~ValueSortParser() = default;
    virtual int determineNumericalValue(T) const = 0;
};


#endif //DYNAMICARRAYS_VALUESORTPARSER_H