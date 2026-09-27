#include <iostream>
#include <string>
using namespace std;

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            string s;
            cin >> s;
            int M = 0, m = 0, ans = 0;
            for(int i=0;i<(int)s.length();i++) {
                char c = s[i];
                if (c == 'M') M++;
                else if (c == 'm') m++;
                else if (c == 'n') {
                    if (m > 0) m--;
                    else M--;
                } else if (c == 'N') {
                    if (M > 0) { ans++; M--; }
                    else m--;
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
