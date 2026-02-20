#include "functions.hpp"
using namespace std;

int main(){
    int option, n, a, b, gcd_r = 0;
    vector<int> zstar_r(n);
    cout << "Elige el número de ejercicio: "; 
    cin >> option;

    switch(option){

        case 1: 
            cout << "Dame una a!: "; cin >> a;
            cout << "Dame una b!: "; cin >> b;
            gcd_r = gcd(a,b);
            cout << "Yo te doy un GCD de: "<< gcd_r << "\n"; 
            break;

        case 2: 
            cout << "Dame una n!: "; cin >> n;
            zstar_r = zStar(n);
            cout << "Yo te doy un Z^*: ";
            printV(zstar_r);
            break;

        case 3:          
            cout << "Dame una n!: "; cin >> n;
            zstar_r = zStar(n);
            cout << "Elige un valor de Z estrella: ";
            printV(zstar_r);
            cout << "Dame un valor!: "; cin >> a;

            b = aminusone(n, a);
            cout << "Yo te doy un b!: "<< b << "\n";
            break;

    }
    return 0;
}

