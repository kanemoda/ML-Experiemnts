#include "kmeans.hpp"

kmeans::kmeans(int k)
{
    numClusters = k;
    clusters = new std::vector<cluster_t *>;
    usedIndexes = new std::unordered_set<int>;
}
void kmeans::initClusters()
{
    for (int i = 0; i < numClusters; i++)
    {
        int index = (rand() % trainingData->size());
        while (usedIndexes->find(index) != usedIndexes->end())
        {
            index = (rand() % trainingData->size());
        }
        clusters->push_back(new cluster(trainingData->at(index)));
        usedIndexes->insert(index);
    }
}
void kmeans::initClustersForEachClass()
{
    std::unordered_set<int> classesUsed;
    for (int i = 0; i < trainingData->size(); i++)
    {
        if (classesUsed.find(trainingData->at(i)->getLabel()) == classesUsed.end())
        {
            clusters->push_back(new cluster_t(trainingData->at(i)));
            classesUsed.insert(trainingData->at(i)->getLabel());
            usedIndexes->insert(i);
        }
    }
}
void kmeans::train()
{
    int index = 0;
    while (usedIndexes->size() < trainingData->size())
    {
        while (usedIndexes->find(index) != usedIndexes->end())
        {
            index++;
        }
        double minDist = std::numeric_limits<double>::max();
        int bestCluster = 0;
        for (int j = 0; j < clusters->size(); j++)
        {
            double currentDist = euclideadDistance(clusters->at(j)->centroid, trainingData->at(index));
            if (currentDist < minDist)
            {
                minDist = currentDist;
                bestCluster = j;
            }
        }
        clusters->at(bestCluster)->addToCluster(trainingData->at(index));
        usedIndexes->insert(index);
    }
}
double kmeans::euclideadDistance(std::vector<double> *centroid, Data *point)
{
    double dist = 0.0;
    for (int i = 0; i < centroid->size(); i++)
    {
        dist += pow(centroid->at(i) - point->getFeatureVector()->at(i), 2);
    }
    return sqrt(dist);
}
double kmeans::validate()
{
    double numCorrect = 0.0;
    for (auto queryPoint : *validationData)
    {
        double minDist = std::numeric_limits<double>::max();
        int bestCluster = 0;
        for (int j = 0; j < clusters->size(); j++)
        {
            double currentDist = euclideadDistance(clusters->at(j)->centroid, queryPoint);
            if (currentDist < minDist)
            {
                minDist = currentDist;
                bestCluster = j;
            }
        }
        if (clusters->at(bestCluster)->mostFrequentClass == queryPoint->getLabel())
        {
            numCorrect++;
        }
    }
    return 100.0 * (numCorrect / (double)validationData->size());
}
double kmeans::test()
{
    double numCorrect = 0.0;
    for (auto queryPoint : *testData)
    {
        double minDist = std::numeric_limits<double>::max();
        int bestCluster = 0;
        for (int j = 0; j < clusters->size(); j++)
        {
            double currentDist = euclideadDistance(clusters->at(j)->centroid, queryPoint);
            if (currentDist < minDist)
            {
                minDist = currentDist;
                bestCluster = j;
            }
        }
        if (clusters->at(bestCluster)->mostFrequentClass == queryPoint->getLabel())
        {
            numCorrect++;
        }
    }
    return 100.0 * (numCorrect / (double)testData->size());
}

int main(int argc, char const *argv[])
{
    DataHandler *dh = new DataHandler();
    dh->readFeatureVector("mnist_data/train-images-idx3-ubyte");
    dh->readFeatureLabels("mnist_data/train-labels-idx1-ubyte");
    dh->splitData();
    dh->countClasses();
    double performance = 0.0;
    double bestPerformance = 0.0;
    int bestK = 1;
    for (int k = dh->getClassCounts(); k < dh->getTrainingData()->size() * 0.1; k++)
    {
        kmeans *km = new kmeans(k);
        km->setTrainingData(dh->getTrainingData());
        km->setTestData(dh->getTestData());
        km->setValidationData(dh->getValidationData());
        km->initClusters();
        km->train();
        performance = km->validate();
        printf("Current Performance at K = %d: %.4f\n", k, performance);
        if (performance > bestPerformance)
        {
            bestPerformance = performance;
            bestK = k;
        }
    }
    kmeans *km = new kmeans(bestK);
    km->setTrainingData(dh->getTrainingData());
    km->setTestData(dh->getTestData());
    km->setValidationData(dh->getValidationData());
    km->initClusters();
    km->test();
    performance = km->test();
    printf("Tested Performance at K = %d: %.4f\n", bestK, performance);

    return 0;
}
