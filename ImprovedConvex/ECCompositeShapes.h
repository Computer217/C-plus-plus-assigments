#ifndef EC_COMPOSITE_SHAPE_H
#define EC_COMPOSITE_SHAPE_H

#include <vector>
#include <iostream>
#include "ECAbstract2DShape.h"
#include "ECCircle.h"


// Composite shape
class ECCompositeShape : public ECAbstract2DShape
{
public:
    ECCompositeShape();

    virtual ~ECCompositeShape();
    
    // add a sub-shape to the composite shape
    void AddShape(ECAbstract2DShape *pShape);
    
    // Get bounding box (i.e. smallest rectangle contaiing the shape with sides parellel to axes) of the shape
    // the left-upper corner of the window is (0,0)
    virtual void GetBoundingBox( double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight ) const;
    
    // is the ellipse intersecting with point (px, py)
    // to simplify, a point intersects an ellipse if it is inside the bounding box of the ellipse
    virtual bool IsPointInside(const EC2DPoint &pt) const;
    
    virtual double GetArea() const;
    virtual void GetCenter(double &xc, double &yc) const;
    
private:
    // your code here
    std::vector <ECAbstract2DShape *> DList;

};

// Shape with a hole: decorator pattern
// The hole is of circular shape (with certain radius), located right at the center of the original shape
class ECShapeWithHole : public ECAbstract2DShape
{
public:
    //
    ECShapeWithHole( ECAbstract2DShape *pShapeOrig, double radiusHole ): shape(pShapeOrig), radius(radiusHole){}

    virtual ~ECShapeWithHole();
    
    // Get bounding box (i.e. smallest rectangle contaiing the shape with sides parellel to axes) of the shape
    // the left-upper corner of the window is (0,0)
    virtual void GetBoundingBox( double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight ) const;
    
    // is the ellipse intersecting with point (px, py)
    // to simplify, a point intersects an ellipse if it is inside the bounding box of the ellipse
    virtual bool IsPointInside(const EC2DPoint &pt) const;
    
    virtual double GetArea() const;
    virtual void GetCenter(double &xc, double &yc) const;
    
private:
    // your code here
    double radius;
    ECAbstract2DShape* shape; 
};


#endif
