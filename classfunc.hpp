#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <bitset>
#include <cmath>
#include <random>
#include <algorithm>

using namespace std;

// ============================================================
// Utilidades compartidas (usadas por todas las prácticas)
// ============================================================

class Utils
{
public:
    static void printV(const vector<int> &v)
    {
        cout << "[";
        for (size_t i = 0; i < v.size(); ++i)
            cout << v[i] << (i < v.size() - 1 ? ", " : "");
        cout << "]" << endl;
    }

    static int randomV(int min, int max)
    {
        static mt19937 gen(random_device{}());
        return uniform_int_distribution<int>{min, max}(gen);
    }

    static int gcd(int a, int b)
    {
        int vmin, result = 0;
        vmin = (a < b) ? a : b;
        for (int i = 1; i <= vmin; i++)
            if ((a % i == 0) && (b % i == 0))
                result = i;
        return result;
    }

    static vector<int> zStar(int n)
    {
        vector<int> zs;
        for (int i = 1; i <= n - 1; i++)
            if (gcd(n, i) == 1)
                zs.push_back(i);
        return zs;
    }

    static string readFile(string filename)
    {
        ifstream file(filename, ios::binary);
        stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
};

// ============================================================
// Práctica 1 — Cifrado Afín
// ============================================================

class Practica1
{
public:
    static map<int, char> getASCIIDictionary()
    {
        map<int, char> ascii_dict;
        for (int i = 32; i <= 126; ++i)
        {
            ascii_dict[i] = static_cast<char>(i);
            cout << ascii_dict[i] << ", ";
        }
        return ascii_dict;
    }

    static int aminusone(int n, int a)
    {
        int vmax = 0, vmin = 0, quotient = 0, reminder = 0, temp_k = 0, iter = 0;
        vector<int> S = {1, 0}, T = {0, 1}, Qu = {0};
        vector<int> i_epoch, Re;
        int inverse = 0;

        vmax = (a < n) ? n : a;
        vmin = (a < n) ? a : n;

        quotient = floor(vmax / vmin);
        reminder = vmax - vmin * quotient;

        i_epoch.push_back(iter);
        Re.push_back(vmax);
        Qu.push_back(quotient);

        iter = 1;

        while (reminder != 0)
        {
            vmax = vmin;
            vmin = reminder;
            temp_k = floor(vmax / vmin);
            reminder = vmax - (vmin * temp_k);
            i_epoch.push_back(iter);
            Re.push_back(vmax);
            Qu.push_back(temp_k);
            iter++;
        }

        i_epoch.push_back(iter);
        Re.push_back(0);

        for (int i = 0; i <= iter - 2; i++)
        {
            S.push_back(Qu[i + 1] * (-1) * S[i + 1] + S[i]);
            T.push_back(Qu[i + 1] * (-1) * T[i + 1] + T[i]);
        }

        for (int i = 0; i < (int)Re.size(); i++)
            cout << "i: " << i_epoch[i] << " Re: " << Re[i] << " Qu: " << Qu[i] << " S: " << S[i] << " T: " << T[i] << "\n";

        inverse = (Re[0] == a) ? S.back() : T.back();

        if (inverse < 0)
            return n - ((-inverse) % n);
        else
            return inverse;
    }

    static vector<int> kGeneration(int n)
    {
        vector<int> tmp, val;
        int a, b;
        tmp = Utils::zStar(n);

        a = tmp[Utils::randomV(0, tmp.size() - 1)];
        b = Utils::randomV(0, n - 1);

        val.push_back(a);
        val.push_back(b);

        cout << "a: " << a << "\n"
             << "b: " << b << "\n";

        return val;
    }

    static void affineCipher(string filename)
    {
        int const modulo = 95;
        int a = 0, b = 0;
        char c;
        vector<int> key;

        key = kGeneration(modulo);
        a = key[0], b = key[1];

        ifstream inputFile(filename);
        ofstream outputFile("ct_" + filename);

        while (inputFile >> noskipws >> c)
        {
            if (c == '\n')
            {
                outputFile << c;
                continue;
            }
            int x = static_cast<int>(c) - 32;
            int encrypted_val = (a * x + b) % modulo;
            char encrypted_char = static_cast<char>(encrypted_val + 32);
            outputFile << encrypted_char;
        }

        inputFile.close();
        outputFile.close();
    }

