#include <iostream>
#include <list>
#include <cmath>
#include <set>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;

class SequenceTermRepetitionAnalysis {

    public :

        bool static IsThereADivisorOtherThanItselfAndOne(int sizeOfPartOfBaseSeq) {
            if(sizeOfPartOfBaseSeq % 2 == 0 && sizeOfPartOfBaseSeq != 2) { return true; }
            else {
                for (int i = 3; i <= sqrt(sizeOfPartOfBaseSeq); i += 2) {
                    if((sizeOfPartOfBaseSeq % i == 0)) return true;
                }
                return false;
            }
        }

        void static GetNumOfPossibleChunksOfPartOfBaseSeq(int sizeOfPartOfBaseSeq, list<int> &NumOfPossibleChunksOfPartOfBaseSeq) {
            if(sizeOfPartOfBaseSeq % 2 == 0) { 
                NumOfPossibleChunksOfPartOfBaseSeq.push_back(2);
                for (int i = 3; i <= sizeOfPartOfBaseSeq/2; i++) {
                    if(sizeOfPartOfBaseSeq % i == 0) { NumOfPossibleChunksOfPartOfBaseSeq.push_back(i); }
                }
            } else {
                    for (int i = 3; i <= sizeOfPartOfBaseSeq/3; i+=2) {
                        if(sizeOfPartOfBaseSeq % i == 0) { NumOfPossibleChunksOfPartOfBaseSeq.push_back(i); }
                    }
            }
            NumOfPossibleChunksOfPartOfBaseSeq.push_back(sizeOfPartOfBaseSeq);
        }

        vector<list<string>> static DivideSequenceIntoChunks (int sizeOfPartOfBaseSeq, int numOfPossibleChunk, list<string> partOfBaseSeq) {
            vector<list<string>> chunksOfPartOfBaseSeq(numOfPossibleChunk);
            auto it = partOfBaseSeq.begin(), end = it;
            int chunkSize = sizeOfPartOfBaseSeq / numOfPossibleChunk;

            for(int i = 0; i < numOfPossibleChunk; i++) {
                advance(end, chunkSize);
                chunksOfPartOfBaseSeq[i].insert(chunksOfPartOfBaseSeq[i].begin(), it, end);
                it = end;
            }

            return chunksOfPartOfBaseSeq;
        }

        // Algorithms

        void static ControlAlgorithmOfChunkOfPartOfBaseSeq1(int sizeOfPartOfBaseSeq, list<string> partOfBaseSeq, int numOfPossibleChunk, list<int> &successfulChunkings,list<int> &unsuccessfulChunkings, int &numOfRepetitiveSeq, int &numOfNonRepetitiveSeq, unordered_map<int, pair<bool, int>>& repetitionControlMap) {

            int chunkSize = sizeOfPartOfBaseSeq / numOfPossibleChunk;
            bool isRepetitive = true;
            if (repetitionControlMap.find(chunkSize) == repetitionControlMap.end()) {
                for (int i = 0; i < chunkSize; i++) {
                    auto it = partOfBaseSeq.begin();
                    advance(it, i);
                    auto nextIt = it;
                    for (int j = 1; j <= numOfPossibleChunk-1; j++) {
                        advance(nextIt, chunkSize);
                        if(!(*it == *nextIt)) {
                            isRepetitive = false;
                            repetitionControlMap[chunkSize] = make_pair(false, 0);  // If it false, second pair is not important..
                            goto end_loop;
                        }
                    }
                }
                repetitionControlMap[chunkSize] = make_pair(true, numOfPossibleChunk);
            } else {
                pair<bool, int>& entry = repetitionControlMap[chunkSize];
                if(entry.first) {
                    for (int i = 0; i < chunkSize; i++) {
                        auto it = partOfBaseSeq.begin();
                        advance(it, i);
                        auto nextIt = it;
                        advance(nextIt, entry.second*chunkSize-chunkSize);
                        for (int j = 1; j <= numOfPossibleChunk-entry.second; j++) {
                            advance(nextIt, chunkSize);
                            if(!(*it == *nextIt)) {
                                isRepetitive = false;
                                entry = make_pair(false, 0);
                                goto end_loop;
                            }
                        }
                    }
                    entry = make_pair(true, numOfPossibleChunk);
                } else {
                    isRepetitive = false;
                    goto end_loop;
                }
            }

            end_loop:
            if(isRepetitive) {
                successfulChunkings.push_back(sizeOfPartOfBaseSeq);
                successfulChunkings.push_back(numOfPossibleChunk);
                numOfRepetitiveSeq++;
            } else {
                unsuccessfulChunkings.push_back(sizeOfPartOfBaseSeq);
                unsuccessfulChunkings.push_back(numOfPossibleChunk);
                numOfNonRepetitiveSeq++;
            }
        }

