#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

double average(int* array, int length);

int main(void) {
    int c;
    cin >> c;

    for (int i=0; i<c; i++) {
        int n;
        cin >> n;
        int* grades = new int[n];
        for (int j=0; j<n; j++) {
            cin >> grades[j];
        }
        double avg = average(grades, n);
        //cout << "avg: " << avg << endl;
        int aboveAverageCount = 0;
        for (int j=0; j<n; j++) {
            if (grades[j]>avg) aboveAverageCount++;
        }

        double percentage = round(((double)aboveAverageCount/n)*100000.0)/1000.0;
        cout <<fixed<<setprecision(3)<<percentage<<"%"<<endl;

        delete [] grades;
    }
    return 0;
}

double average(int* array, int length) {
    int sum = 0;
    for (int i=0; i<length; i++) {
        sum += array[i];
    }
    double ans = (double)sum/length;
    return ans;
}