    static void affineDecipher(string filename, int a, int b)
    {
        int const modulo = 95;
        int decrypted_val = 0;
        char c;

        ifstream inputFile(filename);
        ofstream outputFile("pt_" + filename);

        a = aminusone(modulo, a);
        cout << "a^-1 mod n: " << a << "\n";

        while (inputFile >> noskipws >> c)
        {
            if (c == '\n')
            {
                outputFile << c;
                continue;
            }
            int x = static_cast<int>(c) - 32;

            if (x - b < 0)
                decrypted_val = modulo - (((-(x - b)) * a) % modulo);
            else
                decrypted_val = ((x - b) * a) % modulo;

            char decrypted_char = static_cast<char>(decrypted_val + 32);
            outputFile << decrypted_char;
        }

        inputFile.close();
        outputFile.close();
    }
};

// ============================================================
// Práctica 2 — Cifrado Hill
// ============================================================

struct matriz2x2
{
    int k[2][2];
};

class Practica2
{
public:
    static int inverseM(int n, int a)
    {
        int a_0, b_0, t_0, t, q, r, temp, res;
        a_0 = n;
        b_0 = a;
        t_0 = 0;
        t = 1;
        q = a_0 / b_0;
        r = a_0 - q * b_0;

        while (r > 0)
        {
            temp = t_0 - q * t;
            res = (temp < 0) ? n - ((-temp) % n) : temp % n;
            t_0 = t;
            t = res;
            a_0 = b_0;
            b_0 = r;
            q = a_0 / b_0;
            r = a_0 - q * b_0;
        }

        if (b_0 != 1)
        {
            cout << "No existe el inverso multiplicativo de " << a << " en Z*" << n << "\n";
            return 0;
        }
        return res;
    }

    static matriz2x2 keyHillCipher(int n)
    {
        int det_K = 0;
        int k_11, k_12, k_21, k_22;
        matriz2x2 Key;

        do
        {
            k_11 = Utils::randomV(0, n - 1);
            k_12 = Utils::randomV(0, n - 1);
            k_21 = Utils::randomV(0, n - 1);
            k_22 = Utils::randomV(0, n - 1);
            det_K = (k_11 * k_22 - k_12 * k_21) % n;
            if (det_K < 0)
                det_K += n;
        } while (Utils::gcd(n, det_K) != 1);

        cout << "Determinante de K: " << det_K << "\n";
        cout << "Z* de n: ";
        Utils::printV(Utils::zStar(n));

        Key.k[0][0] = k_11;
        Key.k[0][1] = k_12;
        Key.k[1][0] = k_21;
        Key.k[1][1] = k_22;

        cout << "La llave generada es: \n";
        cout << Key.k[0][0] << " " << Key.k[0][1] << "\n";
        cout << Key.k[1][0] << " " << Key.k[1][1] << "\n";

        return Key;
    }

    static matriz2x2 kminusone(int n, matriz2x2 Key)
    {
        matriz2x2 K_inv;
        int det_K = (Key.k[0][0] * Key.k[1][1] - Key.k[0][1] * Key.k[1][0]) % n;
        if (det_K < 0)
            det_K += n;

        int inv_K = inverseM(n, det_K);
        cout << "El inverso multiplicativo del determinante es: " << inv_K << "\n";

        K_inv.k[0][0] = (inv_K * Key.k[1][1]);
        K_inv.k[0][1] = (inv_K * -Key.k[0][1]);
        K_inv.k[1][0] = (inv_K * -Key.k[1][0]);
        K_inv.k[1][1] = (inv_K * Key.k[0][0]);

        if (K_inv.k[0][0] < 0)
            K_inv.k[0][0] = n - ((-K_inv.k[0][0]) % n);
        if (K_inv.k[0][1] < 0)
            K_inv.k[0][1] = n - ((-K_inv.k[0][1]) % n);
        if (K_inv.k[1][0] < 0)
            K_inv.k[1][0] = n - ((-K_inv.k[1][0]) % n);
        if (K_inv.k[1][1] < 0)
            K_inv.k[1][1] = n - ((-K_inv.k[1][1]) % n);

        cout << "La llave inversa es: \n";
        cout << K_inv.k[0][0] << " " << K_inv.k[0][1] << "\n";
        cout << K_inv.k[1][0] << " " << K_inv.k[1][1] << "\n";

        return K_inv;
    }

