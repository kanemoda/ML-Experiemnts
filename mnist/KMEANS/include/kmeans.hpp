#ifndef __KMEANS_HPP__
#define __KMEANS_HPP__

#include "common.hpp"
#include <unordered_set>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <map>
#include "data_handler.hpp"

typedef struct cluster
{

    std::vector<double> *centroid;
    std::vector<Data *> *clusterPoints;
    std::map<int, int> classCounts;
    int mostFrequentClass;

    cluster(Data *initialPoint)
    {
        centroid = new std::vector<double>;
        clusterPoints = new std::vector<Data *>;

        for (auto value : *(initialPoint->getFeatureVector()))
        {
            centroid->push_back(value);
        }
        clusterPoints->push_back(initialPoint);
        classCounts[initialPoint->getLabel()] = 1;
        mostFrequentClass = initialPoint->getLabel();
    }

    void addToCluster(Data *point)
    {
        int previousSize = clusterPoints->size();
        clusterPoints->push_back(point);
        for (int i = 0; i < centroid->size() - 1; i++)
        {
            double value = centroid->at(i);
            value *= previousSize;
            value += point->getFeatureVector()->at(i);
            value /= (double)clusterPoints->size();
            centroid->at(i) = value;
        }

        if (classCounts.find(point->getLabel()) == classCounts.end())
        {
            classCounts[point->getLabel()] = 1;
        }
        else
        {
            classCounts[point->getLabel()]++;
        }
        setMostFrequentClass();
    }

    void setMostFrequentClass()
    {
        int bestClass;
        int freq = 0;
        for (auto kv : classCounts)
        {
            if (kv.second > freq)
            {
                freq = kv.second;
                bestClass = kv.first;
            }
        }
        mostFrequentClass = bestClass;
    }

} cluster_t;

class kmeans : public commonData
{
    int numClusters;
    std::vector<cluster_t *> *clusters;
    std::unordered_set<int> *usedIndexes;

public:
    kmeans(int k);
    void initClusters();
    void initClustersForEachClass();
    void train();
    double euclideadDistance(std::vector<double> *, Data *);
    double validate();
    double test();
};

#endif // __KMEANS_HPP__