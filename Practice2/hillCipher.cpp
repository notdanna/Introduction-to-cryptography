#include "../functions.hpp"

using namespace std;

struct matriz2x2 { int k[2][2]; };
int inverseM(int n, int a);
matriz2x2 keyHillCipher(int n);
matriz2x2 kminusone(int n);

int main()
{
    int n = 0, a = 0, options = 0, result = 0;
    matriz2x2 Key = {{{0, 0}, {0, 0}}};

    cout << "Elige una opción: \n";
    cout << "[1]: Calcular el inverso multiplicativo de a en Z* de n\n";
    cout << "[2]: Generar una llave válida para el cifrado de Hill\n";
    cout << "[3]: Generar la llave inversa de una llave de Hill\n";

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
        Key = kminusone(n);
        break;

    default:
        break;
    }

    return 0;
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

    do {
        k_11 = randomV(0, n - 1);
        k_12 = randomV(0, n - 1);
        k_21 = randomV(0, n - 1);
        k_22 = randomV(0, n - 1);
        det_K = (k_11 * k_22 - k_12 * k_21) % n;
        if (det_K < 0) {
            det_K += n;
        }

    } while (gcd(n, det_K) != 1);

    cout << "Determinante de K: " << det_K << "\n";
    cout << "Z* de n: ";
    vector<int> star = zStar(n);
    printV (star);

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

matriz2x2 kminusone(int n){
    matriz2x2 Key;
    matriz2x2 K_inv;
    int det_K = 0;

    Key = keyHillCipher(n);
    det_K = (Key.k[0][0] * Key.k[1][1] - Key.k[0][1] * Key.k[1][0]) % n;
    if (det_K < 0) {
        det_K += n;
    }

    int inv_K = inverseM(n, det_K);

    cout << "El inverso multiplicativo del determinante es: " << inv_K << "\n";

    K_inv.k[0][0] = (inv_K * Key.k[1][1]);
    K_inv.k[0][1] = (inv_K * -Key.k[0][1]);
    K_inv.k[1][0] = (inv_K * -Key.k[1][0]);
    K_inv.k[1][1] = (inv_K * Key.k[0][0]);

    // res = n - ((-temp) % n);
    if (K_inv.k[0][0] < 0) K_inv.k[0][0] = n - ((-K_inv.k[0][0]) % n);
    if (K_inv.k[0][1] < 0) K_inv.k[0][1] = n - ((-K_inv.k[0][1]) % n);
    if (K_inv.k[1][0] < 0) K_inv.k[1][0] = n - ((-K_inv.k[1][0]) % n);
    if (K_inv.k[1][1] < 0) K_inv.k[1][1] = n - ((-K_inv.k[1][1]) % n);


    cout << "La llave inversa es: \n";
    cout << K_inv.k[0][0] << " " << K_inv.k[0][1] << "\n";
    cout << K_inv.k[1][0] << " " << K_inv.k[1][1] << "\n";

    return K_inv;
}
