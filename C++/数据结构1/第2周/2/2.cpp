#include <bits/stdc++.h>
using namespace std;

double doubleCallByValue(double _count)
{
    return _count * 2;
}

double doubleCallByPointer(double* p_count)
{
    *p_count *= 2;
    return *p_count;
}

double doubleCallByReference(double& q_count)
{
    q_count *= 2;
    return q_count;
}

int main()
{
    double count = 5;
    doubleCallByValue(count);
    cout << count << endl;
    doubleCallByPointer(&count);
    cout << count << endl;
    doubleCallByReference(count);
    cout << count << endl;
    return 0;
}