    static string hillCipher(string M, matriz2x2 key)
    {
        int const modulo = 95;
        char segundo;
        string res = "";

        cout << "Pares (p1, p2) -> Indices (m1, m2) -> Caracteres\n";

        for (int i = 0; i < (int)M.size(); i++)
        {
            if (M[i] == '\n')
            {
                res += '\n';
                continue;
            }

            int p1 = M[i] - 32;

            if (i + 1 >= (int)M.size() || M[i + 1] == '\n')
                segundo = ' ';
            else
            {
                segundo = M[i + 1];
                i++;
            }
            int p2 = segundo - 32;

            int m1 = (key.k[0][0] * p1 + key.k[1][0] * p2) % modulo;
            int m2 = (key.k[0][1] * p1 + key.k[1][1] * p2) % modulo;

            if (m1 < 0 || m2 < 0)
            {
                m1 = modulo - ((-(p1 * key.k[0][0] + p2 * key.k[1][0])) % modulo);
                m2 = modulo - ((-(p1 * key.k[0][1] + p2 * key.k[1][1])) % modulo);
            }

            char c1 = static_cast<char>(m1 + 32);
            char c2 = static_cast<char>(m2 + 32);

            cout << "(" << p1 << ", " << p2 << ") \t-> (" << m1 << ", " << m2 << ") \t-> [" << c1 << c2 << "]\n";

            res += c1;
            res += c2;
        }

        cout << "Resultado final: " << res << "\n";
        return res;
    }

    static string hillDeciphered(string C, matriz2x2 key)
    {
        matriz2x2 inverse = kminusone(95, key);
        string decrypted = hillCipher(C, inverse);

        cout << "Resultado final: " << decrypted << "\n";

        ofstream output("deciph.txt");
        output << decrypted;
        output.close();

        return decrypted;
    }
};

// ============================================================
// Práctica 3 — Cifrado por Permutación
// ============================================================

class Practica3
{
public:
    static vector<int> pi(int n)
    {
        vector<int> PI;
        vector<bool> X(n, false);

        do
        {
            int m = Utils::randomV(1, n);
            if (X[m - 1] == false)
            {
                PI.push_back(m);
                X[m - 1] = true;
            }
        } while ((int)PI.size() < n);

        return PI;
    }

    static vector<int> piInverse(vector<int> perm)
    {
        int n = perm.size();
        vector<int> inverse(n);
        for (int i = 0; i <= n - 1; i++)
        {
            int posix = perm[i];
            inverse[posix - 1] = i + 1;
        }
        return inverse;
    }

    static string encipherPerm(string m, vector<int> PI)
    {
        vector<char> mV(m.begin(), m.end());
        int lenMess = m.size();
        int lenPerm = PI.size();
        string ciph = "";

        if (lenMess % lenPerm != 0)
        {
            int residuo = lenMess % lenPerm;
            int completeo = lenPerm - residuo;
            for (int i = 0; i < completeo; i++)
                mV.push_back('X');
            lenMess = lenMess + completeo;
        }

        int inicioBloque = 0;
        while (inicioBloque < lenMess)
        {
            for (int i = 0; i < lenPerm; i++)
            {
                int posix = PI[i];
                char caracter = mV[inicioBloque + (posix - 1)];
                ciph += caracter;
            }
            inicioBloque = inicioBloque + lenPerm;
        }

        return ciph;
    }

