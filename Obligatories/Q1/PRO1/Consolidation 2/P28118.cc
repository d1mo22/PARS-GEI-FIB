//No funciona

#include <iostream>
#include <math.h>
using namespace std;

double distancia(double x1, double y1, double x2, double y2) {
    double x = pow((x1-x2),2);
    double y = pow((y1-y2),2);
    return sqrt(x + y);
    //cout << x << " " << y << " " << distancia << endl;
}

int main() {
    int inici, final, x1, x2, y1, y2;
    string a;
    cin >> a;
    while (cin >> a) {
        double count = 0;
        bool primer = true;
        cin >> inici >> final >> x1 >> x2;
        while (cin >> x1 >> y1 and x1 != inici and y1 != final) {
           if (primer) {
                primer = false;
                count += distancia(inici,final,x1,y1);
            }

           else count += distancia(x1,y1,x2,y2);
           x2 = x1;
           y2 = y1;
        }

        cout << "Trajecte " << a << ": " << distancia(inici, final, x1, y1) << endl;
        
    }
}