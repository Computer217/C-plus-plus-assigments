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
#include "ECCircle.h"

using namespace std;

// -----------------------------------------------------------------------------
// Convex polygon on 2D plane: interface class
// your code here

// Constructor for empty polygon
ECAbstractConvexPolygon::ECAbstractConvexPolygon(){};

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

// Get bounding box (i.e. smallest rectangle contaiing the shape with sides parellel to axes) of the shape
// the left-upper corner of the window is (0,0)
void ECAbstractConvexPolygon::GetBoundingBox(double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight) const{
    double minx = Nodes[0]._x; //minx
    double miny = Nodes[0]._y ; //miny
    double maxx = Nodes[0]._x; //maxx
    double maxy = Nodes[0]._y; //maxy

    for (int i = 1; i < this->Nodes.size(); i++){
        minx = min(this->Nodes[i]._x, minx);
        miny = min(this->Nodes[i]._y, miny);
        maxx = max(this->Nodes[i]._x, maxx);
        maxy = max(this->Nodes[i]._y, maxy);
    }

    xUpperLeft = minx;
    yUpperLeft = miny;
    xLowerRight = maxx;
    yLowerRight = maxy;

}

void ECAbstractConvexPolygon::GetCenter(double &xc, double &yc) const{
    double xUpperLeft, yUpperLeft, xLowerRight, yLowerRight;

    this->GetBoundingBox(xUpperLeft, yUpperLeft, xLowerRight, yLowerRight);

    xc = floor((xUpperLeft + xLowerRight)/2);
    yc = floor((yLowerRight + yUpperLeft)/2);
}

int main(){

    EC2DPoint p1(0,0), p2(0,2), p3(2,0), p4(2,2), p5(3,1), p6(3, 2), p7(3,0), p8(5, 2), p9(9, 0);
	vector<EC2DPoint> listNodes1, listNodes2, listNodes3, listNodes4, listNodes5, listNodes6;
	double xc, yc;
	
	listNodes1.push_back(p6);
	listNodes1.push_back(p8);
	listNodes1.push_back(p9);
	listNodes1.push_back(p7);
	ECConvexPolygon poly1(listNodes1);
	poly1.GetCenter(xc, yc);



	
	ECAbstract2DShape *cir1 = new ECCircle(0,0,1);
	cir1->GetCenter(xc, yc);

	delete cir1;
	
    /*
	ECAbstract2DShape *ecl1 = new ECEllipse(1,6,1,2);
	ecl1->GetCenter(xc, yc);
	delete ecl1;
    */
	
	ECAbstract2DShape *tri1 = new ECTriangle(p1, p2, p3);
	tri1->GetCenter(xc, yc);
	delete tri1;

    return 0;
}





