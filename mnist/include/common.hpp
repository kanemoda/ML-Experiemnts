#ifndef __COMMON_HPP__
#define __COMMON_HPP__
#include "data.hpp"
#include <vector>

class commonData
{
protected:
    std::vector<Data *> *trainingData;
    std::vector<Data *> *testData;
    std::vector<Data *> *validationData;

public:
    void setTrainingData(std::vector<Data *> *vect);
    void setTestData(std::vector<Data *> *vect);
    void setValidationData(std::vector<Data *> *vect);
};

#endif //__COMMON_HPP__
