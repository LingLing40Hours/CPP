#include <iostream>

using namespace std;

int main() {
    string s;
    cin >> s;
    char initial = s.at(0);

    //policy up
    int p1 = 0;
    if (initial=='D') {
        if (s.at(1)=='D') --p1;
        else ++p1;
    }
    for (int i=1; i<s.length(); ++i) {
        if (s.at(i)=='D') p1 += 2;
    }

    //policy down
    int p2 = 0;
    if (initial=='U') {
        if (s.at(1)=='U') --p2;
        else ++p2;
    }
    for (int i=1; i<s.length(); ++i) {
        if (s.at(i)=='U') p2 += 2;
    }

    //policy stay
    int p3 = 0;
    char prev = initial;
    for (int i=1; i<s.length(); ++i) {
        if (prev != s.at(i)) {
            ++p3;
        }
        prev = s.at(i);
    }

    cout << fixed << p1 << endl;
    cout << fixed << p2 << endl;
    cout << fixed << p3 << endl;
    return 0;
}