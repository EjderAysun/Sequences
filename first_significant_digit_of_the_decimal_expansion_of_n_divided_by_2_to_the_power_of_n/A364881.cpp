#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;
class A364881 {
    // Both methods can be used to generate the sequence.
    public:
        // Can produce the first 1023 terms.
        static int aFirstMethod(int n) {
            double x = n/pow(2, n);
            return floor(x / pow(10, floor(log10(x))));
        }

        // Can produce the first 1023 terms.
        static char aSecondMethod(int n) {
            double x = n/pow(2, n);
            ostringstream oss;
            oss << scientific << x;
            return oss.str()[0];
        }

        static int getSequenceSize(string methodName) {
            while (true) {
                try {
                    int n;
                    cout << "Enter sequence size between [1-1023] for " << methodName << ": ";
                    if(!(std::cin >> n)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw std::invalid_argument("Invalid input. Please enter a valid integer!");
                    } else if (!(n >= 1 && n <= 1023)) {
                        throw out_of_range("The number is not between [1-1023]!");
                    }
                    return n;
                }
                catch(const out_of_range& oor) {
                    cerr << oor.what() << endl;
                }
                catch(const exception& e) {
                    std::cerr << e.what() << '\n';
                }
            }
        }
};

// test drive
int main() {
    int sizeForFirstList = A364881::getSequenceSize("aFirstMethod");
    int listForFirstMethod[sizeForFirstList];
    int sizeForSecondList = A364881::getSequenceSize("aSecondMethod");
    char listForSecondMethod[sizeForSecondList];

    for (int n = 1; n <= sizeForFirstList; n++) {
        listForFirstMethod[n-1] = A364881::aFirstMethod(n);
    }
    for (int n = 1; n <= sizeForSecondList; n++) {
        listForSecondMethod[n-1] = A364881::aSecondMethod(n);
    }
    
    cout << "results for first method:" ;
    for(int n : listForFirstMethod) cout << n << " ";
    cout << endl;
    cout << "results for second method:" ;
    for(char n : listForSecondMethod) cout << n << " ";

    return 0;
}