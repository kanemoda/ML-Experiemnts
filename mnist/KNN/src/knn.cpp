#include "knn.hpp"
#include <cmath>
#include <limits>
#include <map>
#include <stdint.h>
#include "data_handler.hpp"
#include <iostream>

knn::knn(int k)
{
    this->k = k;
}
knn::knn()
{
    // Nothing to do
}
knn::~knn()
{
    // Nothing to do
}
int knn::getK()
{
    return this->k;
}

void knn::findKnearest(Data *queryPoint)
{
    neighbours = new std::vector<Data *>;

    double min = std::numeric_limits<double>::max();
    double previousMin = min;
    int index = 0;
    for (int i = 0; i < k; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j < trainingData->size(); j++)
            {
                double distance = calculateDistance(queryPoint, trainingData->at(j));
                trainingData->at(j)->setDistance(distance);

                if (distance < min)
                {
                    min = distance;
                    index = j;
                }
            }
            neighbours->push_back(trainingData->at(index));
            previousMin = min;
            min = std::numeric_limits<double>::max();
        }
        else
        {
            for (int j = 0; j < trainingData->size(); j++)
            {
                double distance = calculateDistance(queryPoint, trainingData->at(j));
                if (distance > previousMin && distance < min)
                {
                    min = distance;
                    index = j;
                }
            }
            neighbours->push_back(trainingData->at(index));
            previousMin = min;
            min = std::numeric_limits<double>::max();
        }
    }
}

void knn::setK(int k)
{
    this->k = k;
}

int knn::predict()
{
    std::map<uint8_t, int> classFreq;
    for (int i = 0; i < neighbours->size(); i++)
    {
        if (classFreq.find(neighbours->at(i)->getLabel()) == classFreq.end())
        {
            classFreq[neighbours->at(i)->getLabel()] = 1;
        }
        else
        {
            classFreq[neighbours->at(i)->getLabel()]++;
        }
    }

    int best = 0;
    int max = 0;
    for (auto kv : classFreq)
    {
        if (kv.second > max)
        {
            max = kv.second;
            best = kv.first;
        }
    }
    delete neighbours;
    return best;
}
double knn::calculateDistance(Data *queryPoint, Data *input)
{
    double distance = 0.0;

    if (queryPoint->getFeatureVectorSize() != input->getFeatureVectorSize())
    {
        std::cout << "Error: Vector Size Mismatch.\n"
                  << std::endl;
        return std::numeric_limits<double>::max(); // Return a large value to indicate error
    }

#ifdef EUCLID
    for (unsigned int i = 0; i < queryPoint->getFeatureVectorSize(); i++)
    {
        distance += pow(queryPoint->getFeatureVector()->at(i) - input->getFeatureVector()->at(i), 2);
    }
    distance = sqrt(distance);

#elif defined(MANHATTAN)
    for (unsigned int i = 0; i < queryPoint->getFeatureVectorSize(); i++)
    {
        distance += fabs(queryPoint->getFeatureVector()->at(i) - input->getFeatureVector()->at(i));
    }

#else
    std::cout << "Error: No distance metric defined.\n"
              << std::endl;
    return std::numeric_limits<double>::max(); // Return a large value to indicate error

#endif

    return distance;
}

double knn::validatePerformance()
{
    double currentPerformance = 0;
    int count = 0;
    int dataIndex = 0;
    for (Data *queryPoint : *validationData)
    {
        findKnearest(queryPoint);
        int prediction = predict();
        printf("%d -> %d\n", prediction, queryPoint->getLabel());
        if (prediction == queryPoint->getLabel())
        {
            count++;
        }
        dataIndex++;
        std::cout << "Current Performance = " << ((double)count * 100.0) / ((double)dataIndex) << std::endl;
    }
    currentPerformance = ((double)count * 100.0) / ((double)validationData->size());
    std::cout << "Validation Performance or K: = " << this->k << currentPerformance << std::endl;
    return currentPerformance;
}
double knn::testPerformance()
{
    double currentPerformance = 0;
    int count = 0;
    for (Data *queryPoint : *testData)
    {
        findKnearest(queryPoint);
        int prediction = predict();
        if (prediction == queryPoint->getLabel())
        {
            count++;
        }
    }
    currentPerformance = ((double)count * 100.0) / ((double)testData->size());
    std::cout << "Tested Performance = " << currentPerformance << std::endl;
    return currentPerformance;
}

int main(int argc, char const *argv[])
{
    DataHandler *dh = new DataHandler();
    dh->readFeatureVector("mnist_data/train-images-idx3-ubyte");
    dh->readFeatureLabels("mnist_data/train-labels-idx1-ubyte");
    dh->splitData();
    dh->countClasses();
    knn *knearest = new knn();
    knearest->setTrainingData(dh->getTrainingData());
    knearest->setTestData(dh->getTestData());
    knearest->setValidationData(dh->getValidationData());
    double performace = 0;
    double bestPerformance = 0;
    int bestK = 1;
    for (int i = 1; i <= 4; i++)
    {
        if (i == 1)
        {
            knearest->setK(i);
            performace = knearest->validatePerformance();
            bestPerformance = performace;
        }
        else
        {
            knearest->setK(i);
            performace = knearest->validatePerformance();
            if (performace > bestPerformance)
            {
                bestPerformance = performace;
                bestK = knearest->getK();
            }
        }
    }
    knearest->setK(bestK);
    knearest->testPerformance();
    return 0;
}
