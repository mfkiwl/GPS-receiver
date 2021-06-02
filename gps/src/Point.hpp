//
//  Point.hpp
//  test
//
//  Created by RAIDEMOT on 30.05.2021.
//

#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>

class Point
{
private:
    double x;
    double y;
    double r;
    
public:
    double getX();
    double getY();
    double getR();
    
    Point(double x, double y);
    Point(double x, double y, double r);
};

#endif /* Point_hpp */
