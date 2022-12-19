#include "Matrix.h"

using namespace algorithm;

MatrixException::MatrixException(std::string s) : msg(s)
{

}

const char* MatrixException::what() const noexcept
{
    return msg.data();
}

QString algorithm::matrix_to_qstring(Matrix<> mat)
{
    QString s;
    s.push_back('[');
    for(int r=0;r<mat.row;r++) {
        s.push_back('[');
        for(int c=0;c<mat.column;c++) {
            s+=QString::number(mat.data[r*mat.column+c]);
            if(c<mat.column-1) {
                s.push_back(',');
            }
            qDebug() << QString::number(mat.data[r*mat.column+c]);
        }
        s.push_back(']');
        if(r<mat.row-1) {
            s.push_back(',');
        }
    }
    s.push_back(']');
    return s;
}
