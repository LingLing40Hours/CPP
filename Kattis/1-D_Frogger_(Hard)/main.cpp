#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include <cstdlib> 
#include <ctime>

using namespace std;

int strategy4(int *board, int n);
int bash(int *board, int n);
void dfsUtil(int position, int cardinality, int *boardCardinalities, set<int> &cycleNumber, set<int> *prevs, bool *visited, int n, int *board);
int dfsUtil(int current, int *sCount, bool *isParent, set<int> *prevs, int *cycles, int n, int i);
void dfsUtil(int position, int cardinality, int n, list<int> numbers, int *board, bool **adj, bool *visited, long *w);
void printArray(int* array, int length);
void printArray(bool* array, int length);
int sum(int* array, int length);
void printList(list<int> l);
void printArray(bool **array, int w, int h);

//Attempt 1 Forward Propagation (WA)
/*
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    bool *counted = new bool[n];
    int *board = new int[n];
    for (int i=0; i<n; ++i) {
        cin >> board[i];
        counted[i] = false;
    }
    long winInstanceCount = 0;

    //find chain starting positions
    bool *start = new bool[n];
    fill_n(start, n, true);
    for (int i=0; i<n; ++i) {
        int next = i+board[i];
        if (next>=0 && next<n)
            start[next] = false;
    }
    //printArray(start, n);

    //count chains
    for (int i=0; i<n; i++) {
        if (start[i]) {
            int position = i;
            int chainLength = 0;
            bool *inCycle = new bool[400001];
            int *visited = new int[n]; //0 if unvisited else chainLength
            fill_n(visited, n, 0);
            fill_n(inCycle, 400001, false);
            int *cardinalities = new int[n]; //at index chainLength-1, no. of distinct integers encountered
            fill_n(cardinalities, n, 0);
            int cardinality = 0;
            int** cycleCardinalities = new int*[n];
            for (int j=0; j<n; ++j) cycleCardinalities[j] = NULL;
            while (1) {
                if (position>=0 && position<n && !counted[position]) {
                    if (visited[position]) { //cycle found
                        int cycleLength = chainLength+1-visited[position];
                        int cycleCardinality = cardinalities[chainLength-1]-cardinalities[chainLength-cycleLength-1];
                        //count cycle and chain
                        winInstanceCount += cycleLength*cycleCardinality;
                        for (int j=0; j<chainLength-cycleLength; j++) {
                            winInstanceCount += cardinality+1-cardinalities[j];
                        }
                        break;
                    }
                    else {
                        if (!inCycle[board[position]+200000]) {
                            ++cardinality;
                            inCycle[board[position]+200000] = true;
                        }
                        cardinalities[chainLength] = cardinality;
                        cycleCardinalities[chainLength] = new int[n];
                        copy(cycleCardinalities[chainLength], cycleCardinalities[chainLength]+n, cardinalities);
                        chainLength += 1;
                        visited[position] = chainLength;
                        counted[position] = true;
                        position += board[position];
                    }

                }
                else { //count chain
                    //cout << chainLength << cardinality << endl;
                    //printArray(cardinalities, n);
                    for (int j=0; j<chainLength; j++) {
                        winInstanceCount += cardinality+1-cardinalities[j];
                    }
                    break;
                }
            }
            delete[] inCycle;
            delete[] cardinalities;
            for (int j=0; j<n; ++j)
                if (cycleCardinalities[j]!=NULL)
                    delete[] cycleCardinalities[j];
            delete[] cycleCardinalities;
            delete[] visited;
        }
    }

    //count cycles
    for (int i=0; i<n; ++i) {
        if (!counted[i]) {
            bool *visited = new bool[n];
            bool *inCycle = new bool[400001];
            fill_n(visited, n, false);
            fill_n(inCycle, 400001, false);
            int position = i;
            int cycleLength = 0;
            int cycleCardinality = 0;
            while (1) {
                if (visited[position]) { //cycle found
                    winInstanceCount += cycleLength*cycleCardinality;
                    break;
                }
                else {
                    if (!inCycle[board[position]+200000]) {
                        ++cycleCardinality;
                        inCycle[board[position]+200000] = true;
                    }
                    visited[position] = true;
                    counted[position] = true;
                    position += board[position];
                    cycleLength += 1;
                }
            }
            delete[] visited;
            delete[] inCycle;
        }
        //cout << i << winInstanceCount << endl;
    }
    cout << fixed << winInstanceCount << endl;
    delete[] counted;
    delete[] board;
    delete[] start;
    return 0;
} */

