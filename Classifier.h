#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "DSString.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <iomanip>

class Classifier
{
private:
    std::map<DSString, int> trainingMap;
    std::map<DSString, bool> trainingMap2;
    std::map<DSString, bool> testingMap;
    std::vector<DSString> testingVector;
    std::vector<DSString> falseVector;
    std::vector<DSString> stopWordsVector;

public:
    Classifier();
    void readTrainingFile(char *);
    void training(DSString, DSString);
    void readTestingFile(char *);
    void readCheckingFile(char *);
    void test(DSString, DSString);
    void results(char *);
    void accuracy(char *);
};
#endif