    static string decipherPerm(string c, vector<int> PI)
    {
        vector<int> inverse = piInverse(PI);
        vector<char> cV(c.begin(), c.end());
        int lenMess = c.size();
        int lenPerm = PI.size();
        string plain = "";

        int inicioBloque = 0;
        while (inicioBloque < lenMess)
        {
            for (int i = 0; i < lenPerm; i++)
            {
                int posix = inverse[i];
                char caracter = cV[inicioBloque + (posix - 1)];
                plain += caracter;
            }
            inicioBloque = inicioBloque + lenPerm;
        }

        return plain;
    }
};

// ============================================================
// Práctica 5 — Operaciones a nivel de bits
// ============================================================

class Practica5
{
public:
    static void warmingExercise()
    {
        unsigned char data = 'K';

        printf("1) Initial value\n");
        printf("Character: %c\n", data);
        printf("Hexadecimal: 0x%X\n", data);
        printf("Integer: %u\n\n", data);

        printf("2) Left shift\n");
        for (int i = 0; i < 8; i++)
        {
            data = data << 1;
            printf("Shift %d\n", i + 1);
            printf("Character: %c\n", data);
            printf("Hexadecimal: 0x%X\n", data);
            printf("Integer: %u\n\n", data);
        }

        data = 'A';
        printf("3) Right shift\n");
        for (int i = 0; i < 8; i++)
        {
            data = data >> 1;
            printf("Shift %d\n", i + 1);
            printf("Character: %c\n", data);
            printf("Hexadecimal: 0x%X\n", data);
            printf("Integer: %u\n\n", data);
        }

        unsigned char v1 = 'D';
        unsigned char v2 = 'M';
        unsigned char result_and = v1 & v2;
        unsigned char result_or = v1 | v2;
        unsigned char result_xor = v1 ^ v2;

        printf("4) Bitwise operations\n");
        printf("v1 = %c -> 0x%X -> %u\n", v1, v1, v1);
        printf("v2 = %c -> 0x%X -> %u\n\n", v2, v2, v2);
        printf("AND: 0x%X -> %u\n", result_and, result_and);
        printf("OR : 0x%X -> %u\n", result_or, result_or);
        printf("XOR: 0x%X -> %u\n\n", result_xor, result_xor);

        unsigned char data2 = 'R';
        unsigned char mask = 0x80;
        unsigned char result = data2 & mask;

        printf("5) Most significant bit\n");
        printf("data2 = %c -> 0x%X -> %u\n", data2, data2, data2);
        printf("Mask  = 0x%X\n", mask);
        printf("Result: 0x%X -> %u\n\n", result, result);

        data2 = 'V';
        mask = 0x0F;
        result = data2 & mask;

        printf("6) Four least significant bits\n");
        printf("data2 = %c -> 0x%X -> %u\n", data2, data2, data2);
        printf("Mask  = 0x%X\n", mask);
        printf("Result: 0x%X -> %u\n", result, result);
    }

    static unsigned int getNthBit(unsigned int num, unsigned int n)
    {
        unsigned int mask = 1;
        for (int i = 1; i <= (int)n; i++)
            mask = mask << 1;

        bitset<32> rawNumber(num);
        cout << "Número en binario: " << rawNumber << endl;
        cout << "El bit " << n << " es: " << (((num & mask)) ? 1 : 0) << endl;

        return (num & mask) ? 1 : 0;
    }

    static unsigned int setNthBit(unsigned int num, unsigned int n)
    {
        unsigned int bin = 0;
        unsigned int mask = 1;
        for (int i = 1; i <= (int)n; i++)
            mask = mask << 1;

        bin = (num | mask);

        bitset<32> numbere(num);
        bitset<32> answere(bin);

        cout << endl
             << "Posición del bit a modificar: " << n;
        cout << endl
             << "El nuevo entero es: " << bin;
        cout << endl
             << "Número original: " << numbere << endl
             << "Numero modificado: " << answere;

        return (num | mask);
    }

    static unsigned int countLeadingZeros(unsigned int num)
    {
        int counter = 0;
        unsigned int isOne = 0;
        unsigned int modifiedNum = num;

        isOne = getNthBit(modifiedNum, 31);

        if (num == 0)
            return 32;

        while (isOne == 0)
        {
            modifiedNum = modifiedNum << 1;
            counter++;
            isOne = getNthBit(modifiedNum, 31);
        }

        bitset<32> rawNumber(num);
        cout << "Número original: " << rawNumber << endl;
        cout << "Cantidad de ceros:" << counter;

        return counter;
    }
};

// ============================================================
// Práctica 6 — Tabla de sustitución / función S
// ============================================================

class Practica6
{
public:
    static vector<char> tableSubstitution()
    {
        vector<char> S;
        vector<char> hexA = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
        vector<bool> X(hexA.size(), false);

        do
        {
            int pos = Utils::randomV(0, hexA.size() - 1);
            if (X[pos] == false)
            {
                S.push_back(hexA[pos]);
                X[pos] = true;
            }
        } while (hexA.size() != S.size());

        for (char c : hexA)
            cout << c << " ";
        cout << endl;
        for (char k : S)
            cout << k << " ";

        return S;
    }

    static string binaryRep(unsigned int num, int bits)
    {
        string r = "";
        for (int i = bits - 1; i >= 0; i--)
            r += ((num >> i) & 1) ? '1' : '0';
        return r;
    }

