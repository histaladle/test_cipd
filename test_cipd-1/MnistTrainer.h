#ifndef MNISTTRAINER_H
#define MNISTTRAINER_H

#include <QRunnable>
#include "algorithm/NeutralNet.h"
#include <QFile>
class MnistTrainer : public QRunnable
{
public:
    MnistTrainer();
    void run();
    const int imageWidth=28;
    const int imageHeight=28;
    const int hiddenNum=100;
    const int outputNum=10;
    NeutralNet neutralnet;
    void train(QString filename);
    void test(QString filename);
    algorithm::Matrix<> load_csv(QString filename);
    QString dir;
    static bool save_matrix(QString path,algorithm::Matrix<> &matrix);
    static bool load_matrix(QString path,algorithm::Matrix<> &matrix);
};

#endif // MNISTTRAINER_H
