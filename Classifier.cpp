#include "Classifier.h"

Classifier::Classifier()
{
    std::ifstream stopWordsFile;
    stopWordsFile.open("../stopwords.csv");
    if (!stopWordsFile.is_open())
    {
        std::cout << "Error occured while reading stopwords file" << std::endl;
    }
    char buffer[5000];
    while (!stopWordsFile.eof())
    {
        stopWordsFile.getline(buffer, 5000);
        DSString stopWords = buffer;
        stopWordsVector.push_back(stopWords);
    }
    stopWordsFile.close();
}

void Classifier::readTrainingFile(char *fileName1)
{
    // this function reads the training file and send the necessary lines to the training function

    std::ifstream file(fileName1); // opens file

    if (!file.is_open()) // checks to see if the file is open and prints an error statement if it is
    {
        std::cout << "Error occured while reading in training file" << std::endl;
    }
    char buffer[5000];
    file.getline(buffer, 5000); // gets the first line ("header")
    while (!file.eof())         // continues until it reaches the end of the file
    {
        file.getline(buffer, 5000, ',');
        DSString sentiment = buffer; // stores the sentiment as a DSString
        if (sentiment.length() == 0)
        {
            break;
        }
        file.getline(buffer, 5000, ','); // unnecessary column
        file.getline(buffer, 5000, ','); // unnecessary column
        file.getline(buffer, 5000, ','); // unnecessary column
        file.getline(buffer, 5000, ','); // unnecessary column
        file.getline(buffer, 5000);
        DSString tweet = buffer; // stores the tweet as a DSString
        training(tweet, sentiment);
    }
    file.close(); // closes the file

    for (const auto &itr : trainingMap) // reads through the map
    {
        if (itr.second >= 1) // if the value is higher then or equal to 1, the word is positive
        {
            trainingMap2[itr.first] = true;
        }
        else if (itr.second < -1) // if the value is less then -1, the word is negative
        {
            trainingMap2[itr.first] = false;
        }
    }
}

void Classifier::training(DSString tweet, DSString sentiment)
{
    // this function tokenizes and checks and if needed adds tweets to the training map
    // it also increments the map by 1 or -1 based on it's sentiment

    tweet = tweet.toLower();                                  // makes the word all lower case to take all versions into account
    std::vector<DSString> tweetVector = tweet.tokenization(); // creates a vector for tokenized tweets
    for (size_t i = 0; i < tweetVector.size(); i++)
    {
        for (size_t j = 0; j < stopWordsVector.size(); j++)
        {
            if (tweetVector[i] == stopWordsVector[j])
            {
                continue;
            }
        }
        if (trainingMap.find(tweetVector[i]) == trainingMap.end())
        { // checks to see if the tweet is found and if not adds it to the end of the map
            if (sentiment[0] == '4')
            {
                trainingMap[tweetVector[i]] = 1; // adds one to the map value to account for the positive sentiment
            }
            else
            {
                trainingMap[tweetVector[i]] = -1; // if not positive then it subtracts one
            }
        }
        else
        { // else statement for words that are already in the map
            if (sentiment[0] == '4')
            {
                trainingMap[tweetVector[i]] += 1; // adds one to the map value to account for the positive sentiment
            }
            else
            {
                trainingMap[tweetVector[i]] += -1; // if not positive then it subtracts one
            }
        }
    }
}

void Classifier::readTestingFile(char *fileName2)
{
    // this function reads in the testing file and stores the necessary lines

    char buffer[5000];
    std::ifstream file(fileName2); // opens file

    if (!file.is_open())
    {
        std::cout << "Error occured while reading in testing file" << std::endl;
    }

    file.getline(buffer, 5000); // gets the first line ("header")
    while (!file.eof())
    {
        file.getline(buffer, 5000, ',');
        DSString id = buffer; // stores the id column as a DSString
        if (id.length() == 0)
        {
            break;
        }
        file.getline(buffer, 5000, ','); // unnecessary column
        file.getline(buffer, 5000, ','); // unnecessary column
        file.getline(buffer, 5000, ','); // unnecessary column
        file.getline(buffer, 5000);
        DSString tweet = buffer; // stores the tweet as a DSString
        test(tweet, id);
    }
    file.close();
}

void Classifier::test(DSString tweet, DSString id)
{
    int count = 0;
    tweet = tweet.toLower();                                    // makes the word all lower case to take all versions into account
    std::vector<DSString> testingVector = tweet.tokenization(); // creates a vector for tokenized tweets
    for (size_t i = 0; i < testingVector.size(); i++)
    {
        if (trainingMap2.find(testingVector[i]) != trainingMap2.end())
        {
            if (trainingMap2[testingVector[i]])
            {
                count++;
            }
            else
            {
                count--;
            }
        }
    }
    if (count >= 0)
    {
        testingMap[id] = true;
    }
    else if (count < 0)
    {
        testingMap[id] = false;
    }
}

void Classifier::readCheckingFile(char *fileName3)
{
    // this function reads in the final file and stores the lines

    char buffer[5000];
    std::ifstream file(fileName3); // opens file

    if (!file.is_open())
    {
        std::cout << "Error occured while reading in checking file" << std::endl;
    }

    file.getline(buffer, 5000); // gets the first line ("header")
    while (!file.eof())
    {
        file.getline(buffer, 5000, ',');
        DSString sentiment = buffer; // saves the sentiment as a DSString
        if (sentiment.length() == 0)
        {
            break;
        }
        file.getline(buffer, 5000);
        DSString id = buffer; // saves the id as a DSString

        bool idSentiment = testingMap[id];
        if (!(((sentiment == "0") && (idSentiment == false)) || ((sentiment == "4") && (idSentiment == true))))
        {
            falseVector.push_back(id);
        }
    }
    file.close();
    //     results(resultsFile);
    //     accuracy(char *accuracyFile);
}

void Classifier::results(char *resultsFile)
{
    // this function outputs the classifier's results for all tweets in the testing dataset in the same format as the sentiment file

    std::ofstream results(resultsFile);
    for (const auto &itr : testingMap)
    {
        if (itr.second == true)
        {
            results << 4 << ", ";
        }
        else if (itr.second == false)
        {
            results << 0 << ", ";
        }
        results << itr.first << std::endl;
    }
}

void Classifier::accuracy(char *accuracyFile)
{
    // this function outputs the accuracy on the first line
    // the remaining lines output each tweet that my alogrithm incorrectly classified, the ground truth, and the tweet id

    std::ofstream accuracy(accuracyFile);
    double accuracyNumber = (double)(testingMap.size() - falseVector.size()) / testingMap.size();
    accuracy << std::setprecision(3) << accuracyNumber << std::endl;

    for (size_t i = 0; i < falseVector.size(); i++)
    {
        bool idSentiment = testingMap[falseVector[i]];
        if (idSentiment == false)
        {
            accuracy << "0, 4, " << falseVector[i] << std::endl;
        }
        else if (idSentiment == true)
        {
            accuracy << "4, 0, " << falseVector[i] << std::endl;
        }
    }
}
