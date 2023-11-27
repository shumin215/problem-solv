#include <iostream>
#include <queue>

using namespace std;

int N;
queue<int> q;

int main()
{
    cin >> N;

    for (int i=0; i<N; i++) {
        char op;
        cin >> op;

        if (op == 'i') {
            int num;
            cin >> num;
            q.push(num);
        } else if (op == 'o') {
            if (q.empty()) {
                cout << "empty\n";
                continue;
            }
            int num = q.front();
            q.pop();
            cout << num << "\n";
        } else if (op == 'c') {
            cout << q.size() << "\n";
        }
    }

    return 0;
}
