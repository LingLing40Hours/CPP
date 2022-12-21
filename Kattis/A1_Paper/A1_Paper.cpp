#include <iostream>
#include <math.h>
using namespace std;

void printArray(double* array, int length);
void printArray(int* array, int length);
bool isPossible(int* a, int length);

int main(void) {
    //cout << pow(2, 32)-1 << endl;
    int n;
    cin >> n;

    int* a = new int[n-1];
    for (int i=0; i<n-1; i++) {
        cin >> a[i];
    }

    double totalArea = 0;
    double paperArea = 0.5;
    double* lengths = new double[n-1];
    int* lengthsTest = new int[n-1];

    //calculate lengths
    for (int i=0; i<n-1; i++) {
        lengths[i] = pow(2, -0.75-0.5*i);
        lengthsTest[i] = (int) pow(10, n-2-i);
    }
    //printArray(lengths, n-1);
    /*
    for (int i=0; i<n-1; i++) {
        //cout << i << ", " << a[i] << endl;
        totalArea += a[i]*paperArea;
        paperArea /= 2.0;
    } */
    //cout << totalArea << endl;
    if (!isPossible(a, n-1)) cout << "impossible" << endl;
    else {
        double tapeLength = lengths[0];
        int* shortages = new int[n-1];
        int shortage = 1; //A1 paper
        for (int i=0; i<n-1; i++) { //find shortages
            shortage = 2*shortage-a[i];
            shortages[i] = shortage;
            if (shortage <= 0) {
                break;
            }
        }
        //printArray(shortages, n-1);
        for (int i=0; i<n-1; i++) { //find tapeLength
            //cout << i << ", " << shortages[i-1] << ", " << lengths[i] << endl;
            if (i>0) tapeLength += shortages[i-1]*lengths[i];
            if (shortages[i]<=0) break;
        }
        cout << fixed << tapeLength << endl;
        delete [] shortages;
    }

    delete [] a;
    delete [] lengths;
    delete [] lengthsTest;
    return 0;
}

void printArray(double* array, int length) {
    for (int i=0; i<length; i++) {
        cout << array[i] << ", ";
    }
    cout << endl;
}

void printArray(int* array, int length) {
    for (int i=0; i<length; i++) {
        cout << array[i] << ", ";
    }
    cout << endl;
}

bool isPossible(int* a, int length) {
    int shortage = 1;
    for (int i=0; i<length; i++) {
        shortage = 2*shortage-a[i];
    }
    if (shortage<=0) return true;
    return false;
}