    static vector<unsigned int> functionS(int n)
    {
        vector<unsigned int> z, S;
        // nuestra cadenas l pueden ser de 4, 8, 16, 32 bits
        // l = 2^n , donde n puede ser 2,3,4,5
        // combinaciones = 2^l

        int l = 1 << n;
        int combinations = 1 << l;

        for (int i = 0; i < combinations; i++)
            z.push_back(i);

        vector<bool> X(z.size(), false);

        do
        {
            int pos = Utils::randomV(0, z.size() - 1);
            if (X[pos] == false)
            {
                S.push_back(z[pos]);
                X[pos] = true;
            }
        } while (z.size() != S.size());

        // Guardar en archivo
        // Si el archivo existe con este nombre, se le agrega un número al final para no sobreescribirlo
        int counter = 0;
        string filename = "S-BOX_tabla.txt";

        ifstream check(filename);
        while (check.good())
        {
            check.close();
            counter++;
            filename = "S-BOX_" + to_string(counter) + "_tabla.txt";
            check.open(filename);
        }
        check.close();

        ofstream outputFile(filename);

        outputFile << "z : S" << endl;
        for (int i = 0; i < z.size(); i++)
        {
            outputFile << z[i] << " : " << S[i] << endl;
        }

        outputFile << "z : S" << endl;
        for (int i = 0; i < z.size(); i++)
        {
            outputFile << binaryRep(z[i], l) << " : " << binaryRep(S[i], l) << endl;
        }

        outputFile.close();

        /*
        cout << "z : S" << endl;
                for (int i = 0; i < z.size(); i++)
                    cout << z[i] << " : " << S[i] << endl;

                cout << "z: ";
                for (unsigned int c : z)
                    cout << binaryRep(c, l) << " ";
                cout << endl;

                cout << "S: ";
                for (unsigned int k : S)
                    cout << binaryRep(k, l) << " ";
                cout << endl;

        */

        return S;
    }

    static void subsBlocks(vector<char> M, int n)
    {
        vector<unsigned int> ans;

        if (n == 2)
        {
            vector<unsigned int> S4 = functionS(2);

            unsigned int result = 0;
            for (char c : M)
            {
                unsigned char x = (unsigned char)c;

                unsigned int firstbits = x >> 4;  // 4 MSB
                unsigned int lastbits = x & 0x0F; // 4 LSB

                unsigned int firstS = S4[firstbits];
                unsigned int lastS = S4[lastbits];

                ans.push_back(firstS);
                ans.push_back(lastS);

                cout << "Caracter: " << binaryRep(c, 8) << " -> " << (unsigned int)c << endl;
                cout << "firstbytes: " << binaryRep(firstbits, 4) << " -> " << firstbits << endl;
                cout << "lastbytes: " << binaryRep(lastbits, 4) << " -> " << lastbits << endl;
                cout << "firstS: " << binaryRep(firstS, 4) << " -> " << firstS << endl;
                cout << "lastS: " << binaryRep(lastS, 4) << " -> " << lastS << endl
                     << endl;

                cout << "Hexadecimal fS: 0x" << hex << firstS << endl;
                cout << "Hexadecimal lS: 0x" << lastS << dec << endl
                     << endl;

                cout << "Sustitución hexadecimal: 0x";
                for (unsigned int x : ans)
                {
                    cout << hex << x;
                }
                cout << endl
                     << endl;
            }
        }
        else if (n == 3)
        {

            vector<unsigned int> S8 = functionS(3);

            for (char c : M)
            {
                unsigned char x = (unsigned char)c;
                unsigned int substituted = S8[x];

                cout << "Caracter: "
                     << binaryRep(x, 8) << " -> "
                     << dec << (unsigned int)x << endl;

                cout << "Sustitucion:"
                     << binaryRep(substituted, 8) << " -> "
                     << dec << substituted << endl;

                ans.push_back(substituted);

                cout << "Sustitucion hexadecimal: 0x";
                for (unsigned int y : ans)
                {
                    cout << hex << y;
                }
                cout << dec << endl;
            }
        }
    }