//Attempt 2 DFS (MLE)
/*
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int *board = new int[n];
    for (int i=0; i<n; ++i) {
        cin >> board[i];
    }
    long winInstanceCount = 0;

    bool **inverted = new bool*[n];
    for (int i=0; i<n; i++) {
        bool *temp = new bool[n];
        fill_n(temp, n, false);
        inverted[i] = temp;
    }

    for (int i=0; i<n; ++i) {
        int next = i+board[i];
        if (next>=0 && next<n) {
            inverted[next][i] = true;
        }
    }

    //find cycle branches, cycle number lists
    bool *visited = new bool[n];
    int *cycleRoot = new int[n];
    list<int> *cycleNumbers = new list<int>[n];
    fill_n(cycleRoot, n, 0);
    fill_n(visited, n, false);
    for (int i=0; i<n; ++i) {
        if (!visited[i]) {
            int position = i;
            int cycleLength = 0;
            int *lengths = new int[n];
            fill_n(lengths, n, 0);
            list<int> numbers;
            while (1) {
                if (position>=0 && position<n && !cycleRoot[position]) { //don't enter cycle a second time
                    if (visited[position]) { //cycle found
                        cycleRoot[position] = cycleLength+1-lengths[position];
                        list<int>::iterator last = numbers.begin();
                        advance(last, numbers.size()-cycleRoot[position]);
                        numbers.erase(numbers.begin(), last);
                        numbers.sort();
                        cycleNumbers[position] = numbers;
                        break;
                    }
                    else { //hop
                        ++cycleLength;
                        lengths[position] = cycleLength;
                        numbers.push_back(board[position]);
                        visited[position] = true;
                        position += board[position];
                    }
                }
                else { //no cycle found
                    break;
                }
            }
            delete[] lengths;
        }
    }
    
    printArray(cycleRoot, n);
    for (int i=0; i<n; ++i) {
        if (cycleRoot[i]) {
            for (auto j : cycleNumbers[i])
                cout << fixed << j << " ";
            cout << endl;
        }
    }

    //dfs trees
    long *w = &winInstanceCount;
    list<int> numbers;
    fill_n(visited, n, false);
    for (int i=0; i<n; ++i) {
        if (!visited[i] && (i+board[i]<0 || i+board[i]>=n)) {
            dfsUtil(i, 0, n, numbers, board, inverted, visited, w);
        }
    }
    //cout << fixed << "trees only: " << winInstanceCount << endl;

    //dfs cycles
    for (int i=0; i<n; ++i) {
        if (cycleRoot[i]) {
            dfsUtil(i, cycleRoot[i], n, cycleNumbers[i], board, inverted, visited, w);
        }
    }

    cout << fixed << winInstanceCount << endl;

    for (int i=0; i<n; ++i) {
        delete[] inverted[i];
    }
    delete[] inverted;
    delete[] visited;
    delete[] board;
    delete[] cycleRoot;
    delete[] cycleNumbers;
    return 0;
} */

