#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int main(void) {
    int n;
    vector<int> a;
    a.resize(n);

    cin >> n;
    for (int i=0; i < n; ++i) {
        cin >> a[i];
    }

    int similarSequenceCount = (int)pow(3, n);
    int oddProductSequenceCount = 1;
    for (int i=0; i < n; ++i) {
        if (a[i]%2 == 0) {
            oddProductSequenceCount *= 2;
        }
    }

    int ans = similarSequenceCount - oddProductSequenceCount;
    std::cout << ans << std::endl;

    return 0;
}