    static void subsK(unsigned short K)
    {
        vector<unsigned int> S1 = functionS(3);
        vector<unsigned int> S2 = functionS(3);

        unsigned short firstbits = K >> 8;
        unsigned short lastbits = K & 0xFF;

        unsigned short firstS = S1[firstbits];
        unsigned short lastS = S2[lastbits];

        unsigned short ans = (firstS << 8) | lastS;

        cout << "Real K: 0x" << hex << K << endl
             << endl;
        cout << "firstbits: " << binaryRep(firstbits, 8) << " -> " << dec << firstbits << endl;
        cout << "lastbits: " << binaryRep(lastbits, 8) << " -> " << lastbits << endl;
        cout << "firstS1: " << binaryRep(firstS, 8) << " -> " << firstS << endl;
        cout << "lastS2: " << binaryRep(lastS, 8) << " -> " << lastS << endl
             << endl;

        cout << "firstbits en hexadecimal: " << hex << firstbits << endl;
        cout << "lastbits en hexadecimal: " << lastbits << endl;
        cout << "firstS1: " << firstS << endl;
        cout << "lastS2: " << lastS << endl
             << endl;

        cout << "Sustitución hexadecimal: 0x" << ans << endl;
    }

    static void subsKd(unsigned short K)
    {

        vector<unsigned int> S = functionS(2);
        unsigned short ans = 0;
        int counter = 0;

        cout << "Real K: 0x" << hex << K << endl
             << endl;

        for (int i = 3; i >= 0; i--)
        {
            // 0000 0000 0000 0000
            counter++;
            unsigned int block = (K >> (i * 4) & 0xF);
            unsigned int subs = S[block];
            ans = ans | (subs << (i * 4));

            cout << "Bloque " << counter << ": " << binaryRep(block, 4) << " -> " << block << endl;
            cout << "Sustitución: " << binaryRep(subs, 4) << " -> " << subs << endl;
        }

        cout << "Sustitución hexadecimal: 0x" << hex << ans << endl;
    }
};

// ===================================
// Práctica 7 — Tiny Block Cipher
// ===================================

class Practica7
{
public:
    // Key Expansion
    static vector<unsigned int> keyExpansion(unsigned short int K, const vector<unsigned int> &S)
    {
        vector<unsigned int> W;

        unsigned short int w0 = K >> 8;
        W.push_back(w0);

        unsigned short int w1 = K & 0xFF;
        W.push_back(w1);

        cout << "Soy w0: " << uppercase << hex << setw(2) << setfill('0') << w0 << endl;
        cout << "Soy w1: " << uppercase << hex << setw(2) << setfill('0') << w1 << endl;

        // r(w1)
        unsigned short int R_tmp_1 = w1 >> 4;
        unsigned short int R_tmp_2 = w1 & 0x0F;
        unsigned short int R = (R_tmp_2 << 4) | R_tmp_1;

        unsigned short int subs = S[R];

        // op1
        unsigned short int w2 = w0 ^ 0x80 ^ subs;
        W.push_back(w2);
        cout << "Soy w2: " << uppercase << hex << setw(2) << setfill('0') << w2 << endl;

        // op2
        unsigned short int w3 = w2 ^ w1;
        W.push_back(w3);
        cout << "Soy w3: " << uppercase << hex << setw(2) << setfill('0') << w3 << endl;

        // r(w3)
        R_tmp_1 = w3 >> 4;
        R_tmp_2 = w3 & 0x0F;
        R = (R_tmp_2 << 4) | R_tmp_1;

        subs = S[R];

        // op3
        unsigned short int w4 = w2 ^ 0x30 ^ subs;
        W.push_back(w4);
        cout << "Soy w4: " << uppercase << hex << setw(2) << setfill('0') << w4 << endl;

        // op4
        unsigned short int w5 = w4 ^ w3;
        W.push_back(w5);
        cout << "Soy w5: " << uppercase << hex << setw(2) << setfill('0') << w5 << endl;

        return W;
    }

    // Tiny block cipher
    // Ejercicio 1 a)
    static unsigned short int generateKey()
    {
        unsigned short int K = Utils::randomV(0, 65535);

        int counter = 0;
        string filename = "KEY.txt";

        ifstream check(filename);
        while (check.good())
        {
            check.close();
            counter++;
            filename = "KEY_" + to_string(counter) + ".txt";
            check.open(filename);
        }
        check.close();

        ofstream outputFile(filename);

        outputFile << uppercase << hex << setw(4) << setfill('0') << K << endl;

        outputFile.close();

        return K;
    }

