#include "../classfunc.hpp"

int main()
{
    int option;

    cout << ">>>-->> Proyecto 1: Tiny Block Cipher 16 - Counter Mode of Operation <<--<<<" << endl;
    cout << "1. Generate S-box" << endl;
    cout << "2. Generate Key" << endl;
    cout << "3. Cipher" << endl;
    cout << "4. Decipher" << endl;
    cout << "Elige una opcion: ";
    cin >> option;

    switch (option)
    {
    case 1:
    {
        Proyecto1::generateSbox(3);
        cout << "Se genero la S-box y se guardo en CAK_sbox.txt" << endl;
        break;
    }

    case 2:
    {
        unsigned short int K = Proyecto1::generateKey();

        cout << "Se genero la clave y se guardo en CAK_key.txt" << endl;
        cout << "Clave generada en hexadecimal: "
             << uppercase << hex << setw(4) << setfill('0') << K << endl;
        break;
    }

    case 3:
    {
        string plaintextFilename;
        string keyFilename;
        string outputFilename;

        cout << "Dame el nombre del archivo que contiene el plaintext: ";
        cin >> plaintextFilename;

        cout << "Dame el nombre del archivo que contiene la clave K: ";
        cin >> keyFilename;

        Proyecto1::CTRResult result = Proyecto1::ctrEncipher(plaintextFilename, keyFilename);

        cout << "Dame el nombre del archivo donde se guardara el counter y el ciphertext: ";
        cin >> outputFilename;

        Proyecto1::saveCTRResultToFile(result, outputFilename);

        cout << "Se guardo correctamente el counter y el ciphertext en base64 en el archivo: "
             << outputFilename << endl;

        break;
    }

    case 4:
    {
        string ciphertextFilename;
        string keyFilename;

        cout << "Dame el nombre del archivo que contiene el counter y el ciphertext: ";
        cin >> ciphertextFilename;

        cout << "Dame el nombre del archivo que contiene la clave K: ";
        cin >> keyFilename;

        Proyecto1::CTRDecipherResult result = Proyecto1::ctrDecipher(ciphertextFilename, keyFilename);

        cout << "Counter usado en hexadecimal: "
             << uppercase << hex << setw(4) << setfill('0') << result.counter << endl;

        cout << "Plaintext recuperado:" << endl;
        cout << result.plaintext << endl;

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