        void static ControlAlgorithmOfChunkOfPartOfBaseSeq2(int sizeOfPartOfBaseSeq, int numOfPossibleChunk, vector<list<string>> chunksOfPartOfBaseSeq, list<int> &successfulChunkings, list<int> &unsuccessfulChunkings, int &numOfRepetitiveSeq, int &numOfNonRepetitiveSeq) {

            set<list<string>> setOfChunksOfPartOfBaseSeq;
            for(list<string> chunk : chunksOfPartOfBaseSeq) { setOfChunksOfPartOfBaseSeq.insert(chunk); }
            if(setOfChunksOfPartOfBaseSeq.size() == 1) {
                successfulChunkings.push_back(sizeOfPartOfBaseSeq);
                successfulChunkings.push_back(numOfPossibleChunk);
                numOfRepetitiveSeq++;
            } else {  // setOfChunksOfPartOfBaseSeq.size() > 1
                unsuccessfulChunkings.push_back(sizeOfPartOfBaseSeq);
                unsuccessfulChunkings.push_back(numOfPossibleChunk);
                numOfNonRepetitiveSeq++;
            }
        }

        // Enter the sequence you want to test here, starting with the first term.
        list<string> static getBaseSequence() {
            /*
            Enter your sequence with the desired data type (int, double, char, string, etc.).
            Since are not interested in the type of data, whether it repeats or not, it will be converted directly to string type. 
            Because if it repeats in the data type you entered, it will repeat after being converted to string type.
            We are not interested in any calculation, we are interested in whether it repeats or not.
            */

           // Enter the sequence here:
            auto baseSequence = {1,2,3,4,5};

            list<string> stringBaseSequence;
            for (const auto& term : baseSequence) {
                stringBaseSequence.push_back(ConvertSequenceTermToString(term));
            }
            return stringBaseSequence;
        }

    template <typename T>
    string static ConvertSequenceTermToString(const T& data) {
        return to_string(data);
    }
};

class FileManager {

    public:
        static void ControlFile(string fileName, ofstream& writeFile) {
            ifstream readFile(fileName);
            bool isFileExist = readFile.good();
            readFile.close();

            if (isFileExist) writeFile.open(fileName, ios::app);
            else writeFile.open(fileName);
        }
};

class TextManager {

    public:

        string static NoPossibleChunkWarning(int sizeOfPartOfBaseSeq) {
            string noPossibleChunkWarning = "There is no possible chunk for n = " + to_string(sizeOfPartOfBaseSeq) + ".\n" + "Because " + to_string(sizeOfPartOfBaseSeq) + " has no divisors other than itself and the one.\n";
            return noPossibleChunkWarning;
        }

        string static BaseSequenceText(list<string> baseSequence) {
            string baseSequenceText = "";
            for(string term : baseSequence) {
                baseSequenceText += term + " ";
            }
            baseSequenceText += LineForReadability();
            return baseSequenceText;
        }

        string static NumOfPossibleChunksText (int sizeOfPartOfBaseSeq, list<int> numOfPossibleChunksOfPartOfBaseSeq, list<string> partOfBaseSeq) {
            string numOfPossibleChunksText = "";
            numOfPossibleChunksText += "Possible chunk nums for n = " + to_string(sizeOfPartOfBaseSeq) + ": ";
            for(int numOfPossibleChunk : numOfPossibleChunksOfPartOfBaseSeq) { numOfPossibleChunksText += to_string(numOfPossibleChunk) + " "; }
            numOfPossibleChunksText += "\n\n";
            return numOfPossibleChunksText;
        }