    // Ejercicio 1 b)
    static vector<unsigned int> functionS(int n)
    {
        vector<unsigned int> z, S;

        // l = 2^n
        // combinations = 2^l
        int l = 1 << n;
        int combinations = 1 << l;

        for (int i = 0; i < combinations; i++)
            z.push_back(i);

        vector<bool> X(z.size(), false);

        do
        {
            int pos = Utils::randomV(0, z.size() - 1);
            if (X[pos] == false)
            {
                S.push_back(z[pos]);
                X[pos] = true;
            }
        } while (z.size() != S.size());

        // Guardar en archivo
        // Si el archivo existe con este nombre, se le agrega un número al final para no sobreescribirlo
        int counter = 0;
        string filename = "S-BOX_tabla.txt";

        ifstream check(filename);
        while (check.good())
        {
            check.close();
            counter++;
            filename = "S-BOX_" + to_string(counter) + "_tabla.txt";
            check.open(filename);
        }
        check.close();

        ofstream outputFile(filename);

        for (int i = 0; i < S.size(); i++)
        {
            outputFile << uppercase << hex << setw(2) << setfill('0') << S[i] << endl;
        }

        outputFile.close();

        return S;
    }

    // Ejercicio 2
    static unsigned short int readKeyFromFile(const string &filename)
    {
        ifstream inputFile(filename);

        if (!inputFile.is_open())
        {
            cerr << "No se pudo abrir el archivo de la clave." << endl;
            return 0;
        }

        unsigned short int K;
        inputFile >> hex >> K;

        inputFile.close();
        return K;
    }

    static vector<unsigned int> readSFromFile(const string &filename)
    {
        ifstream inputFile(filename);
        vector<unsigned int> S;

        if (!inputFile.is_open())
        {
            cerr << "No se pudo abrir el archivo de la S-box." << endl;
            return S;
        }

        unsigned int value;
        while (inputFile >> hex >> value)
        {
            S.push_back(value);
        }

        inputFile.close();
        return S;
    }

    static unsigned short int tinyBlockCipher(unsigned short int M, unsigned short int K, const vector<unsigned int> &S)
    {
        vector<unsigned int> W = keyExpansion(K, S);

        unsigned short int K0 = (W[0] << 8) | W[1];
        unsigned short int K1 = (W[2] << 8) | W[3];
        unsigned short int K2 = (W[4] << 8) | W[5];

        vector<unsigned short int> roundKeys;
        roundKeys.push_back(K0);
        roundKeys.push_back(K1);
        roundKeys.push_back(K2);

        for (int i = 0; i < 3; i++)
        {
            M = M ^ roundKeys[i];

            unsigned int m1 = M >> 8;
            unsigned int m2 = M & 0xFF;

            m1 = S[m1];
            m2 = S[m2];

            M = (m1 << 8) | m2;
        }

        unsigned short int C = M;
        return C;
    }
};

// ===================================
// Práctica 8 — Tiny Block Cipher II
// ===================================

class Practica8
{
public:
    // Part 1
    // S-BOX inverse
    static vector<unsigned int> functionSinverse(vector<unsigned int> S)
    {
        int n = S.size();
        vector<unsigned int> S_inv(n);
        for (int i = 0; i < n; i++)
        {
            unsigned int posix = S[i];
            S_inv[posix] = i;
        }

        // Guardar en archivo
        // Si el archivo existe con este nombre, se le agrega un número al final para no sobreescribirlo
        int counter = 0;
        string filename = "S-BOX-INVERSE_tabla.txt";

        ifstream check(filename);
        while (check.good())
        {
            check.close();
            counter++;
            filename = "S-BOX-INVERSE_" + to_string(counter) + "_tabla.txt";
            check.open(filename);
        }
        check.close();

        ofstream outputFile(filename);

        for (int i = 0; i < S_inv.size(); i++)
        {
            outputFile << uppercase << hex << setw(2) << setfill('0') << S_inv[i] << endl;
        }

        outputFile.close();

        return S_inv;
    }

