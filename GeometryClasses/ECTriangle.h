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

// -----------------------------------------------------------------------------
// Triangle on 2D plane

class ECTriangle
{
    EC2DPoint _vertex1;
    EC2DPoint _vertex2;
    EC2DPoint _vertex3;

    public:
        ECTriangle(const EC2DPoint &p1, const EC2DPoint &p2, const EC2DPoint &p3){
            _vertex1 = p1; _vertex2 = p2; _vertex3 = p3; 
        };
        
        // Get area of the triangle
        double GetArea() const;
        
        // Test if a point is inside the triangle (if on the edge, consider it is inside)
        bool IsPointInside(const EC2DPoint &pt) const;
        
        // Test if the passed-in triangle is contained within this triangle
        // again, if the triangle (rhs) has vertex on the side of this triangle, it is allowed (considered to be contained)
        bool IsContaining(const ECTriangle &rhs) const;
        
        // Test if two triangles intersects (i.e. has non-empty common area)
        bool IsIntersecting(const ECTriangle &rhs) const;
        
    private:
        
        // your code goes here
};


#endif /* ECTriangle_h */
