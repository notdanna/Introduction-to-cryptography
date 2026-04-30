#include "../classfunc.hpp"

int main()
{
     int option;

     cout << "1. Deciphering" << endl;
     cout << "2. TBC con permutation" << endl;
     cout << "3. TBD con permutation" << endl;
     cout << "Elige una opcion: ";
     cin >> option;

     switch (option)
     {
     case 1:
     {
          string keyFilename, sFilename;
          string cipherText;

          cout << "Dame el nombre del archivo de la clave K: ";
          cin >> keyFilename;

          cout << "Dame el nombre del archivo de la S-box: ";
          cin >> sFilename;

          cout << "Dame el cipherText en hexadecimal (4 digitos): ";
          cin >> cipherText;

          unsigned short int K = Practica7::readKeyFromFile(keyFilename);
          vector<unsigned int> S = Practica7::readSFromFile(sFilename);
          unsigned short int C = stoul(cipherText, nullptr, 16);

          unsigned short int M = Practica8::tinyBlockDecipher(C, K, S);

          unsigned char m1 = M >> 8;
          unsigned char m2 = M & 0xFF;

          cout << "Plaintext en hexadecimal: "
               << uppercase << hex << setw(4) << setfill('0') << M << endl;

          cout << "Plaintext en caracteres ASCII imprimibles: "
               << static_cast<char>(m1) << static_cast<char>(m2) << endl;

          break;
     }

     case 2:
     {
          string keyFilename, sFilename;
          string plainText;

          cout << "Dame el nombre del archivo de la clave K: ";
          cin >> keyFilename;

          cout << "Dame el nombre del archivo de la S-box: ";
          cin >> sFilename;

          cout << "Dame el plaintext de 2 caracteres: ";
          cin >> plainText;

          unsigned short int K = Practica7::readKeyFromFile(keyFilename);
          vector<unsigned int> S = Practica7::readSFromFile(sFilename);

          unsigned char m1 = plainText[0];
          unsigned char m2 = plainText[1];

          unsigned short int M = (m1 << 8) | m2;

          vector<int> P = Practica8::pi(8);

          cout << "Permutacion P usada: ";
          for (int i = 0; i < 8; i++)
          {
               cout << P[i];
          }
          cout << endl;

          unsigned short int C = Practica8::tinyBlockCipherPermutation(M, K, S, P);

          cout << "Ciphertext en hexadecimal: "
               << uppercase << hex << setw(4) << setfill('0') << C << endl;

          break;
     }

     case 3:
     {
          string keyFilename, sFilename;
          string cipherText;
          vector<int> P;

          cout << "Dame el nombre del archivo de la clave K: ";
          cin >> keyFilename;

          cout << "Dame el nombre del archivo de la S-box: ";
          cin >> sFilename;

          cout << "Dame el cipherText en hexadecimal (4 digitos): ";
          cin >> cipherText;

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
          unsigned short int C = stoul(cipherText, nullptr, 16);

          unsigned short int M = Practica8::tinyBlockDecipherPermutation(C, K, S, P);

          unsigned char m1 = M >> 8;
          unsigned char m2 = M & 0xFF;

          cout << "Plaintext en hexadecimal: "
               << uppercase << hex << setw(4) << setfill('0') << M << endl;

          cout << "Plaintext en caracteres ASCII imprimibles: "
               << static_cast<char>(m1) << static_cast<char>(m2) << endl;

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