        string static PossibleChunksText (int numOfPossibleChunks, vector<list<string>> chunksOfPartOfBaseSeq) {
            string possibleChunksText = "";
            possibleChunksText += "For " + to_string(numOfPossibleChunks) + " chunk:\n/";
            for(list<string> chunk : chunksOfPartOfBaseSeq) { for(string term : chunk) { possibleChunksText += term; } possibleChunksText += "/"; }
            possibleChunksText += "\n";
            return possibleChunksText;
        }

        string static ResultText(int numOfRepetitiveSeq, int numOfNonRepetitiveSeq, list<int> successfulChunkings, list<int> unsuccessfulChunkings) {
            // chunk abbreviation is 'c'
            string result = "Results for: last term is a(n), does not repeats every c terms\n\n";
            auto it = unsuccessfulChunkings.begin();
            int prevIt = *it;
            for (int i = 0; i < unsuccessfulChunkings.size()/2; i ++) {
                if(*it != prevIt) {
                    result += "\n";
                    prevIt = *it;
                }
                result += "n: " + to_string(*it) + " c: " + to_string(*it/(*next(it))) + ", ";
                advance(it, 2);
            }
            result +="\n\nThere is " + to_string(numOfNonRepetitiveSeq) + " non repetitive sequence.\n";
            result += LineForReadability();
            it = successfulChunkings.begin();
            result += "Results for: last term is a(n), repeats every c terms \n";
            for (int i = 0; i < successfulChunkings.size()/2; i ++) {
                if(*it != prevIt) {
                    result += "\n";
                    prevIt = *it;
                }
                result += ", n: " + to_string(*it) + " c: " + to_string(*it/(*next(it))) + ", ";
                advance(it, 2);
            }
            result += "\nThere is " + to_string(numOfRepetitiveSeq) + " repetitive sequence.\n";
            result += LineForReadability();
            return result;
        }

        string static LineForReadability() {
            string lineForReadabilityText = "==================================================\n";
            return lineForReadabilityText;
        }

        // helper methods

        static void WrapText(string text, int maxChar, ofstream &writeFile) {
            istringstream iss(text);
            string line;
            string wrappedLine;

            while (getline(iss, line)) {
                while (line.length() > maxChar) {
                    wrappedLine = line.substr(0, maxChar);
                    writeFile << wrappedLine << endl;
                    line = line.substr(maxChar);
                }
                writeFile << line << endl;
            }
        }

        static string DateText() {
            string date = "";

            time_t now = time(0);
            tm* localTime = localtime(&now);

            stringstream localTimeStream;
            localTimeStream << put_time(localTime, "%H.%M.%S");
            string localTimeStr = localTimeStream.str();

            stringstream globalDateStream;
            globalDateStream << put_time(localTime, "%y.%m.%d");
            string globalDateStr = globalDateStream.str();

            date += LineForReadability();
            date += "Local time: " + localTimeStr + " Global date: " + globalDateStr + "\n";
            date += LineForReadability();
            
            return date;
        }

        static string TestDurationText(double duration) {
            string testTimeText = "Elapsed time: " + to_string(duration) + " second\n";
            testTimeText += LineForReadability();
            return testTimeText;
        }
};

