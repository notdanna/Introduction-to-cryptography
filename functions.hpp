#include "libraries.hpp"

using namespace std;

// ----------------------
// Práctica 1
// ----------------------

map<int, char> getASCIIDictionary()
{
    map<int, char> ascii_dict;
    for (int i = 32; i <= 126; ++i)
    {
        // Este metodo transforma el numero actual en su caracter ascii
        ascii_dict[i] = static_cast<char>(i);
        cout << ascii_dict[i] << ", ";
    }
    return ascii_dict;
}

void printV(const vector<int> &v)
{
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i)
        cout << v[i] << (i < v.size() - 1 ? ", " : "");
    cout << "]" << endl;
}

int randomV(int min, int max)
{
    static std::mt19937 gen(std::random_device{}());
    return std::uniform_int_distribution<int>{min, max}(gen);
}

int gcd(int a, int b)
{
    int vmin, result = 0;

    vmin = (a < b) ? a : b;

    for (int i = 1; i <= vmin; i++)
        if ((a % i == 0) && (b % i == 0))
            result = i;

    return result;
}

int aminusone(int n, int a)
{
    int vmax = 0, vmin = 0, quotient = 0, reminder = 0, temp_k = 0, iter = 0;
    vector<int> S = {1, 0}, T = {0, 1}, Qu = {0};
    vector<int> i_epoch, Re;
    int inverse = 0;

    vmax = (a < n) ? n : a;
    vmin = (a < n) ? a : n;

    quotient = floor(vmax / vmin);
    // vmax - vmin * quotient == vmax % quotient
    reminder = vmax - vmin * quotient;

    i_epoch.push_back(iter);
    Re.push_back(vmax);
    // Qu.push_back(0);
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

    // Agregar el 0 del reminder
    Re.push_back(0);

    // Los casos 1 y 2 ya no son casos especiales porque está lleno el vector de S y T.
    // Caso 3 hasta la última iteración
    for (int i = 0; i <= iter - 2; i++)
    {
        S.push_back(Qu[i + 1] * (-1) * S[i + 1] + S[i]);
        T.push_back(Qu[i + 1] * (-1) * T[i + 1] + T[i]);
    }

    // Imprimir la pseudomatriz:)
    for (int i = 0; i < Re.size(); i++)
    {
        cout << "i: " << i_epoch[i] << " Re: " << Re[i] << " Qu: " << Qu[i] << " S: " << S[i] << " T: " << T[i] << "\n";
    }

    // Si "a" está en Re[0] entonces regresar S[iter], si no, regresar T[iter], pero en positivo.
    inverse = (Re[0] == a) ? S.back() : T.back();

    if (inverse < 0)
    {
        // - 11 mod 28 = 28 - (-(-11)mod 28) = 28 - (11 mod 28)
        return n - ((-inverse) % n);
    }
    else
    {
        return inverse;
    }
}

vector<int> zStar(int n)
{

    vector<int> zs;

    for (int i = 1; i <= n - 1; i++)
        if (gcd(n, i) == 1)
            zs.push_back(i);

    return zs;
}

vector<int> kGeneration(int n)
{
    vector<int> tmp, val;
    int a, b;
    tmp = zStar(n);

    // Ir a una posicion aleatoria de zStar y la ponemos en a
    a = tmp[randomV(0, tmp.size() - 1)];
    b = randomV(0, n - 1);

    val.push_back(a);
    val.push_back(b);

    cout << "a: " << a << "\n"
         << "b: " << b << "\n";

    return val;
}

