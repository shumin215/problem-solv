#include <iostream>
#include <climits>

using namespace std;

int n;
string exp;
int max_res = INT_MIN;

int cal(int _a, int _b, char _op)
{
    int ret;
    switch (_op) {
        case '+' : ret = _a + _b; break; 
        case '*' : ret = _a * _b; break; 
        case '-' : ret = _a - _b; break; 
    }

    return ret;
}

void doDFS(int _res, int _idx)
{
    // 1. Exit condition
    if (_idx + 1 > n) {
#ifdef DEBUG
        printf("[DEBUG] Cal: %d\n", _res);
#endif
        if (max_res < _res)
            max_res = max(max_res, _res);
        return;
    }
    char op = (_idx == 0) ? '+' : exp[_idx-1];

    // 2. In case of bracket
    // A OP B
#ifdef DEBUG
    printf("[DEBUG] %d %c %c\n", _res, op, exp[_idx]);
#endif
    doDFS(cal(_res, exp[_idx]-'0', op), _idx+2);
    // 3. In case of bracket
    // A OP1 (B OP2 C)
    if (_idx + 4 < n) {
        int brac_res = cal(exp[_idx]-'0', exp[_idx+2]-'0', exp[_idx+1]);
#ifdef DEBUG
        printf("[DEBUG] %d %c (%c %c %c)\n", _res, op, exp[_idx], exp[_idx+1], exp[_idx+2]);
#endif
        doDFS(cal(_res, brac_res, op), _idx+4);
    }
}

int main()
{
    cin >> n;
    cin >> exp;

    doDFS(0, 0);

    printf("%d\n", max_res);
    return 0;
}
