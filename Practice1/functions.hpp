#include <iostream>
#include <vector>
using namespace std;

void printV(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) cout << v[i] << (i < v.size() - 1 ? ", " : "");
    cout << "]" << endl;
}

int gcd(int a, int b){
    int vmin, result = 0;

    vmin = (a < b) ? a : b;

    for (int i = 1; i <= vmin; i++) 
        if ((a % i == 0) && (b % i == 0)) result = i;
    
    return result;
}

int aminusone(int n, int a){
    int vmax = 0, vmin = 0, quotient = 0, reminder = 0, temp_k = 0, iter = 0;
    vector<int> S = {1,0}, T = {0,1};
    vector<int> i_epoch, Re, Qu;

    vmax = (a < n) ? n : a;
    vmin = (a < n) ? a : n;

    quotient = floor(vmax/vmin); 
    // vmax + vmin * quotient == vmax % quotient
    reminder = vmax % quotient;

    i_epoch.push_back(iter);
    Re.push_back(vmax);      
    Qu.push_back(0);         
    Qu.push_back(quotient);  

    iter = 1;

    while(reminder != 0){
        vmax = vmin;
        vmin = reminder;
        temp_k = floor(vmax/vmin); 
        reminder = vmax-(vmin*temp_k);  
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
    for (int i = 0; i <= iter; i++){
        S.push_back(Qu[i + 1] * (-1) * S[i + 1] + S[i]);
        T.push_back(Qu[i + 1] * (-1) * T[i + 1] + T[i]);
    }

    // Imprimir la pseudomatriz:)
    for(int i = 0; i < Re.size(); i++){
        cout << "i: " << i_epoch[i] << " Re: " << Re[i] << " Qu: " << Qu[i] << " S: " << S[i] << " T: " << T[i] << "\n";
    }
    
    // Si "a" está en Re[0] entonces regresar S[iter], si no, regresar T[iter]
    return ( Re[0] == a) ? S.back() : T.back();

}

vector<int> zStar(int n){
    
    vector<int> zs;
    
    for (int i = 1; i <= n - 1; i++)
        if (gcd(n,i)==1) zs.push_back(i);

    return zs;
}

