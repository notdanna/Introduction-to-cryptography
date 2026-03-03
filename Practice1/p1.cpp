#include "../functions.hpp"
using namespace std;


int main(){
    int option, n, a, b, gcd_r = 0;
    string filename = "";
    vector<int> key;
    
    vector<int> zstar_r;
    cout << "\n" << "Podemos hacer las siguientes operaciones:" << "\n";
    cout << "[1]: Calcular el gcd de valores a y b: " << "\n";
    cout << "[2]: Calcular el Z* estrella de un valor n: " << "\n";
    cout << "[3]: Calcular el inverso de un valor a en Z* de n: " << "\n";
    cout << "[4]: Generar llaves válidas: " << "\n";
    cout << "[5]: Cifrar un archivo con el cifrado afín: " << "\n";
    cout << "[6]: Descifrar un archivo con el descifrado afín: " << "\n";
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
            cout << "ab mod n: " << (a * b) % n << "\n";
            break;

        case 4:
            cout << "Dame una n!: "; cin >> n;
            key = kGeneration(n);
            cout << "K = " ;
            printV(key);
            break;

        case 5:
            cout << "Dame el nombre del archivo a cifrar!: ";
            cin >> filename;
            affineCipher(filename);
            break;
        
        case 6:
            cout << "Dame el nombre del archivo cifrado!: ";
            cin >> filename;
            cout << "Dame una a!:"; cin >> a;
            cout << "Dame una b!:"; cin >> b;
            affineDecipher(filename, a, b);
            break;
        default:
            cout << "No se puede >:c";
            break;
    }
    return 0;
}

