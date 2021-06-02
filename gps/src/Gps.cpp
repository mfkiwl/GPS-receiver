//
//  Gps.cpp
//  GPS
//
//  Created by RAIDEMOT on 30.05.2021.
//

#include "Gps.hpp"
//
//Gps::Gps(char** G2Taps, unsigned int size) {
//    this->G2Taps = G2Taps;
//}

// Генерация CA кода
bool* Gps::generateCA(char satelliteId) {
    
    char G2Taps[32][2] = {
        {2, 6}, {3, 7}, {4, 8}, {5, 9},{1, 9}, {2, 10}, {1, 8}, {2, 9},{3, 10}, {2, 3}, {3, 4}, {5, 6},{6, 7}, {7, 8}, {8, 9}, {9, 10},{1, 4}, {2, 5}, {3, 6}, {4, 7},{5, 8}, {6, 9}, {1, 3}, {4, 6},{5, 7}, {6, 8}, {7, 9}, {8, 10},{1, 6}, {2, 7}, {3, 8}, {4, 9},
    };
    
    char fn = G2Taps[satelliteId-1][0] - 1;
    char sn = G2Taps[satelliteId-1][1] - 1;

    bool G1[10], G2[10];
    
    bool* ca = new bool[CABitLength];
    
    bool G1New, G1Out;
    bool G2New, G2Out;

    for (int i = 0; i < 10; i++) {
        G1[i] = 1;
        G2[i] = 1;
    }

    for (int i = 0; i < CABitLength - 1; i++) {

        G1New = G1[2] ^ G1[9];
        
        for (int j = 9; j >= 1; j--)
            G1[j] = G1[j - 1];
        G1[0] = G1New;

        
        G2New = G2[1] ^ G2[2] ^ G2[5] ^ G2[7] ^ G2[8] ^ G2[9];
        
        for (int j = 9; j >= 1; j--)
            G2[j] = G2[j - 1];
        G2[0] = G2New;

        
        G1Out = G1[9];
        G2Out = G2[fn] ^ G2[sn];
        ca[i] = G1Out ^ G2Out;
    }
    
    return ca;
}

// Коррелятор
short Gps::correlate(char satelliteId, bool* receivedSignal) {
    bool* ca = generateCA(satelliteId);
    short total;
    int minimum_total = CABitLength;
    for (int i = 0; i < receivedSignalLenght - CABitLength; i++) {
        total = 0;
        for (int j = 0; j < 100; j++) {
            total += receivedSignal[i + j] ^ ca[j];
        }

        if (total > 30) {
            continue;
        }
        for (int j = 100; j < CABitLength; j++) {
            total += receivedSignal[i + j] ^ ca[j];
        }

        if (total < 100) {
            return (rCodeBitLength - i) % rCodeBitLength;
        }
    }
    return -1;
}

// Нахождение PRN по входным данным
char Gps::getPRN(bool* receivedSignal) {
    for (int i = 1; i <= 32; i++) {
        
        short shift = correlate(i, receivedSignal);
        
        if (shift > 0)
            return i;
    }
    return 0;
}

// Длина принятого сигнала
bool* Gps::generateReceivedSignal(char satellineId, char cycles, unsigned short shift)
{
    receivedSignalLenght = rCodeBitLength * cycles - shift;
    
    bool* ca = generateCA(satellineId);
    
    bool* receivedSignal = new bool[receivedSignalLenght];

    for (int i = shift; i < CABitLength; i++)
        receivedSignal[i - shift] = ca[i];

    for (int i = 0; i < navBitLength; i++)
        receivedSignal[(CABitLength - 1) + i - shift] = ca[i];

    for (int i = 1; i < cycles; i++) {
        
        for (int j = 0; j < CABitLength; j++)
            receivedSignal[rCodeBitLength * i + j - shift] = ca[j];
            
        for (int j = 0; j < navBitLength; j++)
            receivedSignal[rCodeBitLength * i + (CABitLength - 1) + j - shift] = ca[j];
    }

    return receivedSignal;
}

// Вычисление положения спутника по параметрам орбиты
Point Gps::findSatellite(Point center, double radius, double ang, double time) {
    double angle = ang * time;
    double dx = std::cos(angle) * radius;
    double dy = std::sin(angle) * radius;

    return Point(center.getX() + dx, center.getY() + dy);
}

// Триангуляция, нахождение координат приемника по расстояниям до спутников
Point Gps::triangulate(Point a, Point b, Point c) {
    double x, y;
    
    double x1 = a.getX(), y1 = a.getY(), r1 = a.getR();
    double x2 = b.getX(), y2 = b.getY(), r2 = b.getR();
    double x3 = c.getX(), y3 = c.getY(), r3 = c.getR();
    
    x = ((y2 - y1) * (pow(r2, 2) - pow(r3, 2) - pow(y2, 2) + pow(y3, 2) - pow(x2, 2) + pow(x3, 2)) - (y3 - y2) * (pow(r1, 2) - pow(r2, 2) - pow(y1, 2) + pow(y2, 2) - pow(x1, 2) + pow(x2, 2))) / (2 * ((y3 - y2) * (x1 - x2) - (y2 - y1) * (x2 - x3)));
    
    y = ((x2 - x1) * (pow(r2, 2) - pow(r3, 2) - pow(x2, 2) + pow(x3, 2) - pow(y2, 2) + pow(y3, 2)) - (x3 - x2) * (pow(r1, 2) - pow(r2, 2) - pow(x1, 2) + pow(x2, 2) - pow(y1, 2) + pow(y2, 2))) / (2 * ((x3 - x2) * (y1 - y2) - (x2 - x1) * (y2 - y3)));
    
    return Point(x, y);
}
