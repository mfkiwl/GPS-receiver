#include <iostream>
#include <typeinfo>
#include "Gps.hpp"
#include "Point.hpp"

using namespace std;

int main()
{
    Gps gps;
    
    // Генерация CA кода
    bool* ca = gps.generateCA(8);
    cout << "CAS: ";
    
    for (int i = 0; i < CABitLength; i++)
        cout << ca[i];
    
    cout<<'\n';

    // Длина принятого сигнала
    bool* rs;
    rs = gps.generateReceivedSignal(8, 7, 1000);
    cout<<"RS: ";
    
    for (int i = 0; i < gps.receivedSignalLenght; i++)
        cout<<rs[i];
    
    cout << "\n";
    
    char prn = gps.getPRN(rs);
    
    cout << "PRN: " << int(prn) << "\n";
    
    cout<<"satellite 1: " << gps.correlate(1, rs) << "\n";
    cout<<"satellite 8: " << gps.correlate(8, rs) << "\n";

    Point a(0, 4, 2);
    Point b(2, 6, 2);
    Point c(5, 0, 5);
    Point c1 = gps.triangulate(a,b,c);
    
    cout << c1.getX() << ' ' << c1.getY();
}
