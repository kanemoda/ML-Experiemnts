#include "common.hpp"

void commonData::setTrainingData(std::vector<Data *> *trainingData)
{
    this->trainingData = trainingData;
}
void commonData::setTestData(std::vector<Data *> *testData)
{
    this->testData = testData;
}
void commonData::setValidationData(std::vector<Data *> *validationData)
{
    this->validationData = validationData;
}