int main() {
    string fileName = "test_results.txt";
    int const MAX_CHAR_PER_LINE = 125;
    ofstream writeFile;
    FileManager::ControlFile(fileName, writeFile);

    // For tests with a large number of terms, it is recommended to convert all "TextManager" containing methods to a \
    comment line, except the last "TextManager" containing line.\
    (This will result in a less detailed test_results.txt file, containing only the results, and the test will run faster).

    writeFile << TextManager::DateText();

    clock_t startTime = clock();

    //   sizeOfPartOfBaseSeq, numOfPossibleChunkOfPartOfBaseSeq
    list<int> successfulChunkings;  // successful if all chunks are equal
    list<int> unsuccessfulChunkings;  // and unsuccessful if all chunk are not equal
    int numOfRepetitiveSeq = 0;
    int numOfNonRepetitiveSeq = 0;

    list<string> baseSequence = SequenceTermRepetitionAnalysis::getBaseSequence();
    TextManager::WrapText(TextManager::BaseSequenceText(baseSequence), MAX_CHAR_PER_LINE, writeFile);
    unordered_map<int, pair<bool, int>> repetitionControlMap;  
    // first: key : chunk size
    // second : first : bool pair : Whether it repeats in key chunk size
    // second : second : int pair : If the sequence repeats in key chunk size, it shows how many times it repeats.\
    If not, this is irrelevant, it is not updated. Once the pair bool is false, it will never be true again.

    auto it = baseSequence.begin();
    list<string> partOfBaseSeq;
    partOfBaseSeq.push_back(*it);
    advance(it, 1);

    for (int n = 2; n <= 1023; n++) {
        partOfBaseSeq.push_back(*it);
        advance(it, 1);

        list<int> numOfPossibleChunksOfPartOfBaseSeq;
        SequenceTermRepetitionAnalysis::GetNumOfPossibleChunksOfPartOfBaseSeq(n, numOfPossibleChunksOfPartOfBaseSeq);
        if(!SequenceTermRepetitionAnalysis::IsThereADivisorOtherThanItselfAndOne(n)) {
            // TextManager::WrapText(TextManager::NoPossibleChunkWarning(n), MAX_CHAR_PER_LINE, writeFile);
            TextManager::WrapText(TextManager::NumOfPossibleChunksText(n, numOfPossibleChunksOfPartOfBaseSeq, partOfBaseSeq), MAX_CHAR_PER_LINE, writeFile);
            vector<list<string>> chunksOfPartOfBaseSeq = SequenceTermRepetitionAnalysis::DivideSequenceIntoChunks(n, n, partOfBaseSeq);
            // Algorithm1 is faster than Algorithm2. 
            SequenceTermRepetitionAnalysis::ControlAlgorithmOfChunkOfPartOfBaseSeq1(n, partOfBaseSeq, n, successfulChunkings, unsuccessfulChunkings, numOfRepetitiveSeq, numOfNonRepetitiveSeq, repetitionControlMap);
            // If you want to use Algorithm2, open the bottom comment lines and close the top one.
            // SequenceTermRepetitionControl::ControlAlgorithmOfChunkOfPartOfBaseSeq2(n, numOfPossibleChunk, chunksOfPartOfBaseSeq, successfulChunkings, unsuccessfulChunkings, numOfRepetitiveSeq, numOfNonRepetitiveSeq);
            TextManager::WrapText(TextManager::PossibleChunksText(n, chunksOfPartOfBaseSeq), MAX_CHAR_PER_LINE, writeFile);
        } else {
            TextManager::WrapText(TextManager::NumOfPossibleChunksText(n, numOfPossibleChunksOfPartOfBaseSeq, partOfBaseSeq), MAX_CHAR_PER_LINE, writeFile);
            for (int numOfPossibleChunk : numOfPossibleChunksOfPartOfBaseSeq) {
                vector<list<string>> chunksOfPartOfBaseSeq = SequenceTermRepetitionAnalysis::DivideSequenceIntoChunks(n, numOfPossibleChunk, partOfBaseSeq);
                // Algorithm1 is faster than Algorithm2. 
                SequenceTermRepetitionAnalysis::ControlAlgorithmOfChunkOfPartOfBaseSeq1(n, partOfBaseSeq, numOfPossibleChunk, successfulChunkings, unsuccessfulChunkings, numOfRepetitiveSeq, numOfNonRepetitiveSeq, repetitionControlMap);
                // If you want to use Algorithm2, open the bottom comment lines and close the top one.
                // SequenceTermRepetitionControl::ControlAlgorithmOfChunkOfPartOfBaseSeq2(n, numOfPossibleChunk, chunksOfPartOfBaseSeq, successfulChunkings, unsuccessfulChunkings, numOfRepetitiveSeq, numOfNonRepetitiveSeq);
                TextManager::WrapText(TextManager::PossibleChunksText(numOfPossibleChunk, chunksOfPartOfBaseSeq), MAX_CHAR_PER_LINE, writeFile);
            }
        }
        if(n%1000==0) cout<< n << endl;  // For simple progress demonstration, you can change the number according to the size of your test.
        writeFile << TextManager::LineForReadability();
    }

    clock_t endTime = clock();
    double duration = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    TextManager::WrapText(TextManager::ResultText(numOfRepetitiveSeq, numOfNonRepetitiveSeq, successfulChunkings, unsuccessfulChunkings), MAX_CHAR_PER_LINE, writeFile);
    
    writeFile.close();
}