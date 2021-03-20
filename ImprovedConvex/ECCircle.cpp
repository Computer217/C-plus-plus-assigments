#include "ECCircle.h"
#include <cmath>
#include <iostream>
using namespace std;

//*************************************************************************************
// Circle

// your code here

void ECCircle :: GetBoundingBox(double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight) const{
    xUpperLeft = _x - radius;
    yUpperLeft = _y - radius;
    xLowerRight = _x + radius;
    yLowerRight = _y + radius;
}


// is the shape intersecting with point (px, py)
bool ECCircle :: IsPointInside(const EC2DPoint &pt) const{
    if (pow((pt._x - _x), 2) + pow((_y - pt._y), 2) <= pow(radius,2)){
        return true;
    }
    else{
        return false;
    }
}

double ECCircle :: GetArea() const{
    return PI * pow(radius, 2);
}

void ECCircle :: GetCenter(double &xc, double &yc) const{
    xc = _x;
    yc = _y;
}


//*************************************************************************************
// Ellipse

// your code here

void ECEllipse :: GetBoundingBox(double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight) const{
    xUpperLeft = (_x - rightmost);
    yUpperLeft = (_y - upmost);
    xLowerRight = (_x + rightmost);
    yLowerRight = (_y + upmost);
}

// is the ellipse intersecting with point (px, py)
bool ECEllipse :: IsPointInside(const EC2DPoint &pt) const{
    if ((pow((pt._x - _x),2) / pow(rightmost,2)) + (pow((pt._y - _y),2) / pow(upmost,2)) <= 1){
        return true;
    }
    else{
        return false;
    }

}

double ECEllipse :: GetArea() const{
    return PI * upmost * rightmost;

}

void ECEllipse :: GetCenter(double &xc, double &yc) const{
    xc = _x;
    yc = _y;

}