#include "ECCompositeShapes.h"
#include "ECCircle.h"
#include <vector>
#include <iostream>
#include <math.h>


using namespace std; 

//using namespace std;

//*************************************************************************************
// Composite shape

ECCompositeShape :: ECCompositeShape(){}

// your code here
ECCompositeShape::~ECCompositeShape(){
    for (auto item : this->DList){
        delete item; 
    }
}
    
// add a sub-shape to the composite shape
void ECCompositeShape :: AddShape(ECAbstract2DShape *pShape){
    DList.push_back(pShape);
}
    
// Get bounding box (i.e. smallest rectangle contaiing the shape with sides parellel to axes) of the shape
// the left-upper corner of the window is (0,0)
void ECCompositeShape :: GetBoundingBox (double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight) const{
    double minx, miny, maxx, maxy;
    double temp_minx, temp_miny, temp_maxx, temp_maxy;

    if (DList.size() < 1){return;}

    DList[0]->GetBoundingBox(minx, miny, maxx, maxy);
    DList[0]->GetBoundingBox(temp_minx, temp_miny, temp_maxx, temp_maxy);

    for (int i=1; i < this->DList.size();i++){
        DList[i]->GetBoundingBox(temp_maxx, temp_miny, temp_maxx, temp_maxy);
        minx = min(temp_minx, minx);
        miny = min(temp_miny, miny);
        maxx = max(temp_maxx, maxx);
        maxy = max(temp_maxy, maxy);
    }

    xUpperLeft = minx;
    yUpperLeft = miny;
    xLowerRight = maxx;
    yLowerRight = maxy;

}
    
// is the ellipse intersecting with point (px, py)
// to simplify, a point intersects an ellipse if it is inside the bounding box of the ellipse
bool ECCompositeShape :: IsPointInside(const EC2DPoint &pt) const {
    for (auto item : DList){
        if (item->IsPointInside(pt)){
            return true;
        }
    }

    return false;
}
    
double ECCompositeShape :: GetArea() const{
    double total = 0.0;
    for (auto Item : DList){
        total += Item->GetArea();
    }

    return total;
}


void ECCompositeShape :: GetCenter(double &xc, double &yc) const {
    double xUpperLeft, yUpperLeft, xLowerRight, yLowerRight;

    this->GetBoundingBox(xUpperLeft, yUpperLeft, xLowerRight, yLowerRight);

    xc = (xUpperLeft + xLowerRight)/2;
    yc = (yLowerRight + yUpperLeft)/2;

}


//*************************************************************************************
// Decorator pattern: shape with a hole at the center

// your code here

ECShapeWithHole :: ~ECShapeWithHole(){
    delete shape;
}
    
    // Get bounding box (i.e. smallest rectangle contaiing the shape with sides parellel to axes) of the shape
    // the left-upper corner of the window is (0,0)
void ECShapeWithHole :: GetBoundingBox( double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight ) const{
    double minx, miny, maxx, maxy; //maxy

    shape->GetBoundingBox(minx, miny, maxx, maxy);

    xUpperLeft = minx;
    yUpperLeft = miny;
    xLowerRight = maxx;
    yLowerRight = maxy;

}
    
// is the ellipse intersecting with point (px, py)
// to simplify, a point intersects an ellipse if it is inside the bounding box of the ellipse
bool ECShapeWithHole :: IsPointInside(const EC2DPoint &pt) const{

    if (shape->IsPointInside(pt)){
        double x,y;
        shape->GetCenter(x,y);
        ECCircle *hole = new ECCircle(x,y,radius);

        if(!hole->IsPointInside(pt)){
            return true;
        }
    }
    return false;
}
    
double ECShapeWithHole :: GetArea() const{

    double x,y;
    shape->GetCenter(x,y);
    ECCircle *hole = new ECCircle(x,y,radius);
    double area_shape = 0.0; 
    double area_hole = 0.0;

    area_shape = shape->GetArea();
    area_hole = hole->GetArea();

    return area_shape - area_hole;

}

void ECShapeWithHole :: GetCenter(double &xc, double &yc) const{
    double xUpperLeft, yUpperLeft, xLowerRight, yLowerRight;

    this->GetBoundingBox(xUpperLeft, yUpperLeft, xLowerRight, yLowerRight);

    xc = floor((xUpperLeft + xLowerRight)/2);
    yc = floor((yLowerRight + yUpperLeft)/2);

}
