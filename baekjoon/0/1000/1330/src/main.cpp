#include <iostream>

using namespace std;

int a;
int b;

int main()
{
    cin >> a >> b;

    if (a < b)
        cout << "<" << endl;
    else if (a > b)
        cout << ">" << endl;
    else
        cout << "==" << endl;

    return 0;
}