    // Tiny block decipher
    static unsigned short int tinyBlockDecipher(unsigned short int C, unsigned short int K, const vector<unsigned int> &S)
    {
        vector<unsigned int> W = Practica7::keyExpansion(K, S);

        unsigned short int K0 = (W[0] << 8) | W[1];
        unsigned short int K1 = (W[2] << 8) | W[3];
        unsigned short int K2 = (W[4] << 8) | W[5];

        vector<unsigned short int> roundKeys;
        roundKeys.push_back(K0);
        roundKeys.push_back(K1);
        roundKeys.push_back(K2);

        // S-BOX inversa
        vector<unsigned int> S_inv = functionSinverse(S);

        // Para descifrar, se aplican las rondas en orden inverso y con la S-box inversa
        for (int i = 2; i >= 0; i--)
        {
            unsigned int c1 = C >> 8;
            unsigned int c2 = C & 0xFF;

            c1 = S_inv[c1];
            c2 = S_inv[c2];

            C = (c1 << 8) | c2;

            C = C ^ roundKeys[i];
        }

        unsigned short int M = C;
        return M;
    }

    // Part 2
    // Exercise 1
    static vector<int> pi(int n)
    {
        vector<int> PI;
        vector<bool> X(n, false);

        do
        {
            int m = Utils::randomV(0, n - 1);

            if (X[m] == false)
            {
                PI.push_back(m);
                X[m] = true;
            }

        } while ((int)PI.size() < n);

        return PI;
    }

    static unsigned int getNthBit(unsigned int num, unsigned int n)
    {
        unsigned int mask = 1 << n;
        return (num & mask) ? 1 : 0;
    }

    static unsigned int setNthBit(unsigned int num, unsigned int n)
    {
        unsigned int mask = 1 << n;
        return num | mask;
    }

    static unsigned char permutation(const vector<int> &P, unsigned char s)
    {
        unsigned char P_S = 0;

        for (int i = 0; i < 8; i++)
        {
            unsigned int bit = getNthBit(s, P[i]);

            if (bit == 1)
            {
                P_S = setNthBit(P_S, 7 - i);
            }
        }

        return P_S;
    }

    // Exercise 2
    static unsigned short int tinyBlockCipherPermutation(unsigned short int M, unsigned short int K, const vector<unsigned int> &S, const vector<int> &P)
    {
        vector<unsigned int> W = Practica7::keyExpansion(K, S);

        unsigned short int K0 = (W[0] << 8) | W[1];
        unsigned short int K1 = (W[2] << 8) | W[3];
        unsigned short int K2 = (W[4] << 8) | W[5];

        vector<unsigned short int> roundKeys;
        roundKeys.push_back(K0);
        roundKeys.push_back(K1);
        roundKeys.push_back(K2);

        for (int i = 0; i < 3; i++)
        {
            M = M ^ roundKeys[i];

            unsigned char m1 = M >> 8;
            unsigned char m2 = M & 0xFF;

            m1 = S[m1];
            m2 = S[m2];

            m1 = permutation(P, m1);
            m2 = permutation(P, m2);

            M = (m1 << 8) | m2;
        }

        unsigned short int C = M;
        return C;
    }

    // Exercise 3
    static unsigned char inversePermutation(const vector<int> &P, unsigned char s)
    {
        unsigned char original = 0;

        for (int i = 0; i < 8; i++)
        {
            unsigned int bit = getNthBit(s, 7 - i);

            if (bit == 1)
            {
                original = setNthBit(original, P[i]);
            }
        }

        return original;
    }

    static unsigned short int tinyBlockDecipherPermutation(unsigned short int C, unsigned short int K, const vector<unsigned int> &S, const vector<int> &P)
    {
        vector<unsigned int> W = Practica7::keyExpansion(K, S);

        unsigned short int K0 = (W[0] << 8) | W[1];
        unsigned short int K1 = (W[2] << 8) | W[3];
        unsigned short int K2 = (W[4] << 8) | W[5];

        vector<unsigned short int> roundKeys;
        roundKeys.push_back(K0);
        roundKeys.push_back(K1);
        roundKeys.push_back(K2);

        vector<unsigned int> S_inv = functionSinverse(S);

        for (int i = 2; i >= 0; i--)

        {
            unsigned char c1 = C >> 8;
            unsigned char c2 = C & 0xFF;

            c1 = inversePermutation(P, c1);
            c2 = inversePermutation(P, c2);

            c1 = S_inv[c1];
            c2 = S_inv[c2];

            C = (c1 << 8) | c2;

            C = C ^ roundKeys[i];
        }
        unsigned short int M = C;
        return M;
    }
};
