//
//  ECAbstractConvexPolygon.h
//  
//
//  Created by Yufeng Wu on 1/29/21.
//
//

    
#include "ECTriangle.h"
#include "ECLineSegment.h"
#include "ECConvexPolygon.h"
#include "ECAbstractConvexPolygon.h"
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

// -----------------------------------------------------------------------------
// Convex polygon on 2D plane: interface class
// your code here

// Constructor for empty polygon
ECAbstractConvexPolygon::ECAbstractConvexPolygon(){};
    
// Consructor takes a list of nodes, which are the nodes of the polygon
// ordered sequentially (either clockwise or counter clockwise
ECAbstractConvexPolygon::ECAbstractConvexPolygon(const std::vector<EC2DPoint> &listNodes){
    Nodes = listNodes;
}


double Orientation(EC2DPoint P0,  EC2DPoint P1, EC2DPoint P2){
    //direction function
    //(x1-x0)(y2-y0) - (x2-x0)(y1-y0)
    double result = (P1._x-P0._x)*(P2._y-P0._y) - (P2._x-P0._x)*(P1._y-P0._y);

    return result;
}

bool OnLine(EC2DPoint P0,  EC2DPoint P1, EC2DPoint P2){
    if ((min(P0._x,P1._x) <= P2._x && P2._x <= max(P0._x,P1._x)) && 
    (min(P0._y,P1._y) <= P2._y && P2._y <= max(P0._y,P1._y))){
        return true;
    }
    else{
        return false;
    }
}


// Test if a point is inside the polygon (if on the edge, consider it is inside)
bool ECAbstractConvexPolygon::IsPointInside(const EC2DPoint &pt) const{

    if (Nodes.size() < 3){return false;}

    //create ray
    EC2DPoint rightmost = EC2DPoint(pt._x + 1000, pt._y);
    ECLineSegment ray = ECLineSegment(pt,rightmost);

    //cout << ray.segment_length() << endl;

    int count = 0, first = 0, last = 0;

    do{
        last = (first + 1) % Nodes.size();

        ECLineSegment temp_line = ECLineSegment(Nodes[first], Nodes[last]);

        //cout << "line segment is: " << endl;
        //Nodes[first].print(cout);
        //Nodes[last].print(cout);

        //if the ray intersects with current temp line
        if (ray.IsIntersect(temp_line)){
            ///cout << "intersects with ray: " << endl;
            //pt.print(cout);
            //rightmost.print(cout);

            if (pt._y == Nodes[last]._y && Nodes.size() != 3){
                count--;
            }

            if (fabs(Orientation(Nodes[first], pt, Nodes[last])) == 0){
                //cout << "is on line" << endl;
                return OnLine(Nodes[first], Nodes[last], pt);
            }

            count++;
        }

        //cout << "-----" << endl;

        first = last;

    } while(first != 0);

    return (count%2 == 1);

}
    
// Test if the passed-in polygon is contained within this polygon
// again, if the polygon (rhs) has vertex on the side of this polygon, it is allowed (considered to be contained)
bool ECAbstractConvexPolygon::IsContaining(const ECAbstractConvexPolygon &rhs) const{
    if (Nodes.size() < 3 || rhs.Nodes.size() < 3){return false;}

    for (EC2DPoint vertex: rhs.Nodes){
        if (this->IsPointInside(vertex) != true){
            return false;
        }
    }
    return true;

}
    
// Test if two polygons intersect (i.e. has non-empty common area)
bool ECAbstractConvexPolygon::IsIntersecting(const ECAbstractConvexPolygon &rhs) const{

    for (int i=0; i < Nodes.size(); i++){
        ECLineSegment test1 = ECLineSegment(Nodes[i%Nodes.size()], Nodes[(i+1)%Nodes.size()]);
        cout << "line one: " << endl;
        Nodes[i%Nodes.size()].print(cout);
        Nodes[(i+1)%Nodes.size()].print(cout);
        cout << endl;

        for (int j=0; j<rhs.Nodes.size(); j++){
            ECLineSegment test2 = ECLineSegment(rhs.Nodes[j%rhs.Nodes.size()], rhs.Nodes[(j+1)%rhs.Nodes.size()]);

            if (test1.IsIntersect(test2)){
                cout << "intersected with: "<<endl;
                Nodes[j%rhs.Nodes.size()].print(cout);
                Nodes[(j+1)%rhs.Nodes.size()].print(cout);
                cout << endl;

                return true;
            }

        }
    }

    return false;
}

int main(){

    EC2DPoint p1(0, 0), p2(2, 2), p3(5,3), p4(5,0), p5(8, 2), p6(10, 0), p7(5, -3), p8(10, -5);
	
	ECTriangle tri1(p1, p2, p3);
	ECTriangle tri2(p4, p5, p6);
	ECTriangle tri3(p5, p6, p7);
	cout << "answer: " << tri1.IsIntersecting(tri2) << " result: " << false << endl;
    cout << "answer: " << tri2.IsIntersecting(tri1) << " result: " << false << endl;
    cout << "answer: " << tri2.IsIntersecting(tri3) << " result: " << true << endl;
    cout << "answer: " << tri3.IsIntersecting(tri2) << " result: " << true << endl;

    cout << "------wrong------" << endl;


    cout << "answer: " << endl;
    cout << tri1.IsIntersecting(tri3) << " result: " << false << endl;
    cout << "answer: " << endl; 
    cout << tri3.IsIntersecting(tri1) << " result: " << false << endl;

    return 0;
}
