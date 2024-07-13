#ifndef __KNN_HPP__
#define __KNN_HPP__

#include "common.hpp"

class knn : public commonData
{
    int k;
    std::vector<Data *> *neighbours;

public:
    knn(int k);
    knn();
    ~knn();
    int getK();

    void findKnearest(Data *queryPoint);
    void setK(int k);

    int predict();
    double calculateDistance(Data *queryPoint, Data *input);
    double validatePerformance();
    double testPerformance();
};

#endif // __KNN_HPP__
