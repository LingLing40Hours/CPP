#include <iostream>
#include <bits/stdc++.h>

using namespace std;

char symbol(int operation);

int main() {
    int m;
    cin >> m;

    //calculate ns
    int results[4][4][4];
    int operationList[3];
    for (operationList[0]=0; operationList[0]<4; ++operationList[0]) {
        for (operationList[1]=0; operationList[1]<4; ++operationList[1]) {
            for (operationList[2]=0; operationList[2]<4; ++operationList[2]) {
                int result = 0;
                int distance = 0;
                int product = 4;
                //find products
                list<int> products;
                while (distance<3) {
                    if (operationList[distance]==2) { //multiplication
                        product *= 4;
                    }
                    else if (operationList[distance]==3) { //division (floored)
                        product /= 4;
                    }
                    else { //append product
                        products.push_back(product);
                        product = operationList[distance] ? -4 : 4;
                    }
                    ++distance;
                }
                products.push_back(product);
                //sum products, store result
                for (list<int>::iterator it = products.begin(); it!=products.end(); ++it) {
                    result += *it;
                }
                results[operationList[0]][operationList[1]][operationList[2]] = result;
            }
        }
    }

    //print answers
    for (int it=0; it<m; ++it) {
        int n;
        cin >> n;
        //search for n
        bool found = false;
        for (int i=0; i<4; ++i) {
            for (int j=0; j<4; ++j) {
                for (int k=0; k<4; ++k) {
                    if (results[i][j][k]==n) {
                        cout << "4 " << symbol(i) << " 4 " << symbol(j) << " 4 " << symbol(k) << " 4 = " << n << endl;
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            if (found) break;
        }
        if (!found) cout << "no solution" << endl;
    }

    return 0;
}

char symbol(int operation) {
    switch(operation) {
        case 0:
            return '+';
        case 1:
            return '-';
        case 2:
            return '*';
        case 3:
            return '/';
        default:
            return '+';
    }
}