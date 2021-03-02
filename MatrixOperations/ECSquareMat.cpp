#include "ECSquareMat.h"
#include <iostream>

using namespace std;

void ECSquareMat::print(ostream& os) const{

    os << "----- start ---" << endl;
    for (int i = 0; i < listMatEntries.size(); i++){
        os << "[";

        //print row of numbers
        for (int j = 0; j < listMatEntries[i].size(); j++){
            if (j != listMatEntries[i].size()-1){
                os << listMatEntries[i][j] << ",";
            }
            else{
                os << listMatEntries[i][j];
            }
        }
        os << "]" << endl;
    }
    os << "----- end ---" << endl;
}


// nDim: dimension of matrix (number of rows or columns)
ECSquareMat::ECSquareMat(int nDim){
    listMatEntries.resize(nDim,vector<int>(nDim));
}

//copy constructor
ECSquareMat::ECSquareMat(const ECSquareMat &rhs):
    listMatEntries(rhs.listMatEntries)
{}


ECSquareMat::~ECSquareMat(){
    for(vector<int> v : listMatEntries){ v.clear(); }
    listMatEntries.clear();
};

ECSquareMat & ECSquareMat:: operator=(const ECSquareMat &rhs){
    if (this == &rhs){
        return *this;
    }

    //left side size
    for(vector<int> row : listMatEntries){ row.clear(); }
    listMatEntries.clear();
    listMatEntries = rhs.listMatEntries;

    return *this;
}

int ECSquareMat::GetDimension() const{
    return listMatEntries.size();
}

void ECSquareMat::SetValAt(int nRow, int nCol, int val){
    listMatEntries[nRow][nCol] = val;
}


int ECSquareMat::GetValAt(int nRow, int nCol) const{
    return listMatEntries[nRow][nCol];
}


ECSquareMat ECSquareMat:: operator+(const ECSquareMat &rhs){

    //CHECK IF DIMENSIONS MATCH
    ECSquareMat temp(GetDimension());
    
    if ((this->listMatEntries.size() != rhs.listMatEntries.size()) || 
    (this->listMatEntries[0].size() != rhs.listMatEntries[0].size())){
        throw string("matrices of different dimensions being added");
    }
    else{
        for(int i=0; i<rhs.GetDimension(); i++){
            for(int j=0;j<rhs.GetDimension(); j++){
                    temp.SetValAt(i,j, rhs.GetValAt(i, j) + GetValAt(i, j));
                }
        }
    }

    return temp;
    
}

ECSquareMat ECSquareMat:: operator*(const ECSquareMat &rhs){

    //number of columns in the first matrix must be equal to 
    //the number of rows in the second matrix
    if (this->listMatEntries.size() != rhs.listMatEntries[0].size()){
        throw string("matrices of different dimensions being multiplied");
    }

    ECSquareMat temp(GetDimension());
    int sum = 0;
    
    //for item in row of first
    for(int i=0; i<GetDimension(); i++){
        for(int j=0; j<GetDimension(); j++){
            sum = 0;
            for(int k=0;k<GetDimension(); k++){
                sum += this->listMatEntries[i][k] * rhs.listMatEntries[k][j];
            }
                temp.SetValAt(i,j, sum);
        }
    }

    return temp;
}


int main(){
    
    ECSquareMat mat1(2);
    

	mat1.SetValAt(0,0,1);
	mat1.SetValAt(0,1,2);
	mat1.SetValAt(1,0,3);
	mat1.SetValAt(1,1,4);
    


	ECSquareMat mat2 = mat1;
    

	mat2.SetValAt(0,1,3);
	mat2.SetValAt(1,0,2);




	ECSquareMat mat3 = mat1+mat2;

    mat2.print(cout);
    mat1.print(cout);

    ECSquareMat mat4 = mat1*mat2;

    mat4.print(cout);
    


    
    //could also do ECSquaremat matrix(5)
    ECSquareMat matrix = ECSquareMat(5);
    ECSquareMat matrix2 = ECSquareMat(matrix);
    ECSquareMat matrix3 = ECSquareMat(2);

    matrix2.SetValAt(0,0,1);
    matrix2.SetValAt(1,1,2);

    matrix.SetValAt(0,0,2);

    matrix3.SetValAt(0,0,1);
    matrix3.SetValAt(0,1,1);
    matrix3.SetValAt(1,0,2);
    matrix3.SetValAt(1,1,2);


    try {
        cout << "adding: " << endl;
        matrix.print(cout);
        cout << "with: " << endl;
        matrix2.print(cout);

        matrix3 = matrix2 + matrix;
    }
    catch(string s){
        cout << "Error: " << s << endl;
        return 1;
    }

    cout << "result: " << endl;

    matrix3.print(cout);


    try{
        cout << "multiplying: " << endl;
        matrix.print(cout);
        cout << "with: " << endl;
        matrix2.print(cout);

        matrix3 = matrix2 * matrix;
    
    }
    catch(string s)
    {
        cout << "Error: " << s << endl;
        return 1;
    }
    

    cout << "result: " << endl;

    matrix3.print(cout);



    
    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              