#include <iostream>
#include <vector>
using namespace std;

void printV(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << (i < v.size() - 1 ? ", " : "");
    }
    cout << "]" << endl;
}


// GCD
int gcd(int a, int b){
    int vmin, result = 0;

    vmin = (a < b) ? a : b;

    for (int i = 1; i <= vmin; i++) 
        if ((a % i == 0) && (b % i == 0)) result = i;
    
    return result;
}

// Z^*
vector<int> zStar(int n){
    
    vector<int> zs;
    
    for (int i = 1; i <= n - 1; i++)
        if (gcd(n,i)==1) zs.push_back(i);

    return zs;
}

// a^-1 = b
int aminusone(int n, int a){
    int vmax, vmin, quotient, reminder, temp_k, iter = 0;
    int const no = -1;
    vector<int> i_epoch, Re, Qu;
    vector<int> S = {1,0};
    vector<int> T = {0,1};

    vmax = (a < n) ? n : a;
    vmin = (a < n) ? a : n;

    quotient = floor (vmax/vmin); 
    reminder = vmax - (vmin*quotient);

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

    // Caso 1
    S.push_back(Qu[1] * no * S[1] + S[0]);
    T.push_back(Qu[1] * no * T[1] + T[0]);

    // Caso 2
    S.push_back(Qu[2] * no * S[2] + S[1]);
    T.push_back(Qu[2] * no * T[2] + T[1]);

    // Caso 3 hasta la última iteración
    for (int i = 2; i <= iter; i++){
        S.push_back(Qu[i + 1] * no * S[i + 1] + S[i]);
        T.push_back(Qu[i + 1] * no * T[i + 1] + T[i]);
    }

    // Imprimir la pseudomatriz:)
    for(int i = 0; i < Re.size(); i++){
        cout << "i: " << i_epoch[i] << " Re: " << Re[i] << " Qu: " << Qu[i] << " S: " << S[i] << " T: " << T[i] << "\n";
    }
    
    // Si "a" está en Re[0] entonces regresar S[iter], si no, regresar T[iter]
    return ( Re[0] == a) ? S.back() : T.back();

}
