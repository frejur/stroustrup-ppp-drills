#include <iostream>
#include <stdexcept>

using namespace std;

namespace ch10_test {
    void skip_to_int() {
        if (cin.fail()) {
            cin.clear();

            for (char ch; cin >> ch; ) {
                if (isdigit(ch) || ch == '-') {
                    cin.unget();

                    return;
                }
            }
        }

        throw runtime_error("no input");
    }

    int main() {
        cout << "Please enter an integer between 1 and 10" << endl;

        int n = 0;
        while (true) {
            if (cin >> n) {
                if (1 <= n && n <= 10)
                    cout << "= " << n << endl;
                else
                    cout << "Invalid range" << endl;
            }
            else {
                cout << "Not a number, try again" << endl;
                skip_to_int();
            }
        }
        return 0;
    }
}