#include "data.hpp"

Data::Data()
{
    this->featureVector = new std::vector<uint8_t>;
}

Data::~Data()
{
}

void Data::setFeatureVector(std::vector<uint8_t> *featureVector)
{
    this->featureVector = featureVector;
}
void Data::appendToFeatureVector(uint8_t val)
{
    this->featureVector->push_back(val);
}
void Data::setLabel(uint8_t label)
{
    this->label = label;
}
void Data::setEnumeratedLabel(int enumLabel)
{
    this->enumLabel = enumLabel;
}

void Data::setDistance(double val)
{
    this->distance = val;
}

int Data::getFeatureVectorSize()
{
    return this->featureVector->size();
}
uint8_t Data::getLabel()
{
    return label;
}
int Data::getEnumeratedLabel()
{
    return enumLabel;
}

std::vector<uint8_t> *Data::getFeatureVector()
{
    return this->featureVector;
}
