//
//  ECTriangle.cpp
//  
//
//  Created by Yufeng Wu on 1/22/21.
//
//

#include "ECTriangle.h"
#include <cmath>
#include <limits>

using namespace std;

// your code goes here

double ECTriangle :: GetArea() const {
    //Get length of all 3 segments
    //_vertex1.print(cout);
    //_vertex2.print(cout);
    //_vertex3.print(cout);

    ECLineSegment Seg1 = ECLineSegment(_vertex1, _vertex2);
    ECLineSegment Seg2 = ECLineSegment(_vertex2, _vertex3);
    ECLineSegment Seg3 = ECLineSegment(_vertex3, _vertex1);

    double Len_Seg1 = Seg1.segment_length();
    double Len_Seg2 = Seg2.segment_length();
    double Len_Seg3 = Seg3.segment_length();
    

    //Herons formula for area

    double s = (Len_Seg1 + Len_Seg2 + Len_Seg3)/2;

    double area = sqrt(s * (s-Len_Seg1) * (s-Len_Seg2) * (s-Len_Seg3));

    return area;

}

bool ECTriangle :: IsPointInside(const EC2DPoint &pt) const {
    double total_area = this->GetArea();

    ECTriangle T0 = ECTriangle(pt, _vertex1, _vertex2);
    ECTriangle T1 = ECTriangle(pt, _vertex2, _vertex3);
    ECTriangle T2 = ECTriangle(pt, _vertex1, _vertex3);

    double A0 = T0.GetArea();
    double A1 = T1.GetArea();
    double A2 = T2.GetArea();

    double result = A0 + A1 + A2;

    //cout.precision(17);

    //cout << "result: " << result << endl;
    //cout << "total: " << total_area << endl;

    //double test = numeric_limits<double>::epsilon();

    return fabs(total_area - result) < pow(10, -13);
}


bool ECTriangle :: IsContaining(const ECTriangle &rhs) const{
    if (this->IsPointInside(rhs._vertex1) && this->IsPointInside(rhs._vertex2) 
    && this->IsPointInside(rhs._vertex3)){
        return true;
    }
    else{
        return false;
    }
}

bool ECTriangle :: IsIntersecting(const ECTriangle &rhs) const{
    if (this->IsPointInside(rhs._vertex1) || this->IsPointInside(rhs._vertex2) 
    || this->IsPointInside(rhs._vertex3)){
        return true;
    }
    else if (rhs.IsPointInside(_vertex1) || rhs.IsPointInside(_vertex2)
    || rhs.IsPointInside(_vertex3)){
        return true;
    }
    else{
        return false;
    }

}




/*
int main(){
    EC2DPoint Point1 = EC2DPoint(5,2);
    EC2DPoint Point2 = EC2DPoint(3,1);
    EC2DPoint Point3 = EC2DPoint(7,1);
    EC2DPoint Point4 = EC2DPoint(0,10);

    ECTriangle T = ECTriangle(Point1, Point2, Point3);

    cout << T.GetArea() << endl;
    cout << "false: " << false << endl;
    cout << T.IsPointInside(Point4) << endl;
    
}

*/

