#ifndef __DATA_HPP__
#define __DATA_HPP__

#include <vector>
#include <stdint.h>
#include <stdio.h>

class Data
{
    std::vector<uint8_t> *featureVector;
    uint8_t label;
    int enumLabel; // A -> 1 , B -> 2
    double distance;

public:
    Data();
    ~Data();
    void setFeatureVector(std::vector<uint8_t> *vect);
    void appendToFeatureVector(uint8_t);
    void setLabel(uint8_t);
    void setEnumeratedLabel(int);
    void setDistance(double val);

    int getFeatureVectorSize();
    uint8_t getLabel();
    int getEnumeratedLabel();
    std::vector<uint8_t> *getFeatureVector();
};

#endif // __DATA_HPP__
