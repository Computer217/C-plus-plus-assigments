#ifndef EC_CIRCLE_H
#define EC_CIRCLE_H

#include <vector>
#include "ECAbstract2DShape.h"

const double PI = 3.1415926;

// circle
class ECCircle : public ECAbstract2DShape
{
public:
    // (x,y): the center of circle, and radius
    ECCircle(double x, double y, double radius): _x(x), _y(y), radius(radius){}

    // Get bounding box (i.e. smallest rectangle contaiing the shape with sides parellel to axes) of the shape
    // the left-upper corner of the window is (0,0)
    virtual void GetBoundingBox(double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight) const;

    // is the shape intersecting with point (px, py)
    virtual bool IsPointInside(const EC2DPoint &pt) const;

    virtual double GetArea() const;
    virtual void GetCenter(double &xc, double &yc) const;

private:
    // your code here
    double _x;
    double _y; 
    double radius; 
};

// ellipse
class ECEllipse : public ECAbstract2DShape
{
public:
    // (x,y): the center of ellipse, and radiu along x and y coordinate
    ECEllipse(double x, double y, double radiusx, double radiusy): _x(x), _y(y), rightmost(radiusx), upmost(radiusy){}

    // Get bounding box (i.e. smallest rectangle contaiing the shape with sides parellel to axes) of the shape
    // the left-upper corner of the window is (0,0)
    virtual void GetBoundingBox(double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight) const;

    // is the ellipse intersecting with point (px, py)
    virtual bool IsPointInside(const EC2DPoint &pt) const;

    virtual double GetArea() const;
    virtual void GetCenter(double &xc, double &yc) const;

private:
    // your code here
    double _x;
    double _y; 
    double rightmost; 
    double upmost; 

};

#endif
