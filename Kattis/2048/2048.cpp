#include <iostream>
#include <cmath>

using namespace std;

void leftMove(int* row);
void leftShift(int* row);
void reverse(int* row);
int passArrayByReference(int (&row)[4]);

int main(void) {
    //input
    int move=0;
    int grid[4][4] = {0};
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            cin >> grid[i][j];
        }
    }
    cin >> move; //0123 left up right down
    if (move==0) {
        for (int i=0; i<4; i++) {
            leftMove(grid[i]);
        }
    }
    else if (move==2) {
        for (int i=0; i<4; i++) {
            reverse(grid[i]);
            leftMove(grid[i]);
            reverse(grid[i]);
        }
    }
    else if (move==1) {
        for (int j=0; j<4; j++) {
            int col[4] = {0};
            for (int i=0; i<4; i++) {
                col[i] = grid[i][j];
            }
            leftMove(col);
            for (int i=0; i<4; i++) {
                grid[i][j] = col[i];
            }
        }
    }
    else {
        for (int j=0; j<4; j++) {
            int col[4] = {0};
            for (int i=0; i<4; i++) {
                col[i] = grid[4-i-1][j];
            }
            leftMove(col);
            reverse(col);
            for (int i=0; i<4; i++) {
                grid[i][j] = col[i];
            }
        }
    }

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            cout << fixed << grid[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

void leftMove(int* row) {
    int cIndex = 0;
    int cValue = -1;
    for (int i=0; i<4; i++) {
        if (cValue==row[i]) {
            //merge
            row[cIndex] *= 2;
            row[i] = 0;
            cIndex = i;
            cValue = -1;
        }
        else if (row[i]!=0) {
            //reset
            cValue = row[i];
            cIndex = i;
        }
    }
    leftShift(row);
}

void leftShift(int* row) {
    int ans[4] = {0};
    int index = 0;
    for (int i=0; i<4; i++) {
        if (row[i]!=0) {
            ans[index] = row[i];
            index++;
        }
    }
    copy(ans, ans+4, row);
}

void reverse(int* row) {
    int ans[4] = {0};
    for (int i=0; i<4; i++) {
        ans[4-i-1] = row[i];
    }
    copy(ans, ans+4, row);
}

int passArrayByReference(int (&row)[4]) {
    return 0;
}