#include <bits/stdc++.h>

using namespace std;

void foo(int n, int &sum)

{

    if (n == 0) return;

    int k = n % 10;

    int j = n / 10;

    sum = sum + k;

    foo (j, sum);

    cout << k << "" << endl;
    cout << sum << endl;

}

int main ()

{

    int a = 2048, sum = 0;

    foo (a, sum);

    cout << sum;

}


