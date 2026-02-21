using namespace std;

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
    vector<int> S = {1, 0}, T = {0, 1};
    vector<int> i_epoch, Re, Qu;

    vmax = (a < n) ? n : a;
    vmin = (a < n) ? a : n;

    quotient = floor(vmax / vmin);
    // vmax + vmin * quotient == vmax % quotient
    reminder = vmax % quotient;

    i_epoch.push_back(iter);
    Re.push_back(vmax);
    Qu.push_back(0);
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
    for (int i = 0; i <= iter; i++)
    {
        S.push_back(Qu[i + 1] * (-1) * S[i + 1] + S[i]);
        T.push_back(Qu[i + 1] * (-1) * T[i + 1] + T[i]);
    }

    // Imprimir la pseudomatriz:)
    for (int i = 0; i < Re.size(); i++)
    {
        cout << "i: " << i_epoch[i] << " Re: " << Re[i] << " Qu: " << Qu[i] << " S: " << S[i] << " T: " << T[i] << "\n";
    }

    // Si "a" está en Re[0] entonces regresar S[iter], si no, regresar T[iter]
    return (Re[0] == a) ? S.back() : T.back();
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

    // Revisar
    // a = randomV(1, tmp.size());
    // vamos a una posicion aleatoria de zStar y la ponemos en a
    a = tmp[randomV(0, tmp.size() - 1)];
    b = randomV(0, n);

    val.push_back(a);
    val.push_back(b);

    cout << "a: " << a << "\n"
         << "b: " << b << "\n";

    return val;
}

void affineCipher(string filename)
{
    // El modulo seria del tamaño del alfabeto? 126 - 32 = 94
    // (a * x + b) mod m
    int const modulo = 94;
    int a = 0, b = 0;
    vector<int> key;

    // generación de clave aleatoria
    key = kGeneration(modulo);
    a = key[0], b = key[1];
    map<int, char> asciiCharacterMap = getASCIIDictionary();

    /*
    string plaintext = "oso";
    string ciphertext = "";

    // un for (a : b) es un foreach
    for (char c : plaintext)
    {
        // Para inicar en 0
        int x = static_cast<int>(c) - 32;

        // Formuloca
        int encrypted_val = (a * x + b) % modulo;
        // Para ir agregando cada caracte, como el pushback pero para string
        ciphertext = ciphertext + asciiCharacterMap[encrypted_val + 32];
        // if (encrypted_val < 0) encrypted_val += modulo;
    }

    cout << "\n" << "Text: " << plaintext << endl;
    cout << "Cifred: " << ciphertext << endl;
    */

    // Para agarrar obtener el archivo se usa ifstream
    ifstream inputFile(filename);
    ofstream outputFile("cifred_" + filename);

    char c;
    // noskipws evita que ignore los espacios en blanco
    while (inputFile >> noskipws >> c)
    {
        if (c == '\n')
        {
            outputFile << c;
        }
        else
        {
            int x = static_cast<int>(c) - 32;

            int encrypted_val = (a * x + b) % modulo;
            if (encrypted_val < 0)
                encrypted_val += modulo;

            char encrypted_char = static_cast<char>(encrypted_val + 32);

            outputFile << encrypted_char;
        }
    }

    inputFile.close();
    outputFile.close();
}
