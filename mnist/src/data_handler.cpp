#include "data_handler.hpp"

DataHandler::DataHandler()
{
    this->dataArray = new std::vector<Data *>;
    this->testData = new std::vector<Data *>;
    this->trainingData = new std::vector<Data *>;
    this->validationData = new std::vector<Data *>;
}
DataHandler::~DataHandler()
{
    // FREE Dynamically Aloocated stuff
}

void DataHandler::readFeatureVector(std::string path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + path);
    }

    std::vector<uint32_t> header(4);
    unsigned char bytes[4];

    for (int i = 0; i < 4; ++i)
    {
        if (!file.read(reinterpret_cast<char *>(bytes), sizeof(bytes)))
        {
            throw std::runtime_error("Failed to read header from file");
        }
        header[i] = convertToLittleEndian(bytes);
    }

    std::cout << "Done getting Input File header!" << std::endl;
    int imageSize = header[2] * header[3];

    for (int i = 0; i < header[1]; i++)
    {
        Data *d = new Data();
        uint8_t element[1];
        for (int j = 0; j < imageSize; j++)
        {
            if (!file.read(reinterpret_cast<char *>(element), sizeof(element)))
            {
                throw std::runtime_error("Failed to read data from file");
            }
            d->appendToFeatureVector(element[0]);
        }
        dataArray->push_back(d);
    }
    std::cout << "Successfully read and stored " << dataArray->size() << " feature vectors.\n"
              << std::endl;
}

void DataHandler::readFeatureLabels(std::string path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + path);
    }

    std::vector<uint32_t> header(2);
    unsigned char bytes[4];

    for (int i = 0; i < 2; ++i)
    {
        if (!file.read(reinterpret_cast<char *>(bytes), sizeof(bytes)))
        {
            throw std::runtime_error("Failed to read header from file");
        }
        header[i] = convertToLittleEndian(bytes);
    }

    std::cout << "Done getting Label File header!" << std::endl;

    for (int i = 0; i < header[1]; i++)
    {
        uint8_t element[1];
        if (!file.read(reinterpret_cast<char *>(element), sizeof(element)))
        {
            throw std::runtime_error("Failed to read data from file");
        }
        dataArray->at(i)->setLabel(element[0]);
    }
    std::cout << "Successfully read and stored labels.\n"
              << std::endl;
}
void DataHandler::splitData()
{
    std::unordered_set<int> usedIndexes;
    int trainSize = dataArray->size() * TRAIN_SET_PERCENT;
    int testSize = dataArray->size() * TEST_SET_PERCENT;
    int validSize = dataArray->size() * VALIDATION_PERCENT;

    // Train Data

    int count = 0;
    while (count < trainSize)
    {
        int randIndex = rand() % dataArray->size();

        if (usedIndexes.find(randIndex) == usedIndexes.end())
        {
            trainingData->push_back(dataArray->at(randIndex));
            usedIndexes.insert(randIndex);
            count++;
        }
    }

    // Test Data

    count = 0;
    while (count < testSize)
    {
        int randIndex = rand() % dataArray->size();

        if (usedIndexes.find(randIndex) == usedIndexes.end())
        {
            testData->push_back(dataArray->at(randIndex));
            usedIndexes.insert(randIndex);
            count++;
        }
    }

    // Validation Data

    count = 0;
    while (count < validSize)
    {
        int randIndex = rand() % dataArray->size();

        if (usedIndexes.find(randIndex) == usedIndexes.end())
        {
            validationData->push_back(dataArray->at(randIndex));
            usedIndexes.insert(randIndex);
            count++;
        }
    }

    std::cout << "Training Data Size: " << trainingData->size() << std::endl;
    std::cout << "Test Data Size: " << testData->size() << std::endl;
    std::cout << "Validation Data Size: " << validationData->size() << std::endl;
}
void DataHandler::countClasses()
{
    int count = 0;
    for (unsigned i = 0; i < dataArray->size(); i++)
    {
        if (classMap.find(dataArray->at(i)->getLabel()) == classMap.end())
        {
            classMap[dataArray->at(i)->getLabel()] = count;
            dataArray->at(i)->setEnumeratedLabel(count);
            count++;
        }
    }

    numClasses = count;
    std::cout << "Successfully Extracted " << numClasses << " Unique Classes" << std::endl;
}

uint32_t DataHandler::convertToLittleEndian(const unsigned char *bytes)
{
    return (static_cast<uint32_t>(bytes[0]) << 24) |
           (static_cast<uint32_t>(bytes[1]) << 16) |
           (static_cast<uint32_t>(bytes[2]) << 8) |
           (static_cast<uint32_t>(bytes[3]));
}

int DataHandler::getClassCounts()
{
    return numClasses;
}

std::vector<Data *> *DataHandler::getTrainingData()
{
    return trainingData;
}
std::vector<Data *> *DataHandler::getTestData()
{
    return testData;
}
std::vector<Data *> *DataHandler::getValidationData()
{
    return validationData;
}
