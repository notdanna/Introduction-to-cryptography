#include "../functions.hpp"
using namespace std;



int main()
{


    int n = 0;
    cout << "Dame una t!: ";
    cin >> n;
    vector<int> piv;
    vector<int> inv;
    vector<int> X;


    for (int i = 1; i <= n; i++){
        X.push_back(i);
    }

    cout << "X: ";
    printV(X);

    cout << string(4*n - 2, '-') << "\n";

    piv = pi(n);
    cout << "π: ";
    printV(piv);

    inv = piInverse(piv);
    cout << "ı: ";
    printV(inv);

    return 0;
}




