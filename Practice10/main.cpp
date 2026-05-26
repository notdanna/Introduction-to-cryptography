#include "../classfunc.hpp"


int main()
{
    int option;
    unsigned short f, g;

    cout << "Elige una opción:" << endl;
    cout << "1. Multiplicar f(x) por x" << endl;
    cout << "2. Multiplicar f(x) por g(x)" << endl;
    cout << "Opción: ";
    cin >> option;

    switch (option)
    {
        case 1:
            cout << "Dame f(x) en hexadecimal!: ";
            cin >> hex >> f;

            Practica10::printMultiplyByX(f);
            break;

        case 2:
            cout << "Dame f(x) en hexadecimal!: ";
            cin >> hex >> f;

            cout << "Dame g(x) en hexadecimal!: ";
            cin >> hex >> g;

            Practica10::printMultiplication(f, g);
            break;

        default:
            cout << "Opción inválida:(" << endl;
            break;
    }

    return 0;
}