#include "../classfunc.hpp"

int main(){
  int n = 0, option = 0;
  vector<char> M = {};
  vector<unsigned int> ans;
  char c;
  unsigned short K = 0;
  int caracteres = 0;

  cout << "Seleccione el ejercicio: \n";
  cout << "0. Ejercicio a)\n";
  cout << "1. Ejercicio b)\n";
  cout << "2. Ejercicio c)\n";
  cout << "3. Ejercicio d)\n";

  cin >> option;

  switch(option){
    case 0:
      cout << "Ingrese el valor de n (2 o 3): ";
      cin >> n;
      cout << endl; 
      ans = Practica6::functionS(n);
      break;
    case 1:
      cout << "Ingrese el número de caracteres a usar: ";
      cin >> caracteres;
      for (int i = 0; i < caracteres; i++){
        cout << "Ingrese el caracter: " << i+1 << ": ";
        cin >> c;
        M.push_back(c);
      }
      cout << "Ingrese el valor de n (2 o 3): ";
      cin >> n;
      cout << endl;
      Practica6::subsBlocks(M, n);
      break;
    case 2:
      cout << "Ingrese el valor de K: ";
      cin >> K;
      Practica6::subsK(K);
      break;
    case 3:
      cout << "Ingrese el valor de K: ";
      cin >> K;
      Practica6::subsKd(K);
      break;
    default:
      cout << "Opción no válida" << endl;
      return 1;
  }
}

