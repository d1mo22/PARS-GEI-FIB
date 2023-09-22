#include <iostream>
using namespace std;

struct Time {
    int hour, minute, second;
};

void one_second(const Time& t, Time& t1, Time& t2) {
    t1.second = t2.second = t.second;
    t1.minute = t2.minute = t.minute;
    t1.hour = t2.hour = t.hour;

    //Suma de un segon
    ++t1.second;
    if (t1.second >= 60) {
        ++t1.minute;
        t1.second = 0;
        if (t1.minute >= 60) {
            t1.minute = 0;
            ++t1.hour;
            if (t1.hour >= 24) {
                t1.hour = 0;
            }
        }
    }
    cout << t1.hour << " " << t1.minute << " " << t1.second << endl;

    //Resta de un segon
    --t2.second;
    if (t2.second < 0) {
        t2.second = 59;
        --t2.minute;
        if (t2.minute < 0) {
            t2.minute = 59;
            --t2.hour;
            if (t2.hour < 0) {
                t2.hour = 23;
            }
        }
    }
    cout << t2.hour << " " << t2.minute << " " << t2.second << endl;
}

int main() {
    Time x;
    Time mes;
    Time menys;
    int h, m, s;
    while (cin >> h >> m >> s) {
        x.hour = h;
        x.minute = m;
        x.second = s;
        one_second(x, mes, menys);
    }
}