//Attempt 3 Forward Propagation (WA)
/*
int main() {
    int n;
    cin >> n;
    int *board = new int[n];
    for (int i=0; i<n; ++i) cin >> board[i];

    //find start tiles
    bool *start = new bool[n];
    fill_n(start, n, true);
    for (int i=0; i<n; ++i) {
        int next = i+board[i];
        if (next>=0 && next<n) {
            start[next] = false;
        }
    }

    //cycles (also chains)
    bool *visited = new bool[n];
    int *boardCardinalities = new int[n];
    fill_n(visited, n, false);
    fill_n(boardCardinalities, n, 0);

    for (int i=0; i<n; ++i) {
        if (!visited[i]) {
            int position = i;
            int distance = 0;
            int *distances = new int[n];
            int *positions = new int[n];
            fill_n(distances, n, 0);
            fill_n(positions, n, 0);
            //track cardinalities in case chain ends without cycle?

            while (1) {
                if (position>=0 && position<n && !boardCardinalities[position]) { //don't enter cycle more than once
                    if (visited[position]) { //cycle found
                        int cycleLength = distance+1-distances[position];
                        //find cycle cardinality using last <cycleLength> positions
                        int cycleCardinality = 0;
                        bool *inCycle = new bool[400001];
                        fill_n(inCycle, 400001, false);
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            if (!inCycle[board[positions[j]]+200000]) {
                                ++cycleCardinality;
                                inCycle[board[positions[j]]+200000] = true;
                            }
                        }
                        //update boardCardinalities
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            boardCardinalities[positions[j]] = cycleCardinality;
                        }
                        delete[] inCycle;
                        break;
                    }
                    else { //hop
                        positions[distance] = position;
                        ++distance;
                        distances[position] = distance;

                        visited[position] = true;
                        position += board[position];
                    }
                }
                else { //no cycle found, count chain instead; speed up by propagating cardinality start to end
                    int chainLength = distance;
                    int cardinality = boardCardinalities[position];
                    bool *inChain = new bool[400001];
                    fill_n(inChain, 400001, false);
                    for (int j=chainLength-1; j>=0; --j) {
                        if (!inChain[board[positions[j]]+200000]) {
                            ++cardinality;
                            inChain[board[positions[j]]+200000] = true;
                        }
                        boardCardinalities[positions[j]] = cardinality;
                    }
                    delete[] inChain;
                }
            }
            delete[] distances;
            delete[] positions;
        }
    }
    printArray(boardCardinalities, n);

    //more chains
    for (int i=0; i<n; ++i) {
        if (!boardCardinalities[i]) {
            int position = i;
            int distance = 0;
            int *distances = new int[n];
            int *positions = new int[n];
            fill_n(distances, n, 0);
            fill_n(positions, n, 0);
            while (!boardCardinalities[position]) {
                if (position>=0 && position<n) {
                    positions[distance] = position;
                    ++distance;
                    distances[position] = distance;

                    visited[position] = true;
                    position += board[position];
                }
                else { //no cycle found, count chain instead; speed up by propagating cardinality start to end
                    int chainLength = distance;
                    int cardinality = boardCardinalities[position];
                    bool *inChain = new bool[400001]; //==================INCORRECT
                    fill_n(inChain, 400001, false);
                    for (int j=chainLength-1; j>=0; --j) {
                        if (!inChain[board[positions[j]]+200000]) {
                            ++cardinality;
                            inChain[board[positions[j]]+200000] = true;
                        }
                        boardCardinalities[positions[j]] = cardinality;
                    }
                    delete[] inChain;
                }
            }
            delete[] distances;
            delete[] positions;
        }
    }

    //bool *inCycle at every intersection?
    //dfs without recursion and undo change to inCycle before return
    //loop s find m; loop m find s?

    int winInstanceCount = sum(boardCardinalities, n);
    cout << fixed << winInstanceCount << endl;


    delete[] board;
    delete[] visited;
    delete[] boardCardinalities;
    return 0;
} */

//Attempt 4 DFS (WA on case 5) board = {2,2,-1,-3,-1,-2,-4,-5}

