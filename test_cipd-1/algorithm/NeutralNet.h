#ifndef NEUTRALNET_H
#define NEUTRALNET_H

#include "Matrix.h"
#include <cmath>
class NeutralNet
{
public:
    NeutralNet(int inputNum,int hiddenNum,int outputNum);
    int inputNodes;
    int hiddenNodes;
    int outputNodes;
    double learningRate=0.3;
    algorithm::Matrix<> w_ih,w_ho;

    algorithm::Matrix<> query(algorithm::Matrix<> input);
    algorithm::Matrix<> activation(algorithm::Matrix<> input);
    void train(algorithm::Matrix<> input,algorithm::Matrix<> target);
    static void debug(algorithm::Matrix<> mat)
    {
        for(int r=0;r<mat.row;r++) {
            for(int c=0;c<mat.column;c++) {
                qDebug() << r << c << mat(r,c);
            }
        }
    }
    int train_num=0;
};

#endif // NEUTRALNET_H
