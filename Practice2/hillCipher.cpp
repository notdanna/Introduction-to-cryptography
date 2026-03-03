#include "../functions.hpp"

using namespace std;

struct matriz2x2
{
    int k[2][2];
};
int inverseM(int n, int a);
matriz2x2 keyHillCipher(int n);
matriz2x2 kminusone(int n, matriz2x2 Key);
string hillCipher(string M, matriz2x2 Key );
string hillDeciphered(string C, matriz2x2 Key);
string readFile(string filename);

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
        cout << "Dame un archivo a cifrar!: ";   
        cin >> filename;
        M = readFile(filename);
        cout << "Dame la llave de Hill (4 enteros):! \n";
        cin >> Key.k[0][0] >> Key.k[0][1] >> Key.k[1][0] >> Key.k[1][1];
        encrypted = hillCipher(M, Key);
        output.open("ciph.txt");
        output << encrypted;
        output.close();
        break;

    case 5:
        cout << "Dame un archivo a descifrar!: ";   
        cin >> filename;
        C = readFile(filename);
        cout << "Dame tu llave de Hill!: ";
        cin >> Key.k[0][0] >> Key.k[0][1] >> Key.k[1][0] >> Key.k[1][1];
        hillDeciphered(C, Key);
        break;

    default:
        break;
    }

    return 0;
}


string readFile(string filename) {
    ifstream file(filename, ios::binary);
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();
    
    for (char& c : content){
        int i;
        vector<int> linebreaks = {};
        if (c == '\n') {
            c = '|'; // Reemplazamos el salto de línea por un carácter especial
            //linebreaks.push_back(i); // Guardamos la posición del salto de línea
        }
    }
    
    return content;
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
    string res = "";

    if (M.size() % 2 != 0) M += ' '; // Padding con espacio si el mensaje tiene longitud impar

    cout << "Pares (p1, p2) -> Indices (m1, m2) -> Caracteres\n";

    for (int i = 0; i < M.size(); i += 2)
    {

        int p1 = M[i] - 32;
        int p2 = M[i+1] - 32;

        // Multiplicación de matriz: C = K * P
        int m1 = (key.k[0][0] * p1 + key.k[0][1] * p2) % modulo;
        int m2 = (key.k[1][0] * p1 + key.k[1][1] * p2) % modulo;

        // Normalización de negativos
        if (m1 < 0 || m2 < 0)
        {
            m1 = modulo - ((-(p1 * key.k[0][0] + p2 * key.k[0][1])) % modulo);
            m2 = modulo - ((-(p2 * key.k[1][0] + p2 * key.k[1][1])) % modulo);
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

string hillDeciphered(string C, matriz2x2 key) {
    matriz2x2 inverse = kminusone(95, key);
    string decrypted = hillCipher(C, inverse);

    for (char& c : decrypted) 
        if (c == '|') c = '\n';

    cout << "Resultado final: " << decrypted << "\n";
    
    ofstream output("deciph.txt");
    output << decrypted; // Ahora guarda el resultado real
    output.close();

    return decrypted;
}
