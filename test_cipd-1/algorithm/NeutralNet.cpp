#include "NeutralNet.h"
#include <random>
NeutralNet::NeutralNet(int inputNum, int hiddenNum, int outputNum)
    :w_ih(hiddenNum,inputNum),w_ho(outputNum,hiddenNum)
{
    inputNodes=inputNum;
    hiddenNodes=hiddenNum;
    outputNodes=outputNum;
//    std::default_random_engine random(uint(time(nullptr)));
    std::default_random_engine random;
    std::normal_distribution<double> ih_dist(0.0,pow(hiddenNum,-0.5));
    std::normal_distribution<double> ho_dist(0.0,pow(outputNum,-0.5));
    for(int r=0;r<w_ih.row;r++) {
        for(int c=0;c<w_ih.column;c++) {
            w_ih(r,c)=1.0*(abs(rand())%900)/1000.0-0.45;
//            w_ih(r,c)=ih_dist(random);
        }
    }

    for(int r=0;r<w_ho.row;r++) {
        for(int c=0;c<w_ho.column;c++) {
            w_ho(r,c)=1.0*(abs(rand())%900)/1000.0-0.45;
//            w_ho(r,c)=ho_dist(random);
        }
    }
}

void NeutralNet::train(algorithm::Matrix<> input,algorithm::Matrix<> target)
{
    train_num++;
    algorithm::Matrix<> hiddenInput=w_ih*input;
    algorithm::Matrix<> hiddenOutput=activation(hiddenInput);
    algorithm::Matrix<> finalInput=w_ho*hiddenOutput;
    algorithm::Matrix<> finalOutput=activation(finalInput);
    algorithm::Matrix<> outputError=target-finalOutput;
    algorithm::Matrix<> hiddenError=w_ho.transpose()*outputError;
    algorithm::Matrix<> mat1(finalOutput.row,finalOutput.column);
    mat1.fill(1.0);
//    outputError=outputError*learningRate;
//    hiddenError=hiddenError*learningRate;
    algorithm::Matrix<> delta_w_ho=outputError.multiply(finalOutput).multiply(mat1-finalOutput)*hiddenOutput.transpose();
    delta_w_ho=delta_w_ho*learningRate;
    w_ho=w_ho+delta_w_ho;

    algorithm::Matrix<> mat2(hiddenOutput.row,hiddenOutput.column);
    mat2.fill(1.0);
    algorithm::Matrix<> delta_w_ih=hiddenError.multiply(hiddenOutput).multiply(mat2-hiddenOutput)*input.transpose();
    delta_w_ih=delta_w_ih*learningRate;
    w_ih=w_ih+delta_w_ih;
}

algorithm::Matrix<> NeutralNet::activation(algorithm::Matrix<> input)
{
    algorithm::Matrix<> output(input.row,input.column);
    for(int r=0;r<input.row;r++) {
        for(int c=0;c<input.column;c++) {
            output(r,c)=1.0/(1.0+::exp(-input(r,c)));
        }
    }
    return output;
}
algorithm::Matrix<> NeutralNet::query(algorithm::Matrix<> input)
{
    algorithm::Matrix<> hidden_input(hiddenNodes,1);
    algorithm::Matrix<> hidden_output(hiddenNodes,1);
    algorithm::Matrix<> final_input(outputNodes,1);
    algorithm::Matrix<> final_output(outputNodes,1);

    hidden_input=w_ih*input;
    hidden_output=activation(hidden_input);
    final_input=w_ho*hidden_output;
    final_output=activation(final_input);
    return final_output;
}
