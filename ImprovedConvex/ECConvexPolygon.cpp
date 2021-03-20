//
//  ECConvexPolygon.cpp
//  
//
//  Created by Yufeng Wu on 1/29/21.
//
//

#include "ECConvexPolygon.h"
#include "ECTriangle.h"

// -----------------------------------------------------------------------------
// Convex polygon on 2D plane: implementing polygon for non-triangles
// your code here

ECConvexPolygon :: ECConvexPolygon(const std::vector<EC2DPoint> &listNodes){
    Nodes = listNodes;
}

// Test if the polygon is convex? Return false if not
bool ECConvexPolygon::IsConvex() const{
    int numdot =0;
    int size = Nodes.size();

    bool negative = true;
    bool positive = true;



    while (numdot != size){
        //calculate dot product 

        int dx1 = Nodes[(numdot+1) % size]._x - Nodes[numdot]._x;
        int dy1 = Nodes[(numdot+1) % size]._y - Nodes[numdot]._y;
        int dx2 = Nodes[(numdot+2) % size]._x - Nodes[(numdot+1) % size]._x;
        int dy2 = Nodes[(numdot+2) % size]._y - Nodes[(numdot+1) % size]._y;

        int cross = dx1*dy2 - dy1*dx2;

        if (cross < 0){
            positive = false;
        }

        if (cross > 0){
            negative = false;
        }

        numdot++;
    }


    if (negative == false && positive == false){
        return false;
    }

    return true;

}
   
// Calculate total area of the polygon (you can assume it is indeed convex)
double ECConvexPolygon::GetArea() const{
    double area = 0.0;
    int temp = Nodes.size()-1;
    for (int i = 0; i < Nodes.size(); i++){
        area += (Nodes[temp]._x + Nodes[i]._x) * (Nodes[temp]._y - Nodes[i]._y);
        temp = i;
    }

    return fabs(area / 2.0);
}