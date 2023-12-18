#include <iostream>
#include <cstdio>
#include <chrono>
#include "DSString.h"
#include "Classifier.h"

int main(int argc, char **argv)
{
    Classifier classifier;
    classifier.readTrainingFile(argv[1]);
    classifier.readTestingFile(argv[2]);
    classifier.readCheckingFile(argv[3]);
    classifier.results(argv[4]);
    classifier.accuracy(argv[5]);

    argc = 0;
    return argc;
}

//     auto startTrain = std::chrono::high_resolution_clock::now();

//     try {
//         classifier.readTrainingFile(argv[1]);
//     }
//     catch (const std::exception& e) {
//         std::cerr << "Training error: " << e.what() << std::endl;
//         return 1;
//     }

//     auto finishTrain = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> elapsedTrain = finishTrain - startTrain;
//     std::cout << "Training elapsed time: " << elapsedTrain.count() << " seconds" << std::endl;
//     auto startTest = std::chrono::high_resolution_clock::now();

//     try {
//         classifier.readTestingFile(argv[2]);
//         classifier.readCheckingFile(argv[3]);
//         classifier.results(argv[4]);
//         classifier.accuracy(argv[5]);
//     }
//     catch (const std::exception& e) {
//         std::cerr << "Testing error: " << e.what() << std::endl;
//         return 1;
//     }

//     auto finishTest = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> elapsedTest = finishTest - startTest;
//     std::cout << "Testing elapsed time: " << elapsedTest.count() << " seconds" << std::endl;

//     return 0;
//}
