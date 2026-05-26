#include "../classfunc.hpp"

int main()
{
    int option;

    cout << "1. Cipher" << endl;
    cout << "2. Decipher" << endl;
    cout << "Elige una opcion: ";
    cin >> option;

    switch (option)
    {
    case 1:
    {
        string keyFilename, sFilename;
        string plainText;

        cout << "Dame el nombre del archivo de la clave K: ";
        cin >> keyFilename;

        cout << "Dame el nombre del archivo de la S-box: ";
        cin >> sFilename;

        cin.ignore();

        cout << "Dame el plaintext: ";
        getline(cin, plainText);

        vector<int> P = Practica8::pi(8);

        cout << "Permutacion P usada: ";
        for (int i = 0; i < 8; i++)
        {
            cout << P[i];
        }
        cout << endl;

        unsigned short int K = Practica7::readKeyFromFile(keyFilename);
        vector<unsigned int> S = Practica7::readSFromFile(sFilename);

        string cipherTextHex = Practica9::ctrEncipher(plainText, K, S, P);

        cout << "Ciphertext en hexadecimal: " << cipherTextHex << endl;

        break;
    }

    case 2:
    {
        string keyFilename, sFilename;
        string cipherTextHex;
        vector<int> P;

        cout << "Dame el nombre del archivo de la clave K: ";
        cin >> keyFilename;

        cout << "Dame el nombre del archivo de la S-box: ";
        cin >> sFilename;

        cout << "Dame el ciphertext en hexadecimal: ";
        cin >> cipherTextHex;

        cout << "Dame la permutacion P usada, valor por valor." << endl;
        for (int i = 0; i < 8; i++)
        {
            int value;
            cout << "P[" << i << "]: ";
            cin >> value;
            P.push_back(value);
        }

        unsigned short int K = Practica7::readKeyFromFile(keyFilename);
        vector<unsigned int> S = Practica7::readSFromFile(sFilename);

        string plainText = Practica9::ctrDecipher(cipherTextHex, K, S, P);

        cout << "Plaintext recuperado: " << plainText << endl;

        break;
    }

    default:
    {
        cout << "Opcion invalida." << endl;
        break;
    }
    }

    return 0;
}