int main() {
    int n;
    cin >> n;
    int *board = new int[n];
    for (int i=0; i<n; ++i) cin >> board[i];

    //find prevs
    set<int> *prevs = new set<int>[n];
    for (int i=0; i<n; ++i) {
        set<int> p;
        prevs[i] = p;
    }
    for (int i=0; i<n; ++i) {
        int next = i+board[i];
        if (next>=0 && next<n)
            prevs[next].insert(i);
    }
    //find start positions
    bool *start = new bool[n];
    fill_n(start, n, true);
    for (int i=0; i<n; ++i) {
        int next = i+board[i];
        if (next>=0 && next<n)
            start[next] = false;
    }
    //find cycles
    int *boardCardinalities = new int[n];
    set<int> *cycleNumbers = new set<int>[n];
    bool *cycleRoots = new bool[n];
    bool *visited = new bool[n];
    bool *searched = new bool[n];
    //bool *numbers = new bool[400001];
    fill_n(cycleRoots, n, false);
    fill_n(boardCardinalities, n, 0);
    fill_n(searched, n, false);
    for (int i=0; i<n; ++i) { //from start nodes
        if (start[i]) {
            int position = i;
            int distance = 0;
            int *distances = new int[n];
            int *positions = new int[n];
            int *cycleNumberArray = new int[n];
            fill_n(cycleNumberArray, n, 0);
            fill_n(distances, n, 0);
            fill_n(positions, n, 0);
            fill_n(visited, n, false);
            while (1) {
                if (position>=0 && position<n && !searched[position]) { //don't enter cycle a second time
                    if (visited[position]) { //cycle found
                        cycleRoots[position] = true;
                        int cycleLength = distance+1-distances[position];
                        //find cycleNumber as set
                        set<int> cycleNumber;
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            cycleNumber.insert(cycleNumberArray[j]);
                        }
                        cycleNumbers[position] = cycleNumber;
                        //find cycle cardinality using set size (last <cycleLength> positions)
                        int cycleCardinality = cycleNumber.size();
                        /*
                        fill_n(numbers, 400001, false);
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            if (!numbers[board[positions[j]]+200000]) {
                                ++cycleCardinality;
                                numbers[board[positions[j]]+200000] = true;
                            }
                        }*/
                        //update boardCardinalities
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            boardCardinalities[positions[j]] = cycleCardinality;
                            //segmentation fault bc j = -1
                            //distance = 1, cycleLength = 2
                            //distances[13] = 0 (distances was reset)
                            //visited[13] = true from previous search
                            //why not reset visited every search
                        }
                        break;
                    }
                    else { //hop
                        cycleNumberArray[distance] = board[position];
                        positions[distance] = position;
                        ++distance;
                        distances[position] = distance;

                        visited[position] = true;
                        position += board[position];
                    }
                }
                else { //no cycle found
                    break;
                }
            }
            for (int j=0; j<distance; ++j) {
                searched[positions[j]] = true;
            }
            delete[] cycleNumberArray;
            delete[] positions;
            delete[] distances;
        }
    }
    //branchless cycles
    {
    for (int i=0; i<n; ++i) { //branchless cycles
        if (!searched[i]) {
            int position = i;
            int distance = 0;
            int *distances = new int[n];
            int *positions = new int[n];
            int *cycleNumberArray = new int[n];
            fill_n(cycleNumberArray, n, 0);
            fill_n(distances, n, 0);
            fill_n(positions, n, 0);
            fill_n(visited, n, false);
            while (1) {
                if (position>=0 && position<n && !searched[position]) { //don't enter cycle a second time
                    if (visited[position]) { //cycle found
                        cycleRoots[position] = true;
                        int cycleLength = distance+1-distances[position];
                        //find cycleNumber as set
                        set<int> cycleNumber;
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            cycleNumber.insert(cycleNumberArray[j]);
                        }
                        cycleNumbers[position] = cycleNumber;
                        //find cycle cardinality using set size (last <cycleLength> positions)
                        int cycleCardinality = cycleNumber.size();
                        /*
                        fill_n(numbers, 400001, false);
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            if (!numbers[board[positions[j]]+200000]) {
                                ++cycleCardinality;
                                numbers[board[positions[j]]+200000] = true;
                            }
                        }*/
                        //update boardCardinalities
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            boardCardinalities[positions[j]] = cycleCardinality;
                        }
                        break;
                    }
                    else { //hop
                        cycleNumberArray[distance] = board[position];
                        positions[distance] = position;
                        ++distance;
                        distances[position] = distance;

                        visited[position] = true;
                        position += board[position];
                    }
                }
                else { //no cycle found
                    break;
                }
            }
            for (int j=0; j<distance; ++j) {
                searched[positions[j]] = true;
            }
            delete[] cycleNumberArray;
            delete[] positions;
            delete[] distances;
        }
    }
    }
    //printArray(boardCardinalities, n);

    //dfs trees and cycles (recursive)
    fill_n(visited, n, false);
    //fill_n(numbers, 400001, false);
    for (int i=0; i<n; ++i) {
        if (!visited[i] && (i+board[i]>=n || i+board[i]<0 || cycleRoots[i])) {
            dfsUtil(i, 0, boardCardinalities, cycleNumbers[i], prevs, visited, n, board);
        }
    }
    //printArray(boardCardinalities, n);
    long winInstanceCount = sum(boardCardinalities, n);
    cout << fixed << winInstanceCount << endl;

    delete[] cycleRoots;
    delete[] start;
    //delete[] numbers;
    delete[] boardCardinalities;
    delete[] visited;
    delete[] searched;
    delete[] cycleNumbers;
    delete[] prevs;
    delete[] board;
    return 0;
}

