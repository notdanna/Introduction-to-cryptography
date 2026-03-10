#include "../functions.hpp"
using namespace std;

int main()
{
    int options = 0;
    int n = 0;
    int nperm = 0;
    vector<int> piv;
    vector<int> inv;
    vector<int> X;
    string plain = "";
    string ciph = "";
    string res = "";
    
    cout << "Elige una opción: \n";
    cout << "[1]: Calcular la permutación y su inversa.\n";
    cout << "[2]: Cifrar el mensaje usando Permutación\n";
    cout << "[3]: Decifrar el mensaje usando Permutación\n";

    cin >> options;

    switch (options)
    {
    case 1:
        cout << "Dame una n!: ";
        cin >> n;
        for (int i = 1; i <= n; i++)
            X.push_back(i);
    
        cout << "X: "; printV(X);

        cout << string(4*n - 2, '-') << "\n";

        piv = pi(n);
        cout << "π: "; printV(piv);

        inv = piInverse(piv);
        cout << "ı: "; printV(inv);

        break;
    case 2:
        cout << "Dame un texto a cifrar: ";
        cin.ignore();
        getline(cin, plain);
        cout << "Dame el tamaño n de la permutación para cifrar!: ";
        cin >> n;
        cout << "Dame una permutación para cifrar!: ";
        for (int i = 0; i < n; i++){
            cin >> nperm;
            piv.push_back(nperm);
        }   
        res = encipherPerm(plain, piv);
        cout << res;
        break;

    case 3:
        cout << "Dame un texto a descifrar muejeje: ";
        cin.ignore();
        getline(cin, ciph);
        cout << "Dame el tamaño de tu permutación para descifrar muejeje: ";
        cin >> n;
        cout << "Dame tu permutación para descifrar muejeje: ";
        for (int i = 0; i < n; i++){
            cin >> nperm;
            inv.push_back(nperm);
        }
        res = decipherPerm(ciph, inv);
        cout << res;
        break;

    default:
        break;
    }

    return 0;



   


    

    return 0;
}