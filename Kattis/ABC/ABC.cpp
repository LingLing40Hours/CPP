#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main(void) {
    int* n = new int[3];
    for (int i=0; i<3; i++) {
        cin >> n[i];
    }
    sort(n, n+3);

    char* order = new char[3];
    for (int i=0; i<3; i++) {
        cin >> order[i];
    }

    for (int i=0; i<3; i++) {
        if (order[i]=='A')  cout << fixed << n[0];
        else if (order[i]=='B') cout << fixed << n[1];
        else cout << fixed << n[2];

        if (i==3-1) cout << endl;
        else cout << " ";
    }

    delete [] n;
    delete[] order;
    return 0;
}