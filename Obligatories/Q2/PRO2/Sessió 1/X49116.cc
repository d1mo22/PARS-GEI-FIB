//#include <iostream>
//#include "vectorIOint.hh"
#include <vector>
using namespace std;
 
struct parint {
    int prim, seg;
};
 
parint max_min1(const vector<int>& v)
/* Pre: v.size()>0 */
/* Post: el primer componente del resultado es el valor maximo de v
el segundo componente del resultado es el valor minimo de v */
{
    parint p;
    p.prim = v[0];
    p.seg = v[0];
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] > p.prim) p.prim = v[i];
        if (v[i] < p.seg) p.seg = v[i];
    }
    return p;
}
 
pair<int,int> max_min2(const vector<int>& v)
/* Pre: v.size()>0 */
/* Post: el primer componente del resultado es el valor maximo de v;
el segundo componente del resultado es el valor minimo de v */
{
    pair <int,int> p;
    p.first = v[0];
    p.second = v[0];
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] > p.first) p.first = v[i];
        if (v[i] < p.second) p.second = v[i];
    }
    return p;
}
 
void max_min3(const vector<int>& v, int& x, int& y)
/* Pre: v.size()>0 */
/* Post: x es el valor maximo de v;  y es el valor minimo de v */
{
    x = v[0];
    y = v[0];
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] > x) x = v[i];
        if (v[i] < y) y = v[i];
    }  
}


 