//strategy 4
int strategy4(int *board, int n) {
    //find prevs
    set<int> *prevs = new set<int>[n];
    for (int i=0; i<n; ++i) {
        set<int> p;
        prevs[i] = p;
    }
    for (int i=0; i<n; ++i) {
        int next = i+board[i];
        if (next>=0 && next<n)
            prevs[next].insert(i);
    }
    //find start positions
    bool *start = new bool[n];
    fill_n(start, n, true);
    for (int i=0; i<n; ++i) {
        int next = i+board[i];
        if (next>=0 && next<n)
            start[next] = false;
    }
    //find cycles
    int *boardCardinalities = new int[n];
    set<int> *cycleNumbers = new set<int>[n];
    bool *cycleRoots = new bool[n];
    bool *visited = new bool[n];
    bool *searched = new bool[n];
    //bool *numbers = new bool[400001];
    fill_n(cycleRoots, n, false);
    fill_n(boardCardinalities, n, 0);
    fill_n(searched, n, false);
    for (int i=0; i<n; ++i) { //from start nodes
        if (start[i]) {
            int position = i;
            int distance = 0;
            int *distances = new int[n];
            int *positions = new int[n];
            int *cycleNumberArray = new int[n];
            fill_n(cycleNumberArray, n, 0);
            fill_n(distances, n, 0);
            fill_n(positions, n, 0);
            fill_n(visited, n, false);
            while (1) {
                if (position>=0 && position<n && !searched[position]) { //don't enter cycle a second time
                    if (visited[position]) { //cycle found
                        cycleRoots[position] = true;
                        int cycleLength = distance+1-distances[position];
                        //find cycleNumber as set
                        set<int> cycleNumber;
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            cycleNumber.insert(cycleNumberArray[j]);
                        }
                        cycleNumbers[position] = cycleNumber;
                        //find cycle cardinality using set size (last <cycleLength> positions)
                        int cycleCardinality = cycleNumber.size();
                        /*
                        fill_n(numbers, 400001, false);
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            if (!numbers[board[positions[j]]+200000]) {
                                ++cycleCardinality;
                                numbers[board[positions[j]]+200000] = true;
                            }
                        }*/
                        //update boardCardinalities
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            boardCardinalities[positions[j]] = cycleCardinality;
                            //segmentation fault bc j = -1
                            //distance = 1, cycleLength = 2
                            //distances[13] = 0 (distances was reset)
                            //visited[13] = true from previous search
                            //why not reset visited every search
                        }
                        break;
                    }
                    else { //hop
                        cycleNumberArray[distance] = board[position];
                        positions[distance] = position;
                        ++distance;
                        distances[position] = distance;

                        visited[position] = true;
                        position += board[position];
                    }
                }
                else { //no cycle found
                    break;
                }
            }
            for (int j=0; j<distance; ++j) {
                searched[positions[j]] = true;
            }
            delete[] cycleNumberArray;
            delete[] positions;
            delete[] distances;
        }
    }
    //branchless cycles
    {
    for (int i=0; i<n; ++i) { //branchless cycles
        if (!searched[i]) {
            int position = i;
            int distance = 0;
            int *distances = new int[n];
            int *positions = new int[n];
            int *cycleNumberArray = new int[n];
            fill_n(cycleNumberArray, n, 0);
            fill_n(distances, n, 0);
            fill_n(positions, n, 0);
            fill_n(visited, n, false);
            while (1) {
                if (position>=0 && position<n && !searched[position]) { //don't enter cycle a second time
                    if (visited[position]) { //cycle found
                        cycleRoots[position] = true;
                        int cycleLength = distance+1-distances[position];
                        //find cycleNumber as set
                        set<int> cycleNumber;
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            cycleNumber.insert(cycleNumberArray[j]);
                        }
                        cycleNumbers[position] = cycleNumber;
                        //find cycle cardinality using set size (last <cycleLength> positions)
                        int cycleCardinality = cycleNumber.size();
                        /*
                        fill_n(numbers, 400001, false);
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            if (!numbers[board[positions[j]]+200000]) {
                                ++cycleCardinality;
                                numbers[board[positions[j]]+200000] = true;
                            }
                        }*/
                        //update boardCardinalities
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            boardCardinalities[positions[j]] = cycleCardinality;
                        }
                        break;
                    }
                    else { //hop
                        cycleNumberArray[distance] = board[position];
                        positions[distance] = position;
                        ++distance;
                        distances[position] = distance;

                        visited[position] = true;
                        position += board[position];
                    }
                }
                else { //no cycle found
                    break;
                }
            }
            for (int j=0; j<distance; ++j) {
                searched[positions[j]] = true;
            }
            delete[] cycleNumberArray;
            delete[] positions;
            delete[] distances;
        }
    }
    }
    //printArray(boardCardinalities, n);

    //dfs trees and cycles (recursive)
    fill_n(visited, n, false);
    //fill_n(numbers, 400001, false);
    for (int i=0; i<n; ++i) {
        if (!visited[i] && (i+board[i]>=n || i+board[i]<0 || cycleRoots[i])) {
            dfsUtil(i, 0, boardCardinalities, cycleNumbers[i], prevs, visited, n, board);
        }
    }
    //printArray(boardCardinalities, n);
    long winInstanceCount = sum(boardCardinalities, n);
    //cout << fixed << winInstanceCount << endl;

    delete[] cycleRoots;
    delete[] start;
    //delete[] numbers;
    delete[] boardCardinalities;
    delete[] visited;
    delete[] searched;
    delete[] cycleNumbers;
    delete[] prevs;
    //delete[] board;
    return winInstanceCount;
}

