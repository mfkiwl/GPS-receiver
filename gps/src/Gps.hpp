//
//  Gps.hpp
//  GPS
//
//  Created by RAIDEMOT on 30.05.2021.
//

#ifndef Gps_hpp
#define Gps_hpp

#include <cmath>
#include <ctime>
#include <stdio.h>
#include <iostream>
#include "Point.hpp"

static constexpr size_t CABitLength = 1023;
static constexpr size_t navBitLength = 128;
static constexpr size_t rCodeBitLength = CABitLength + navBitLength;

class Gps {
    
private:
    char** G2Taps;
    
public:
    
//    Gps(char **G2Taps, unsigned int size);
    
    short receivedSignalLenght;

    // Коррелятор
    short correlate(char satelliteId, bool* receivedSignal);
    
    // Длина принятого сигнала
    bool* generateReceivedSignal(char satellineId, char cycles, unsigned short shift = 0);
    
    // Генерация CA кода
    bool* generateCA(char satelliteId);
    
    // Нахождение PRN по входным данным
    char getPRN(bool* receivedSignal);
    
    // Вычисление положения спутника по параметрам орбиты
    Point findSatellite(Point center, double radius, double ang, double time);
    
    // Триангуляция, нахождение координат приемника по расстояниям до спутников
    Point triangulate(Point a, Point b, Point c);
};

#endif /* Gps_hpp */
