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
//EC2DPoint. The most important thing for this Point class is the constructor: 
//it takes two double parameters as x and y coordinates.

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

//ECLineSegment. This is line segment class. (i) Constructor: it takes two 
//EC2DPoint points as the start and end points. (ii) IsIntersect: is this line 
//segment intersecting with the line segment (as passed-in)?

class ECLineSegment
{

    // your code goes here
    EC2DPoint _FirstPoint;
    EC2DPoint _SecondPoint;

public:
    ECLineSegment(const EC2DPoint &pStart, const EC2DPoint &pEnd){
        _FirstPoint = pStart; _SecondPoint = pEnd;
    };
    
    // Is this segment intersect with the other?
    bool IsIntersect(const ECLineSegment &rhs) const;
    
    // your code goes here
    //line length

    double segment_length() const;
};


#endif /* ECLineSegment_h */