//Attempt 5 Loop m DFS with DP (TLE)
/*
int main() {
    int n;
    cin >> n;
    int *board = new int[n];
    for (int i=0; i<n; ++i) cin >> board[i];

    //find nexts
    int *nexts = new int[n];
    for (int i=0; i<n; ++i) {
        nexts[i] = i+board[i];
    }
    //find prevs
    set<int> *prevs = new set<int>[n];
    for (int i=0; i<n; ++i) {
        set<int> p;
        prevs[i] = p;
    }
    for (int i=0; i<n; ++i) {
        int next = i+board[i];
        if (next>=0 && next<n)
            prevs[next].insert(i);
    }
    //find numbers
    bool numbers[400001];
    fill_n(numbers, 400001, false);
    for (int i=0; i<n; ++i) {
        numbers[board[i]+200000] = true;
    }
    //find starts
    bool *start = new bool[n];
    fill_n(start, n, true);
    for (int i=0; i<n; ++i) {
        int next = i+board[i];
        if (next>=0 && next<n)
            start[next] = false;
    }
    //find cycles
    int cycleIndex = 1;
    int *cycles = new int[n];
    bool *visited = new bool[n];
    fill_n(cycles, n, 0);
    fill_n(visited, n, false);
    for (int i=0; i<n; ++i) {
        if (start[i]) {
            int position = i;
            int distance = 0;
            int *distances = new int[n];
            int *positions = new int[n];
            fill_n(distances, n, 0);
            fill_n(positions, n, 0);
            while (1) {
                if (position>=0 && position<n && !cycles[position]) { //don't enter cycle a second time
                    if (visited[position]) { //cycle found
                        int cycleLength = distance+1-distances[position];
                        //update boardCardinalities
                        for (int j=distance-cycleLength; j<distance; ++j) {
                            cycles[positions[j]] = cycleIndex;
                        }
                        ++cycleIndex;
                        break;
                    }
                    else { //hop
                        positions[distance] = position;
                        ++distance;
                        distances[position] = distance;

                        visited[position] = true;
                        position += board[position];
                    }
                }
                else { //no cycle found
                    break;
                }
            }
            delete[] positions;
            delete[] distances;
        }
    }
    //printArray(cycles, n);
    //init stuff
    int winInstanceCount = 0;
    int *sCount = new int[n];
    fill_n(sCount, n, 0);
    bool *isParent = new bool[n];
    //loop winning positions, count distinct parent positions
    for (int num=0; num<400001; ++num) {
        if (numbers[num]) {
            fill_n(isParent, n, false);
            for (int i=0; i<n; ++i) { //search positions containing num
                if (board[i]+200000==num) {
                    int s = 0;
                    //list<int> parents;
                    if (!isParent[i]) { //self
                        isParent[i] = true;
                        //parents.push_back(i);
                        int temp = dfsUtil(i, sCount, isParent, prevs, cycles, n, i);
                        cout << fixed << i << ", " << temp << endl;
                        s += temp;
                    }
                    //dfs for parents; use dp
                    
                    while (parents.size()>0) {
                        int current = parents.front();
                        parents.pop_front();
                        if (sCount[current]) {
                            s += sCount[current];
                            if (cycles[i]>0 && cycles[current]==cycles[i])
                                --s;
                        }
                        else {
                            int sTemp = 0;
                            for (int j=0; j<n; ++j) {
                                if (!isParent[j] && prevs[current].find(j) != prevs[current].end()) {
                                    parents.push_back(j);
                                    ++s;
                                    ++sTemp;
                                    isParent[j] = true;
                                }
                            }
                            sCount[current] = sTemp;
                        }
                    }
                    winInstanceCount += s;
                }
            }
        }
    }
    printArray(sCount, n);
    cout << fixed << winInstanceCount << endl;

    delete[] board;
    delete[] nexts;
    delete[] prevs;
    delete[] sCount;
    delete[] isParent;
    delete[] cycles;
    delete[] visited;
    return 0;
} */

