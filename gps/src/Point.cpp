//
//  Point.cpp
//  test
//
//  Created by RAIDEMOT on 30.05.2021.
//

#include "Point.hpp"

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

Point::Point(double x, double y, double r) {
    this->x = x;
    this->y = y;
    this->r = r;
}

double Point::getX() {
    return this->x;
}

double Point::getY() {
    return this->y;
}

double Point::getR() {
    return this->r;
}
