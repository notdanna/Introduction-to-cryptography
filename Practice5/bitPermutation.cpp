#include "../functions.hpp"
using namespace std;

int main()
{

    int option = 0;
    unsigned int num = 0, n = 0, ans = 0;
    cout << "Selecciona una opción: \n";
    cout << "[1] Ejercicio de calentamiento\n";
    cout << "[2] Obtener el n-ésimo bit\n";
    cout << "[3] Establecer el n-ésimo bit\n";
    cout << "[4] Contar ceros a la izquierda\n";

    cin >> option;
    switch (option)
    {
    case 1:
        warmingExercise();
        break;

    case 2:
        cout << "Dame un numero!: ";
        cin >> num;
        cout << "Dame una n!: ";
        cin >> n;
        ans = getNthBit(num, n);
        break;

    case 3:
        cout << "Dame un número!:";
        cin >> num;
        cout << "Dame una n!: ";
        cin >> n;
        ans = setNthBit(num, n);
        break;

    case 4:
        cout << "Dame un número!:";
        cin >> num;
        ans = countLeadingZeros(num);
        break;
    }

    return 0;
}