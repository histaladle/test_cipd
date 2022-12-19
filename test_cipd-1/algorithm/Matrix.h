#ifndef MATRIX_H
#define MATRIX_H
#include <string>
#include <iostream>
#include <QDebug>
#include <QString>
#include "algorithm.h"
namespace algorithm {
class MatrixException : public std::exception
{
public:
    MatrixException(std::string s);
    const char* what() const noexcept;
private:
    const std::string msg;
};

template<class T=double> class Matrix
{
public:
    Matrix(int row,int column) :row(row),column(column)
    {
        data=new T[row*column];
    }
    Matrix(const Matrix<T> &mat)
    {
        row=mat.row;
        column=mat.column;
        data=new T[row*column];
        for(int i=0;i<row*column;i++) {
            data[i]=mat.data[i];
        }
    }
    ~Matrix()
    {
        if(data!=nullptr) {
            delete[] data;
        }
    }
    int row=0,column=0;
    T *data=nullptr;
    T& operator()(int r,int c)
    {
        return data[r*column+c];
    }
    Matrix<T>& operator=(const Matrix<T> &m)
    {
        if(m.row*m.column!=row*column) {
            if(data!=nullptr) {
                delete [] data;
            }
            data=new T[row*column];
        }
        row=m.row;
        column=m.column;
        for(int i=0;i<row*column;i++) {
            data[i]=m.data[i];
        }
        return (*this);
    }
    Matrix<T> operator+(const Matrix<T> &m)
    {
        if(row!=m.row||column!=m.column) {
            throw MatrixException("Matrix Exception in operation+");
        }
        Matrix<T> mat(row,column);
        for(int i=0;i<row*column;i++) {
            mat.data[i]=data[i]+m.data[i];
        }
        return mat;
    }
    Matrix<T> operator-(const Matrix<T> &m)
    {
        if(row!=m.row||column!=m.column) {
            throw MatrixException("Matrix Exception in operation-");
        }
        Matrix<T> mat(row,column);
        for(int i=0;i<row*column;i++) {
            mat.data[i]=data[i]-m.data[i];
        }
        return mat;
    }
    Matrix<T> operator*(const double d)
    {
        Matrix<T> mat(row,column);
        for(int r=0;r<row;r++) {
            for(int c=0;c<column;c++) {
                mat(r,c)=data[r*column+c]*d;
            }
        }
        return mat;
    }
    Matrix<T> operator*(const Matrix<T> &m)
    {
        if(column!=m.row) {
            throw MatrixException("Matrix Exception in operation*");
        }
        int column1=m.column;
        Matrix<T> mat(row,column1);
        for(int r=0;r<row;r++) {
            for(int c=0;c<column1;c++) {
                mat(r,c)=0;
                for(int i=0;i<column;i++) {
                    mat(r,c)+=data[r*column+i]*m.data[i*column1+c];
                }
            }
        }
        return mat;
    }
    Matrix<T> multiply(const Matrix<T> &m)
    {
        if(row!=m.row||column!=m.column) {
            throw MatrixException("Matrix Exception in multiply");
        }
        Matrix<> mat(m.row,m.column);
        if(m.row!=row||m.column!=column) {
            return mat;
        }
        for(int i=0;i<row*column;i++) {
            mat.data[i]=data[i]*m.data[i];
        }
        return mat;
    }
    std::string to_string()
    {
        std::string s;
        s.push_back('[');
        for(int r=0;r<row;r++) {
            s.push_back('[');
            for(int c=0;c<column;c++) {
                s+=std::to_string(data[r*column+c]);
                if(c<column-1) {
                    s.push_back(',');
                }
            }
            s.push_back(']');
            if(r<row-1) {
                s.push_back(',');
            }
        }
        s.push_back(']');
        return s;
    }
    void setToIdentity()
    {
        if(row!=column) {
            throw MatrixException("Matrix Exception in identity");
        }
        for(int r=0;r<row;r++) {
            data[r*column+r]=1.0;
        }
    }
    void inverted()
    {
        if(row!=column) {
            throw MatrixException("Matrix Exception in inverted");
        }
        if(row==0||column==0) {
            return ;
        }
        double d=0.0;
        Matrix<T> mat(row,column);
        Matrix<T> mat1(row-1,column-1);
        int s=0;
        for(int r=0;r<row;r++) {
            for(int c=0;c<column;c++) {
                for(int r1=0;r1<row-1;r1++) {
                    for(int c1=0;c1<column-1;c1++) {
                        int m=r1,n=c1;
                        if(r<=m) {
                            ++m;
                        }
                        if(c<=n) {
                            ++n;
                        }
                        mat1(r1,c1)=data[m*column+n];
                    }
                }
                d=mat1.determinant();
                mat(r,c)=d;
                if((r+c)%2) {
                    s=-1;
                }
                else {
                    s=1;
                }
                mat(r,c)=s*mat(r,c);
            }
        }
        mat.transposed();
        d=determinant();
        if(d==0.0) {
            return ;
        }
        for(int r=0;r<row;r++) {
            for(int c=0;c<column;c++) {
                mat(r,c)*=(1.0/d);
            }
        }
        for(int i=0;i<row*column;i++) {
            data[i]=mat.data[i];
        }
        return ;
    }

    T laplace_expansion()
    {
        if(row!=column) {
            throw MatrixException("Matrix Exception in laplace");
        }
        T d=T(0.0),a=T(0.0);
        if(row==1) {
            return data[0];
        }
        Matrix<T> mat1(row-1,column-1);
        int s=0;
        for(int r=0;r<1;r++) {
            for(int c=0;c<column;c++) {
                for(int r1=0;r1<row-1;r1++) {
                    for(int c1=0;c1<column-1;c1++) {
                        int m=r1,n=c1;
                        if(r<=m) {
                            ++m;
                        }
                        if(c<=n) {
                            ++n;
                        }
                        mat1(r1,c1)=data[m*column+n];
                    }
                }
                a=mat1.laplace_expansion();
                if((r+c)%2) {
                    s=-1;
                }
                else {
                    s=1;
                }
                d+=s*a*data[r*column+c];
            }
        }
        return d;
    }

    double determinant()
    {
        if(row!=column) {
            throw MatrixException("Matrix Exception in determinant");
        }
        if(row==0||column==0) {
            return 0.0;
        }
        double d=0.0;
        std::vector<std::vector<int> > res;
        std::vector<int> nums;
        for(int i=0;i<row;i++) {
            nums.push_back(i);
        }
        permutation(nums,0,res);
        int invnum=0;
        int t=0;
        for(size_t i=0;i<res.size();i++) {
            invnum=0;
            for(size_t j=0;j<res[i].size();j++) {
                for(size_t k=j;k<res[i].size();k++) {
                    if(res[i][j]>res[i][k]) {
                        ++invnum;
                    }
                }
            }
            if(invnum%2) {
                t=-1;
            }
            else {
                t=1;
            }
            double a=1.0;
            for(size_t j=0;j<res[i].size();j++) {
                a*=data[int(j)*column+res[i][j]];
            }
            d+=t*a;
        }
        return d;
    }

    void transposed()
    {
        T buf[row*column];
        for(int i=0;i<row*column;i++) {
            buf[i]=data[i];
        }
        for(int r=0;r<row;r++) {
            for(int c=0;c<column;c++) {
                data[c*row+r]=buf[r*column+c];
            }
        }
        std::swap(row,column);
    }

    void fill(T t)
    {
        for(int r=0;r<row;r++) {
            for(int c=0;c<column;c++) {
                data[r*column+c]=t;
            }
        }
    }

    Matrix<> invert()
    {
        if(row!=column) {
            throw MatrixException("Matrix Exception in invert");
        }
        Matrix<> mat(row,column);
        for(int i=0;i<row*column;i++) {
            mat.data[i]=data[i];
        }
        mat.inverted();
        return mat;
    }

    Matrix<T> transpose()
    {
        Matrix<T> mat(row,column);
        for(int i=0;i<row*column;i++) {
            mat.data[i]=data[i];
        }
        mat.transposed();
        return mat;
    }

    void alloc(int n)
    {
        data=new T[n]{0};
    }
};
extern QString matrix_to_qstring(Matrix<> mat);
}

#endif // MATRIX_H
