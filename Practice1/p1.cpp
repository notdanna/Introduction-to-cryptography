#include "libraries.hpp"
#include "functions.hpp"
using namespace std;


int main(){
    int option, n, a, b, gcd_r = 0;
    
    /*
    map<int, char> ascii_dict;
    for (int i = 32; i <= 126; ++i) {
        ascii_dict[i] = static_cast<char>(i);
        cout << ascii_dict[i] << ", ";
    }
    cout << "\n";
    */
    vector<int> key;
    int var = 12;
    key = kGeneration(var);
    printV(key);


    string filename = "hello";
    key = {1,2}; 

    affineCipher(filename, key);
    






    vector<int> zstar_r(n);
    cout << "\n" << "Podemos hacer las siguientes operaciones:" << "\n";
    cout << "1: Calcular el gcd de valores a y b: " << "\n";
    cout << "2: Calcular el Z* estrella de un valor n: " << "\n";
    cout << "3: Calcular el inverso de un valor a en Z* de n: " << "\n";
    cout << "Elige: "; cin >> option;

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

