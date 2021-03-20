//
//  ECTriangle.cpp
//  
//
//  Created by Yufeng Wu on 1/22/21.
//
//

#include "ECTriangle.h"
#include <cmath>
using namespace std;

// your code here

ECTriangle::ECTriangle(const EC2DPoint &p1, const EC2DPoint &p2, const EC2DPoint &p3){
	vector<EC2DPoint> triangle;
	triangle.push_back(p1);
	triangle.push_back(p2);
	triangle.push_back(p3);
	Nodes = triangle;

};
    
// Test if the polygon is convex? Return false if not
bool ECTriangle::IsConvex() const{
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
    
// Get area of the triangle
double ECTriangle::GetArea() const{

    if (Nodes.size() > 3){
        return 0.0;
    }

    //need to fix
    ECLineSegment Seg1 = ECLineSegment(Nodes[0], Nodes[1]);
    ECLineSegment Seg2 = ECLineSegment(Nodes[1], Nodes[2]);
    ECLineSegment Seg3 = ECLineSegment(Nodes[2], Nodes[0]);

    double Len_Seg1 = Seg1.segment_length();
    double Len_Seg2 = Seg2.segment_length();
    double Len_Seg3 = Seg3.segment_length();
    

    //Herons formula for area

    double s = (Len_Seg1 + Len_Seg2 + Len_Seg3)/2;

    double area = sqrt(s * (s-Len_Seg1) * (s-Len_Seg2) * (s-Len_Seg3));

    return area;

}