//Attempt 4 DFS
void dfsUtil(int position, int cardinality, int *boardCardinalities, set<int> &cycleNumber, set<int> *prevs, bool *visited, int n, int *board) {
    //check cycle
    if (visited[position]) {
        return;
    }

    //update cardinality
    bool prev = cycleNumber.find(board[position])!=cycleNumber.end();
    if (boardCardinalities[position]) {
        cardinality = boardCardinalities[position];
    }
    else {
        if (!prev) {
            ++cardinality;
            //numbers[board[position]+200000] = true;
            cycleNumber.insert(board[position]);
        }
    }

    //count and mark visited
    boardCardinalities[position] = cardinality;
    visited[position] = true;

    //search adjacent nodes
    for (set<int>::iterator it = prevs[position].begin(); it!=prevs[position].end(); ++it) {
        dfsUtil(*it, cardinality, boardCardinalities, cycleNumber, prevs, visited, n, board);
    }

    //undo change to numbers/cycleNumber
    //numbers[board[position]+200000] = prev;
    if (!prev) cycleNumber.erase(board[position]);
}

//Attempt 5 DFS
int dfsUtil(int current, int *sCount, bool *isParent, set<int> *prevs, int *cycles, int n, int i) {
    int ans = 1;
    if (sCount[current] && cycles[current]<=0 || cycles[current]!=cycles[i]) {
        ans += sCount[current];
    }
    else {
        for (int j=0; j<n; ++j) {
            if (!isParent[j] && prevs[current].find(j)!=prevs[current].end()) {
                isParent[j] = true;
                ans += dfsUtil(j, sCount, isParent, prevs, cycles, n, i);
            }
        }
        sCount[current] = ans;
        for (int j=0; j<n; ++j) {
            if (isParent[j] && cycles[j]>0 && cycles[j]==cycles[current])
                ++sCount[current];
        }
    }
    return ans;
}

