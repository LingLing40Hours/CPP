#include <iostream>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

int main() {
    int n, s, m;
    cin >> n >> s >> m;
    int position = s-1;
    int* board = new int[n];
    bool* visited = new bool[n];
    for (int i=0; i<n; i++) {
        cin >> board[i];
        visited[i] = false;
    }

    int h=0;
    string fate;
    while (1) {
        if (position>=0 && position<n) {
            if (board[position]==m) {
                fate = "magic";
                break;
            }
            else if (visited[position]) {
                fate = "cycle";
                break;
            }
            else {
                visited[position] = true;
                position += board[position];
                h += 1;
            }
        }
        else if (position<0) {
            fate = "left";
            break;
        }
        else {
            fate = "right";
            break;
        }
    }

    cout << fate << endl;
    cout << fixed << h << endl;

    delete [] board;
    delete [] visited;
    return 0;
}