#ifndef EC_SQUARE_MAT
#define EC_SQUARE_MAT

#include <vector>

// square matrix
class ECSquareMat
{
public:
    ECSquareMat(int nDim);     // nDim: dimension of matrix (number of rows or columns)
    ECSquareMat(const ECSquareMat &rhs);
    ~ECSquareMat();
    
    ECSquareMat &operator=(const ECSquareMat &rhs);
    int GetDimension() const;
    void SetValAt(int nRow, int nCol, int val);
    int GetValAt(int nRow, int nCol) const;
    ECSquareMat operator+(const ECSquareMat &rhs);
    ECSquareMat operator*(const ECSquareMat &rhs);
    void print(std::ostream& os) const;

    
private:
    std::vector<std::vector<int> > listMatEntries;
};


#endif

