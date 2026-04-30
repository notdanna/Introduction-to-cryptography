#include "../classfunc.hpp"

int main()
{
    Practica7::generateKey();
    Practica7::functionS(3);

    cout << "Se generó una clave y una S-box." << endl;

    string keyFilename, sFilename;
    string plainText;

    cout << "Dame el nombre del archivo de la clave K: ";
    cin >> keyFilename;

    cout << "Dame el nombre del archivo de la S-box: ";
    cin >> sFilename;

    cout << "Dame el plainText de 2 caracteres ASCII imprimibles: " << endl;
    cin >> plainText;

    unsigned short int K = Practica7::readKeyFromFile(keyFilename);
    vector<unsigned int> S = Practica7::readSFromFile(sFilename);
    unsigned short int M = ((unsigned char)plainText[0] << 8) | (unsigned char)plainText[1];

    unsigned short int C = Practica7::tinyBlockCipher(M, K, S);

    cout << "Ciphertext en hexadecimal: "
         << uppercase << hex << setw(4) << setfill('0') << C << endl;

    return 0;
}