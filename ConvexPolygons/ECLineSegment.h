//
//  ECLineSegment.h
//  
//
//  Created by Yufeng Wu on 1/22/21.
//
//

#ifndef ECLineSegment_h
#define ECLineSegment_h
#include <iostream>
// -----------------------------------------------------------------------------
// Point on 2D plane

class EC2DPoint
{
public:
    double _x;
    double _y;
    EC2DPoint() {_x = _y = 0;}
    EC2DPoint(double x, double y) {_x = x; _y = y;}
    // your code goes here
    EC2DPoint& operator=(const EC2DPoint& p){
        _x = p._x;
        _y = p._y;
        return *this;
    };

    void print(std::ostream& os) const;

};

// -----------------------------------------------------------------------------
// Line segment on 2D plane

class ECLineSegment
{

public:
    ECLineSegment(const EC2DPoint &pStart, const EC2DPoint &pEnd){
        _FirstPoint = pStart; _SecondPoint = pEnd;
    };
    
    // Is this segment intersect with the other?
    bool IsIntersect(const ECLineSegment &rhs) const;
    
    // your code goes here
    //line length

    double segment_length() const;

    bool isequal(const ECLineSegment& p){
        if (_FirstPoint._x == p._FirstPoint._x && _FirstPoint._y == p._FirstPoint._y && 
        _SecondPoint._x == p._SecondPoint._x && _SecondPoint._y == p._SecondPoint._y){
            return true;
        }
        else{
            return false;
        }

    }
    
private:
    // your code goes here
    EC2DPoint _FirstPoint;
    EC2DPoint _SecondPoint;
};


#endif /* ECLineSegment_h */
