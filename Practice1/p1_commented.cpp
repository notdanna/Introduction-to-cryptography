#include <iostream>
#include <vector>
using namespace std;

// Prototipos de funciones

int gcd(int a, int b);
vector<int> zStar(int n);
int aminusone(int n, int a);


// Programa principal
int main()
{
    int option;
    cout << "Elige el número de ejercicio: "; 
    cin >> option;

    switch(option){

        case 1: {
            int a, b = 0;
            int gcdR;

            cout << "Dame una a!: ";
            cin >> a;
            cout << "Dame una b!: ";
            cin >> b;
            gcdR = gcd(a,b);
            cout << "Yo te doy un GCD de: "<< gcdR << "\n"; 
            break;
        }

        case 2: {
            int n = 0;
            vector<int> zstarR(n);
            
            cout << "Dame una n!: ";
            cin >> n;
            zstarR = zStar(n);
            cout << "Yo te doy un Z^*: [";
            for (int i = 0; i < zstarR.size(); i++){
                cout << zstarR[i];  
                if(i < zstarR.size() - 1){
                    cout << ", ";
                }
            }
            cout << "]";
            break;
        }

        case 3: {
            int n = 0;
            int a = 0;
            int b = 0;
            vector<int> zstarR(n);
            
            cout << "Dame una n!: ";
            cin >> n;
            zstarR = zStar(n);
            cout << "Elige un valor de Z estrella: [";

            for (int i = 0; i < zstarR.size(); i++){
                cout << zstarR[i];  
                if(i < zstarR.size() - 1){
                    cout << ", ";
                }
            }
            cout << "]" << "\n";
        
            // Esperar respuesta
            cout << "Dame un valor!: ";
            cin >> a;

            b = aminusone(n, a);
            cout << "Yo te doy un b!: "<< b << "\n";
            break;
        }

    }
    return 0;
}


// Funciones
// GCD
int gcd(int a, int b){
    int resp = 0;
    int vmin = 0;

    vmin = (a < b) ? a : b;

    for (int i = 1; i <= vmin; i++){
        if ((a % i == 0) && (b % i == 0))
            resp = i;
    }
    
    return resp;
}

// Z^*
vector<int> zStar(int n){
    
    vector<int> zs;
    
    for (int i = 1; i <= n - 1; i++){
        if (gcd(n,i)==1)
        zs.push_back(i);
    }

    return zs;
}


// a^-1 = b
int aminusone(int n, int a){
    // 214^-1(a) mod 17(n)
    int vmax, vmin, quotient, reminder = 0;
    int temp_k, iter = 0;
    int const no = -1;
    vector<int> i_epoch, Re, Qu;
    vector<int> S = {1,0};
    vector<int> T = {0,1};

    vmax = (a < n) ? n : a;
    vmin = (a < n) ? a : n;

    quotient = floor (vmax/vmin); 
    reminder = vmax - (vmin*quotient);

    i_epoch.push_back(iter); // 0
    Re.push_back(vmax);      // 214
    Qu.push_back(0);         // 0
    Qu.push_back(quotient);  // 12

    iter = 1;

    while(reminder != 0){
        
        // 214 => 17
        vmax = vmin;
        // 17 => 10
        vmin = reminder;
        // 17 = 10 (1) + ()
        temp_k = floor(vmax/vmin);  // 17/10 = 1.7 = 1
        // 17 = 10 (1) + (7) Like REMINDER
        reminder = vmax-(vmin*temp_k);  // 17-(10*1) = 17 - 10 = 7
        /*
        vmax = 17
        vmin = 10
        temp_k = 1
        reminder = 7

        // 17(max) => 10
        // 10(min) => 7(rem)
        // 10 = 7 (1) + ().         10/7 = 1... = 1(k)
        // 10 = 7 (1) + (3).        10-(7*1) = 10 - 7 = 3

        */
        i_epoch.push_back(iter);     //1
        Re.push_back(vmax);          //17
        Qu.push_back(temp_k);        //1

        iter++; 
    }
    
    i_epoch.push_back(iter);
    // Agregar el 0 del reminder
    Re.push_back(0);
     // Hacer un SHIFT_D de Q y agregar cero izq
    /////////Qu.insert(Qu.begin(), 0);
    // Qu.pop_back();
    
    
    /* calculoco
    case 1
    Q[1]: 12 * (-1) * 0 + 1 = 1 : S[0] 
    12 * (-1) * 1 + 0 = -12 : T[0]
    
    case 2
    Q[2]: 1 * (-1) * 1 : S[0] + 0 = -1[S1] 
    Q[2]: 1 * (-1) * (-12): T[0] + 1

    case 3
    Q[3] * (-1) * S1 + S[0] = S[2]
    Q[3] * (-1) * T1 + T[0] = T[2]
    */
    
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

    for(int i = 0; i < Re.size(); i++){
        cout << "i: " << i_epoch[i] << " Re: " << Re[i] << " Qu: " << Qu[i] << " S: " << S[i] << " T: " << T[i] << "\n";
    }
    // Si "a" está en Re[0] entonces mostrar S[iter]
    if ( Re[0] == a){

        return S.back();
    } 
    // si no lo está, mostrar T[iter]
    else {
        return T.back();
    }
}