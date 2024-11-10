#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

int main() {
    queue<int> q;
    int n;
    int min_val = 1001;
    int max_val = -1001;
    double suma = 0;
    
    while(cin >> n and (n >= -1001 and n <= 1000)) {
        if (n == -1001) {
            if (!q.empty()) {
                int valor_eliminado = q.front();
                q.pop();
                suma -= valor_eliminado;
                
                if (q.empty()) {
                    min_val = 1001;
                    max_val = -1001;
                }
                else if (valor_eliminado == min_val || valor_eliminado == max_val) {
                    // Solo recalculamos si eliminamos un mínimo o máximo
                    queue<int> temp = q;
                    min_val = 1001;
                    max_val = -1001;
                    while (!temp.empty()) {
                        int val = temp.front();
                        temp.pop();
                        if (val < min_val) min_val = val;
                        if (val > max_val) max_val = val;
                    }
                }
            }
        } else {
            q.push(n);
            suma += n;
            if (n < min_val) min_val = n;
            if (n > max_val) max_val = n;
        }
        
        if (q.empty()) {
            cout << "0" << endl;
        } else {
            cout << "min " << min_val << "; max " << max_val << "; media " << suma/q.size() << endl;
        }
    }
    return 0;
}