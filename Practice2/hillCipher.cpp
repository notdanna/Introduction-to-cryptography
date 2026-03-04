#include "../functions.hpp"
using namespace std;

int main()
{
    int n = 0, a = 0, options = 0, result = 0;
    matriz2x2 Key = {{{0, 0}, {0, 0}}};
    matriz2x2 Kminus = {{{0, 0}, {0, 0}}};
    string M = "";
    string C = "";
    string filename;
    string encrypted;
    ofstream output;

    cout << "Elige una opción: \n";
    cout << "[1]: Calcular el inverso multiplicativo de a en Z* de n\n";
    cout << "[2]: Generar una llave válida para el cifrado de Hill\n";
    cout << "[3]: Generar la llave inversa de una llave de Hill\n";
    cout << "[4]: Cifrar con Hill cipher \n";
    cout << "[5]: Descifrar con Hill cifere \n";

    cin >> options;

    switch (options)
    {
    case 1:
        cout << "Dame un n!: ";
        cin >> n;
        cout << "Dame un a!: ";
        cin >> a;
        result = inverseM(n, a);

        cout << "El inverso multiplicativo de " << a << " en Z*" << n << " es: " << result << "\n";
        break;
    case 2:
        cout << "Dame un n!: ";
        cin >> n;
        Key = keyHillCipher(n);
        break;

    case 3:
        cout << "Dame un n!: ";
        cin >> n;
        cout << "Dame la llave de Hill (4 enteros)!:\n";
        cin >> Key.k[0][0] >> Key.k[0][1] >> Key.k[1][0] >> Key.k[1][1];
        Kminus = kminusone(n, Key);
        break;

    case 4:
        cout << "Dame un archivo a cifrar! ";   
        cin >> filename;
        M = readFile(filename);
        cout << "Dame la llave de Hill! \n";
        cin >> Key.k[0][0] >> Key.k[0][1] >> Key.k[1][0] >> Key.k[1][1];
        encrypted = hillCipher(M, Key);
        output.open("ciph.txt");
        output << encrypted;
        output.close();
        break;

    case 5:
        cout << "Dame un archivo a descifrar! ";   
        cin >> filename;
        C = readFile(filename);
        cout << "Dame tu llave de Hill! \n";
        cin >> Key.k[0][0] >> Key.k[0][1] >> Key.k[1][0] >> Key.k[1][1];
        hillDeciphered(C, Key);
        break;

    default:
        break;
    }

    return 0;
}

