#ifndef __KNN_HPP__
#define __KNN_HPP__

#include <vector>
#include "data.hpp"

class knn
{
    int k;
    std::vector<Data *> *neighbours;
    std::vector<Data *> *trainingData;
    std::vector<Data *> *testData;
    std::vector<Data *> *validationData;

public:
    knn(int k);
    knn();
    ~knn();
    int getK();

    void findKnearest(Data *queryPoint);
    void setTrainingData(std::vector<Data *> *vect);
    void setTestData(std::vector<Data *> *vect);
    void setValidationData(std::vector<Data *> *vect);
    void setK(int k);

    int predict();
    double calculateDistance(Data *queryPoint, Data *input);
    double validatePerformance();
    double testPerformance();
};

#endif // __KNN_HPP__