//Attempt 2 DFS
void dfsUtil(int position, int cardinality, int n, list<int> numbers, int *board, bool **adj, bool *visited, long *w) {
    //check cycle
    if (visited[position]) {
        //undercounted cycle instances
        //int cycleCardinality = cardinality;
        //*w += cycleCardinality*(cycleCardinality-1)/2;
        return;
    }

    //update cardinality
    list<int>::iterator it = numbers.begin();
    while (*it < board[position] && it!=numbers.end()) {
        ++it;
    }
    if (*it != board[position]) {
        ++cardinality;
    }
    numbers.insert(it, board[position]);

    //count and mark visited
    visited[position] = true;
    *w += cardinality;

    //search adjacent nodes
    for (int i=0; i<n; ++i) {
        if (adj[position][i]) {
            dfsUtil(i, cardinality, n, numbers, board, adj, visited, w);
        }
    }
}

//generate test cases and bash
/*
int main() {
    //int test[8] = {1,2,3,-1,-2,2,-3,-1};
    //cout << strategy4(test, 8) << endl;
    int n = 1000;
    int *board = new int[n];
    int boardCount = 0;
    int alg4 = 0;
    int bashed = 0;
    srand((unsigned)time(0));
    while (alg4==bashed) {
        //init random board
        for (int i=0; i<n; ++i) {
            board[i] = rand()%200001-100000;
        }

        //progress
        if (boardCount%1==0)
            cout << fixed << "searched " << boardCount << " boards" << endl;

        alg4 = strategy4(board, n);
        bashed = bash(board, n);
        ++boardCount;
    }
    printArray(board, n);
    delete[] board;
    return 0;
}*/

void printArray(int* array, int length) {
    for (int i=0; i<length; ++i) {
        cout << fixed << array[i] << " ";
    }
    cout << endl;
}

void printArray(bool* array, int length) {
    for (int i=0; i<length; ++i) {
        cout << (int) array[i] << " ";
    }
    cout << endl;
}

void printList(list<int> l) {
    for (int i : l) {
        cout << fixed << i << " ";
    }
    cout << endl;
}

int sum(int* array, int length) {
    int ans = 0;
    for (int i=0; i<length; ++i) {
        ans += array[i];
    }
    return ans;
}

void printArray(bool **array, int w, int h) {
    for (int i=0; i<w; ++i) {
        for (int j=0; j<h; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

int bash(int *board, int n) {
    int winInstanceCount = 0;
    
    //find numbers
    bool *numbers = new bool[400001];
    fill_n(numbers, 400001, false);
    for (int i=0; i<n; ++i) {
        numbers[board[i]+200000] = true;
    }

    //loop positions and bash
    bool *visited = new bool[n];
    for (int i=0; i<n; ++i) {
        for (int num=-200000; num<=200000; ++num) {
            if (numbers[num+200000]) {
                int position = i;
                fill_n(visited, n, false);
                while (1) {
                    if (position>=0 && position<n) {
                        if (visited[position]) { //in m-less cycle
                            break;
                        }
                        else if (board[position]==num) { //found a pair
                            ++winInstanceCount;
                            break;
                        }
                        else { //hop
                            visited[position] = true;
                            position += board[position];
                        }
                    }
                    else { //num not found
                        break;
                    }
                }
            } //end if
        } //end num loop
    } //end position loop

    delete[] visited;
    delete[] numbers;
    return winInstanceCount;
}