void affineCipher(string filename)
{
    // El modulo seria del tamaño del alfabeto:  126 - 32 + 1 = 95
    // (a * x + b) mod n
    int const modulo = 95;
    int a = 0, b = 0;
    char c;
    vector<int> key;

    // Generación de clave aleatoria
    key = kGeneration(modulo);
    a = key[0], b = key[1];

    // Para obtener el archivo se usa ifstream
    ifstream inputFile(filename);
    ofstream outputFile("ct_" + filename);

    // noskipws evita que ignore los espacios en blanco
    // La condicion del while está implicita, si no hay más caracteres, el while se detiene
    while (inputFile >> noskipws >> c)
    {
        // Para no cifrar el salto de línea
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

void affineDecipher(string filename, int a, int b)
{
    int const modulo = 95;
    int decrypted_val = 0;
    char c;

    ifstream inputFile(filename);
    ofstream outputFile("pt_" + filename);

    // Sacamos el inverso de a y lo ponemos en a jeje
    a = aminusone(modulo, a);
    cout << "a^-1 mod n: " << a << "\n";

    while (inputFile >> noskipws >> c)
    {

        // Para no tomar en cuenta el salto de línea
        if (c == '\n')
        {
            outputFile << c;
            continue;
        }

        int x = static_cast<int>(c) - 32;

        // int val = ((x - b) * a) % modulo;
        // if (val < 0) val += modulo;

        if (x - b < 0)
        {
            //((0-3) * 15) mod 26 = (-3*15) mod 26 = -45 mod 26 = 26 - (45 mod 26)
            decrypted_val = modulo - (((-(x - b)) * a) % modulo);
        }
        else
        {
            decrypted_val = ((x - b) * a) % modulo;
        }

        char decrypted_char = static_cast<char>(decrypted_val + 32);

        outputFile << decrypted_char;
    }

    inputFile.close();
    outputFile.close();
}

// ----------------------
// Práctica 2
// ----------------------

struct matriz2x2
{
    int k[2][2];
};

string readFile(string filename)
{
    ifstream file(filename, ios::binary);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int inverseM(int n, int a)
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
        if (temp < 0)
        {

            res = n - ((-temp) % n);
        }
        else
        {
            res = temp % n;
        }

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
    else
        return res;
}

matriz2x2 keyHillCipher(int n)
{
    int det_K = 0;
    int k_11, k_12, k_21, k_22;
    matriz2x2 Key;

    do
    {
        k_11 = randomV(0, n - 1);
        k_12 = randomV(0, n - 1);
        k_21 = randomV(0, n - 1);
        k_22 = randomV(0, n - 1);
        det_K = (k_11 * k_22 - k_12 * k_21) % n;
        if (det_K < 0)
        {
            det_K += n;
        }

    } while (gcd(n, det_K) != 1);

    cout << "Determinante de K: " << det_K << "\n";
    cout << "Z* de n: ";
    vector<int> star = zStar(n);
    printV(star);

    // Guardamos en Key a k_11, k_12, k_21 y k_22
    Key.k[0][0] = k_11;
    Key.k[0][1] = k_12;
    Key.k[1][0] = k_21;
    Key.k[1][1] = k_22;

    cout << "La llave generada es: \n";
    cout << Key.k[0][0] << " " << Key.k[0][1] << "\n";
    cout << Key.k[1][0] << " " << Key.k[1][1] << "\n";

    return Key;
}

matriz2x2 kminusone(int n, matriz2x2 Key)
{
    matriz2x2 K_inv;
    int det_K = 0;

    det_K = (Key.k[0][0] * Key.k[1][1] - Key.k[0][1] * Key.k[1][0]) % n;
    if (det_K < 0)
    {
        det_K += n;
    }

    int inv_K = inverseM(n, det_K);

    cout << "El inverso multiplicativo del determinante es: " << inv_K << "\n";

    K_inv.k[0][0] = (inv_K * Key.k[1][1]);
    K_inv.k[0][1] = (inv_K * -Key.k[0][1]);
    K_inv.k[1][0] = (inv_K * -Key.k[1][0]);
    K_inv.k[1][1] = (inv_K * Key.k[0][0]);

    // res = n - ((-temp) % n);
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

string hillCipher(string M, matriz2x2 key)
{

    int const modulo = 95;
    char segundo;
    string res = "";

    // if (M.size() % 2 != 0) M += ' '; // Rellenamos con espacio si el mensaje tiene longitud impar

    cout << "Pares (p1, p2) -> Indices (m1, m2) -> Caracteres\n";

    // for (int i = 0; i < M.size(); i += 2)
    //{
    // int p1 = M[i] - 32;
    // int p2 = M[i+1] - 32;
    for (int i = 0; i < M.size(); i++)
    {
        // Si es salto de linea, lo mantenemos sin cifrar y continuamos
        if (M[i] == '\n')
        {
            res += '\n';
            continue;
        }

        // Caracter 1 (se mantiene como lo teniamos antes)
        int p1 = M[i] - 32;

        if (i + 1 >= M.size() || M[i + 1] == '\n')
        {
            segundo = ' '; // Rellenamos con espacio si no hay pareja o si hay salto de línea
        }
        else
        {
            segundo = M[i + 1];
            i++; // consumimos la posicion para iniciar en [2] en el for (skipeamos el siguiente carácter)
        }
        // Caracter 2
        int p2 = segundo - 32;

        // Multiplicación de matriz: C = K * P
        int m1 = (key.k[0][0] * p1 + key.k[1][0] * p2) % modulo;
        int m2 = (key.k[0][1] * p1 + key.k[1][1] * p2) % modulo;

        // Normalización de negativos
        if (m1 < 0 || m2 < 0)
        {
            m1 = modulo - ((-(p1 * key.k[0][0] + p2 * key.k[1][0])) % modulo);
            m2 = modulo - ((-(p1 * key.k[0][1] + p2 * key.k[1][1])) % modulo);
        }

        char c1 = static_cast<char>(m1 + 32);
        char c2 = static_cast<char>(m2 + 32);

        // Print limpio en una sola línea por par
        cout << "(" << p1 << ", " << p2 << ") \t-> (" << m1 << ", " << m2 << ") \t-> [" << c1 << c2 << "]\n";

        res += c1;
        res += c2;
    }

    cout << "Resultado final: " << res << "\n";
    return res;
}

string hillDeciphered(string C, matriz2x2 key)
{
    matriz2x2 inverse = kminusone(95, key);
    string decrypted = hillCipher(C, inverse);

    cout << "Resultado final: " << decrypted << "\n";

    ofstream output("deciph.txt");
    output << decrypted;
    output.close();

    return decrypted;
}

// ----------------------
// Práctica 3
// ----------------------

vector<int> pi(int n)
{
    vector<int> PI;
    // PI.reserve(n);
    vector<bool> X(n, false);

    do
    {
        int m = randomV(1, n);
        if (X[m - 1] == false)
        {
            PI.push_back(m);
            X[m - 1] = true;
        }

    } while (PI.size() < n);

    return PI;
}

vector<int> piInverse(vector<int> perm)
{
    int n = perm.size();
    vector<int> inverse(n);
    // inverse.reserve(n);
    for (int i = 0; i <= n - 1; i++)
    {
        int posix = perm[i];
        inverse[posix - 1] = i + 1;
    }

    return inverse;
}

string encipherPerm(string m, vector<int> PI)
{

    vector<char> mV(m.begin(), m.end());
    int lenMess = m.size();
    int lenPerm = PI.size();

    string ciph = "";

    if (lenMess % lenPerm != 0)
    {
        // residuo = 16 % 5 = 1
        int residuo = lenMess % lenPerm;
        // completeo = 5 - 1 = 4
        int completeo = lenPerm - residuo;

        for (int i = 0; i < completeo; i++)
        {
            // para char es con un "_"
            mV.push_back('X');
        }
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

string decipherPerm(string c, vector<int> PI)
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

// ----------------------
// Práctica 5
// ----------------------

// Warm up:
void warmingExercise()
{
    // 1 Exercise
    unsigned char data = 'K';

    printf("1) Initial value\n");
    printf("Character: %c\n", data);
    printf("Hexadecimal: 0x%X\n", data);
    printf("Integer: %u\n\n", data);

    // 2 Exercise LSHIFT
    printf("2) Left shift\n");
    for (int i = 0; i < 8; i++)
    {
        data = data << 1;
        printf("Shift %d\n", i + 1);
        printf("Character: %c\n", data);
        printf("Hexadecimal: 0x%X\n", data);
        printf("Integer: %u\n\n", data);
    }

    // 3 Exercise RSHIFT
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

    // 4 Exercise - bitwise AND, OR, XOR
    unsigned char v1 = 'D'; // 0x44 = 68
    unsigned char v2 = 'M'; // 0x4D = 77

    unsigned char result_and = v1 & v2;
    unsigned char result_or = v1 | v2;
    unsigned char result_xor = v1 ^ v2;

    printf("4) Bitwise operations\n");
    printf("v1 = %c -> 0x%X -> %u\n", v1, v1, v1);
    printf("v2 = %c -> 0x%X -> %u\n\n", v2, v2, v2);

    printf("AND: 0x%X -> %u\n", result_and, result_and);
    printf("OR : 0x%X -> %u\n", result_or, result_or);
    printf("XOR: 0x%X -> %u\n\n", result_xor, result_xor);

    // 5 Exercise - obtain most significant bit
    unsigned char data2 = 'R'; // 0x52 = 01010010
    unsigned char mask = 0x80; // 10000000
    unsigned char result = data2 & mask;

    printf("5) Most significant bit\n");
    printf("data2 = %c -> 0x%X -> %u\n", data2, data2, data2);
    printf("Mask  = 0x%X\n", mask);
    printf("Result: 0x%X -> %u\n\n", result, result);

    // 6 Exercise - obtain 4 least significant bits
    data2 = 'V'; // 0x56 = 01010110
    mask = 0x0F; // 00001111
    result = data2 & mask;

    printf("6) Four least significant bits\n");
    printf("data2 = %c -> 0x%X -> %u\n", data2, data2, data2);
    printf("Mask  = 0x%X\n", mask);
    printf("Result: 0x%X -> %u\n", result, result);
}

unsigned int getNthBit(unsigned int num, unsigned int n)
{
    // uint8_t es un entero de 8 bits
    // Si n = 0, no hacemos nada a la mascara
    unsigned int mask = 1;

    // Si n >= 1, hacemos left shift n veces
    for (int i = 1; i <= n; i++)
        mask = mask << 1;

    // if ((num & mask) == 0){
    //     cout << "El bit " << n << " es 0\n";
    // } else {
    //     cout << "El bit " << n << " es 1\n";
    // }

    // Representación binaria
    bitset<32> rawNumber(num);
    cout << "Número en binario: " << rawNumber << endl;
    // Si es != de 0 es true, si es == 0 es false
    cout << "El bit " << n << " es: " << (((num & mask)) ? 1 : 0) << endl;

    return (num & mask) ? 1 : 0;
}

unsigned int setNthBit(unsigned int num, unsigned int n)
{
    // uint8_t es un entero de 8 bits
    unsigned int bin = 0;
    // Si n = 0, no hacemos nada a la mascara
    unsigned int mask = 1;

    // Si n >= 1, hacemos left shift n veces
    for (int i = 1; i <= n; i++)
        mask = mask << 1;

    bin = (num | mask);

    // Representación binaria
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

unsigned int countLeadingZeros(unsigned int num)
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

    // Representación binaria
    bitset<32> rawNumber(num);

    cout << "Número original: " << rawNumber << endl;
    cout << "Cantidad de ceros:" << counter;
    return counter;
}

// ----------------------
// Práctica 6
// ----------------------

vector<char> tableSubstitution()
{
    vector<char> S;
    vector<char> hexA = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    vector<bool> X(hexA.size(), false);

    do
    {

        int pos = randomV(0, hexA.size() - 1);
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

// a)
string binaryRep(unsigned int num, int bits)
{
    string r = "";
    for (int i = bits - 1; i >= 0; i--)
        r += ((num >> i) & 1) ? '1' : '0';
    return r;
}

vector<unsigned int> functionS(int n)
{
    // z = {0, 1, 2, 3, ..., 2^n - 1}
    vector<unsigned int> z;
    vector<unsigned int> S;

    // l = 2^n -> todas las combinaciones posibles de tamaño n
    int l = 1 << n; // 0000 0001 -> (2) 0000 0100 / (3) 0000 1000 / (4) 0001 0000 / (5) 0010 0000

    // Llenar el vector con las combinaciones posibles de cadenas
    for (int i = 0; i < l; i++)
    {
        z.push_back(i);
    }

    vector<bool> X(z.size(), false);

    do
    {

        int pos = randomV(0, z.size() - 1);
        if (X[pos] == false)
        {
            S.push_back(z[pos]);
            X[pos] = true;
        }

    } while (z.size() != S.size());

    cout << "Representación enteros" << endl;
    cout << "z: ";
    for (unsigned int c : z)
        cout << c << " ";
    cout << endl;

    cout << "S: ";
    for (unsigned int k : S)
        cout << k << " ";

    cout << endl
         << "Representación binaria" << endl;
    cout << "z: ";
    for (unsigned int c : z)
        cout << binaryRep(c, n) << " ";
    // cout << bitset<bits> (c) << " ";

    cout << endl;

    cout << "S: ";
    for (unsigned int k : S)
        cout << binaryRep(k, n) << " ";
    cout << endl;

    return S;
}


// b)
// char array M[] = {'a', 'b', 'c'}
// {01010101 , 01010001, 11100001}
// concatenar {010101010101000111100001}
// Si n = 4, separamos en bloques de 4 bits
// si resultan x bloques de n = 4 bits
// bloque 0 -> {0101} , bloque 1 -> {0101}, bloque 2 -> {0101}, bloque 3 -> {0001}, bloque 4 -> {1110}, bloque 5 -> {0001} 
// convertir todos a enteros --- > vemos la s box de n = 4 y hacemos la sustitucion
// convertimos a hexadecimal 
// si n = 8, separamos en bloques de 8 bits
// lo mismo




// c)





// d)