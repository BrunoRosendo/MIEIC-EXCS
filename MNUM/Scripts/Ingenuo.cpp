#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main()
{
    double start = exp(-1);
    for (int i = 1; i <= 25; ++i) {
        start = start * i - 1;
        cout << fixed << setprecision(40) << start << endl;
    }
    return 0;
}
