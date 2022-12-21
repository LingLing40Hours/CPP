#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

list<int>::iterator find(list<int> *populations, int prev, int current);

int main() {
    int p;
    cin >> p;

    //use general formula (a_n too large)
    /*
    double sqrt5 = pow(5, 0.5);
    double Phi = (1+sqrt5)/2.0;
    double phi = (1-sqrt5)/2.0;
    for (int i=0; i<p; ++i) {
        int k;
        long y;
        cin >> k;
        cin >> y;

        int ans = (long long)(round((pow(Phi, y)-pow(phi,y))/sqrt5))%1000000000;
        //cout << pow(Phi, y)-pow(phi,y) << endl;
        //cout << (pow(Phi, y)-pow(phi,y))/sqrt5 << endl;
        //cout << round((pow(Phi, y)-pow(phi,y))/sqrt5) << endl;
        //cout << (long long)(round((pow(Phi, y)-pow(phi,y))/sqrt5)) << endl;
        cout << k << " " << ans << endl;
    }*/
    
    //calculate fibb array (MLE)

    //calculate population cycle
    list<int> populations;
    list<int> *pps = &populations;
    populations.push_back(1);
    populations.push_back(1);
    int prev = 1;
    int current = 1;
    while (1) {
        int next = (prev+current)%1000000000;
        prev = current;
        current = next;
        if (find(pps, prev, current)!=populations.end()) {
            cout << "cycle found" << endl;
            break;
        }
    }

    return 0;
}

list<int>::iterator find(list<int> *populations, int prev, int current) {
    for (list<int>::iterator it = populations->begin(); it!=populations->end(); ++it) {
        if (it==populations->begin()) continue;
        list<int>::iterator pit = it;
        advance(pit, -1);
        if (*pit==prev && *it==current) {
            return pit;
        }
    }
    return populations->end();
}