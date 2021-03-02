//
//  ECLineSegment.cpp
//  
//
//  Created by Yufeng Wu on 1/22/21.
//
//

#include "ECLineSegment.h"
#include <cmath>
#include <algorithm>
using namespace std;

// -----------------------------------------------------------------------------
// Point on 2D plane

// your code goes here

void EC2DPoint::print(ostream& os) const{
    os << "Point:" << '(' << _x << ',' << _y << ')' << endl;
}

// -----------------------------------------------------------------------------
// Line segment on 2D plane

// your code goes here

double Direction(EC2DPoint P0,  EC2DPoint P1, EC2DPoint P2){
    //direction function
    //(x1-x0)(y2-y0) - (x2-x0)(y1-y0)
    double result = (P1._x-P0._x)*(P2._y-P0._y) - (P2._x-P0._x)*(P1._y-P0._y);

    return result;
}

bool OnSegment(EC2DPoint P0,  EC2DPoint P1, EC2DPoint P2){
    if ((min(P0._x,P1._x) <= P2._x && P2._x <= max(P0._x,P1._x)) && 
    (min(P0._y,P1._y) <= P2._y && P2._y <= max(P0._y,P1._y))){
        return true;
    }
    else{
        return false;
    }
}

bool ECLineSegment::IsIntersect(const ECLineSegment &rhs) const{

    double d_1 = Direction(rhs._FirstPoint, rhs._SecondPoint, _FirstPoint);
    double d_2 = Direction(rhs._FirstPoint, rhs._SecondPoint, _SecondPoint);
    double d_3 = Direction(_FirstPoint, _SecondPoint, rhs._FirstPoint);
    double d_4 = Direction(_FirstPoint, _SecondPoint, rhs._SecondPoint);


    if (((d_1 > 0 &&  d_2 < 0) || (d_1 < 0 && d_2 > 0)) && 
    ((d_3 > 0 &&  d_4 < 0) || (d_3 < 0 && d_4 > 0))){
        return true;
    }
    else if (d_1 == 0 &&
    OnSegment(rhs._FirstPoint, rhs._SecondPoint, _FirstPoint)){
        return true;
    }
    else if (d_2 == 0 &&
    OnSegment(rhs._FirstPoint, rhs._SecondPoint, _SecondPoint)){
        return true;
    }
    else if (d_3 == 0 &&
    OnSegment(_FirstPoint, _SecondPoint, rhs._FirstPoint)){
        return true;
    }
    else if (d_4 == 0 &&
    OnSegment(_FirstPoint, _SecondPoint, rhs._SecondPoint)){
        return true;
    }
    else{
        return false;
    }
}

//-----------------------------------------------------------------------------
//Line Length

double ECLineSegment :: segment_length() const{
    //calculate length
    double x = _SecondPoint._x - _FirstPoint._x;
    double y = _SecondPoint._y - _FirstPoint._y;
    double result = sqrt((x*x)+(y*y));

    return result;
}