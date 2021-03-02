//
//  ECAbstractConvexPolygon.h
//  
//
//  Created by Yufeng Wu on 1/29/21.
//
//

#ifndef ECAbstractConvexPolygon_h
#define ECAbstractConvexPolygon_h

#include <vector>
#include "ECLineSegment.h"

// -----------------------------------------------------------------------------
// Convex polygon on 2D plane: interface class
// Note: we assume there is at least three nodes in the polygon (i.e., you don't
// need to deal with invalid inputs with fewer than three nodes)

class ECAbstractConvexPolygon
{
public:
    // Constructor for empty polygon
    ECAbstractConvexPolygon();
    
    // Consructor takes a list of nodes, which are the nodes of the polygon
    // ordered sequentially (either clockwise or counter clockwise
    ECAbstractConvexPolygon(const std::vector<EC2DPoint> &listNodes);
    
    // Test if the polygon is convex? Return false if not
    // NOTE: ALL OTHER METHODS OF THIS CLASS ASSUME THE POLYGON IS CONVEX
    virtual bool IsConvex() const = 0;
    
    // Calculate total area of the polygon (you can assume it is indeed convex)
    virtual double GetArea() const = 0;
    
    // Test if a point is inside the polygon (if on the edge, consider it is inside)
    bool IsPointInside(const EC2DPoint &pt) const;
    
    // Test if the passed-in polygon is contained within this polygon
    // again, if the polygon (rhs) has vertex on the side of this polygon, it is allowed (considered to be contained)
    bool IsContaining(const ECAbstractConvexPolygon &rhs) const;
    
    // Test if two polygons intersect (i.e. has non-empty common area)
    bool IsIntersecting(const ECAbstractConvexPolygon &rhs) const;
    
    // add node (should add sequentially)
    void AddNode(const EC2DPoint &node) { Nodes.push_back(node); }
    
    // Your code here...
        
    protected:
        // your code here
        std::vector<EC2DPoint> Nodes;

};


#endif /* ECAbstractConvexPolygon_h */
