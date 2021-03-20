//
//  ECTriangle.h
//  
//
//  Created by Yufeng Wu on 1/22/21.
//
//

#ifndef ECTriangle_h
#define ECTriangle_h

#include "ECLineSegment.h"
#include "ECAbstractConvexPolygon.h"

// -----------------------------------------------------------------------------
// Triangle on 2D plane

class ECTriangle : public ECAbstractConvexPolygon
{
public:
    ECTriangle(const EC2DPoint &p1, const EC2DPoint &p2, const EC2DPoint &p3);
    
    // Test if the polygon is convex? Return false if not
    virtual bool IsConvex() const;
    
    // Get area of the triangle
    virtual double GetArea() const;
    
    // your code here if needed
};


#endif /* ECTriangle_h */
