#include <iostream>
#include <stack>

using namespace std;

int N;
stack<int> s;

int main()
{
    cin >> N;

    for (int i=0; i<N; i++) {
        char op;
        cin >> op;

        if (op == 'i') {
            int num;
            cin >> num;
            s.push(num);
        } else if (op == 'o') {
            if (s.empty()) {
                cout << "empty\n";
                continue;
            }
            int num = s.top();
            s.pop();
            cout << num << "\n";
        } else if (op == 'c') {
            cout << s.size() << "\n";
        }
    }

    return 0;
}
