#ifndef __DATA_HANDLER_HPP__
#define __DATA_HANDLER_HPP__

#define TRAIN_SET_PERCENT 0.75
#define TEST_SET_PERCENT 0.20
#define VALIDATION_PERCENT 0.05

#include <fstream>
#include <stdint.h>
#include "data.hpp"
#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include <iostream>

class DataHandler
{
    std::vector<Data *> *dataArray;
    std::vector<Data *> *trainingData;
    std::vector<Data *> *testData;
    std::vector<Data *> *validationData;

    int numClasses;
    int featureVector;
    std::map<uint8_t, int> classMap;

public:
    DataHandler();
    ~DataHandler();

    void readFeatureVector(std::string path);
    void readFeatureLabels(std::string path);
    void splitData();
    void countClasses();

    uint32_t convertToLittleEndian(const unsigned char *bytes);

    int getClassCounts();
    std::vector<Data *> *getTrainingData();
    std::vector<Data *> *getTestData();
    std::vector<Data *> *getValidationData();
};

#endif // __DATA_HANDLER_HPP__