#include <iostream>
#include <stack>
using namespace std;

string postToPre(string post_exp) {
    stack<string> s;
    for (char c : post_exp) {
        if (isalnum(c))
            s.push(string(1, c));
        else {
            string b = s.top();
            s.pop();
            string a = s.top();
            s.pop();
            s.push(string(1, c) + a + b);
        }
    }
    return s.top();
}

int main() {
    string s;
    cin >> s;
    cout << postToPre(s);
    return 0;
}
