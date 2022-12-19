#include "MnistTrainer.h"
#include <QDebug>
#include <QThread>
#include <QTime>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
MnistTrainer::MnistTrainer()
    : QRunnable (),
      neutralnet(imageWidth*imageHeight,hiddenNum,outputNum)
{
    setAutoDelete(false);
//    dir="C:/Users/admin/Desktop/songyijie/python_nn";
    dir="C:/Users/Administrator/Desktop/python_nn";
}

void MnistTrainer::train(QString filename)
{
    QFile trainfile(filename);
//    QFile trainfile("d:/work/developing/mnist_train.csv");
    QByteArray ba;
    QString alltext;
    QString textline;
    QStringList textlines;
    QStringList texts;
    int imw=imageWidth,imh=imageHeight;
    algorithm::Matrix<> train_input(imw*imh,1);
    algorithm::Matrix<> train_output(outputNum,1);
    double x=0.0;
    int mark=0;
    double max_output=0.0;
    int fitindex=0;
    int train_correct=0,train_num=0;
    if(trainfile.exists() && trainfile.open(QFile::ReadOnly)) {
        while(!trainfile.atEnd()) {
            ++train_num;
            ba=trainfile.readLine();
            textline=ba;
            textline=textline.trimmed();
            texts=textline.split(",");
            mark=texts.first().toInt();
            texts.removeFirst();
            for(int i=0;i<imw*imh;i++) {
                x=texts[i].toDouble()/255.0*0.98+0.01;
                train_input(i,0)=x;
            }
            train_output.fill(0.01);
            train_output(mark,0)=0.99;
            neutralnet.train(train_input,train_output);
            train_output=neutralnet.query(train_input);
            max_output=train_output.data[0];
            fitindex=0;
            for(int i=0;i<train_output.row*train_output.column;i++) {
                if(max_output<train_output.data[i]) {
                    max_output=train_output.data[i];
                    fitindex=i;
                }
            }
            if(mark==fitindex) {
                ++train_correct;
            }
        }
        trainfile.close();
        qDebug() << "train correct ratio" << train_correct << train_num;
    }
    else {
        return ;
    }
    qDebug() << "training finished";
}
void MnistTrainer::test(QString filename)
{
    QFile testfile(filename);
    QByteArray ba;
    QString textline;
    QStringList texts;
//    QList<int> linedata;
    int imw=imageWidth,imh=imageHeight;
    int test_correct=0,test_num=0;
    int mark=0,fitindex=0;
    double x=0.0,max_output=0.0;
//    QFile testfile("d:/work/developing/mnist_test.csv");
    algorithm::Matrix<> test_input(imw*imh,1);
    algorithm::Matrix<> test_output(outputNum,1);
    if(testfile.exists()&&testfile.open(QFile::ReadOnly)) {
        while(!testfile.atEnd()) {
            ++test_num;
            ba=testfile.readLine();
            textline=ba;
            textline=textline.trimmed();
            texts=textline.split(",");
            mark=texts.first().toInt();
            texts.removeFirst();
            for(int i=0;i<imw*imh;i++) {
                x=texts[i].toDouble()/255.0*0.98+0.01;
                test_input(i,0)=x;
            }
            test_output=neutralnet.query(test_input);
            max_output=test_output.data[0];
            fitindex=0;
            for(int i=0;i<test_output.row*test_output.column;i++) {
                if(max_output<test_output.data[i]) {
                    max_output=test_output.data[i];
                    fitindex=i;
                }
            }
            if(mark==fitindex) {
                ++test_correct;
            }
        }
        testfile.close();
        qDebug() << "test correct ratio" << test_correct << test_num;
    }
    else {
        return ;
    }
    qDebug() << "test finished";
}

void MnistTrainer::run()
{
    neutralnet.w_ho=load_csv(dir+"/who.csv");
    neutralnet.w_ih=load_csv(dir+"/wih.csv");
    QTime t;
    t.start();
    QString train_filename=dir+"/mnist_train.csv";
    train(train_filename);
    QString test_filename=dir+"/mnist_test.csv";
    test(test_filename);
    qDebug() << "mnist cost time:" << t.elapsed();
}

algorithm::Matrix<> MnistTrainer::load_csv(QString filename)
{
    algorithm::Matrix<> mat(1,1);
    QFile file(filename);
    QByteArray ba;
    QString textline;
    QStringList texts;
    QList<double> linedata;
    QList<QList<double> > matdata;
    int row=0,col=0;
    if(file.exists()&&file.open(QFile::ReadOnly)) {
        while(!file.atEnd()) {
            ba=file.readLine();
            textline=ba;
            texts=textline.split(',');
            linedata.clear();
            for(int i=0;i<texts.size();i++) {
                linedata.append(texts[i].toDouble());
            }
            matdata.append(linedata);
            ++row;
            if(linedata.size()>col) {
                col=linedata.size();
            }
        }
    }
    algorithm::Matrix<> mat1(row,col);
    for(int r=0;r<row;r++) {
        for(int c=0;c<col;c++) {
            mat1(r,c)=matdata[r][c];
        }
    }
    return mat1;
}

bool MnistTrainer::save_matrix(QString path, algorithm::Matrix<> &matrix)
{
    bool ok=false;
    QFile file(path);
    if(!file.open(QFile::WriteOnly)) {
        return ok;
    }
    QXmlStreamWriter ws(&file);
    ws.setAutoFormatting(true);
    ws.writeStartDocument();
    ws.writeStartElement("matrix");//<matrix>
    ws.writeAttribute("type","d");
    ws.writeStartElement("row");//<row>
    ws.writeCharacters(QString::number(matrix.row));
    ws.writeEndElement();//</row>
    ws.writeStartElement("column");//<column>
    ws.writeCharacters(QString::number(matrix.column));
    ws.writeEndElement();//</column>
    for(int r=0;r<matrix.row;r++) {
        for(int c=0;c<matrix.column;c++) {
            ws.writeStartElement("data");//<data>
            ws.writeAttribute("r",QString::number(r));
            ws.writeAttribute("c",QString::number(c));
            ws.writeCharacters(QString::number(matrix(r,c)));
            ws.writeEndElement();//</data>
        }
    }
    ws.writeEndElement();//</matrix>
    ws.writeEndDocument();
    file.close();
    return true;
}

bool MnistTrainer::load_matrix(QString path,algorithm::Matrix<> &matrix)
{
    bool ok=false;
    bool readrow=false;
    bool readcolumn=false;
    int row=0,column=0;
    int r=0,c=0;
    QFile file(path);
    if(!file.exists()) {
        return false;
    }
    if(!file.open(QFile::ReadOnly)) {
        return false;
    }
    QXmlStreamReader rs(&file);
    QStringList names;
    while(!rs.atEnd()) {
        int token=rs.readNext();
        qDebug() << token << rs.name();
        if(token==QXmlStreamReader::StartElement) {
            if(rs.name()=="matrix") {
                ok=true;
                ok&=(rs.attributes().hasAttribute("type"));
                ok&=(rs.attributes().value("type")=="d");
                if(ok) {
                    names.append(rs.name().toString());
                }
                else {
                    return false;
                }
            }
            else if(rs.name()=="row") {
                names.append(rs.name().toString());
            }
            else if(rs.name()=="column") {
                names.append(rs.name().toString());
            }
            else if(rs.name()=="data") {
                ok=true;
                ok&=rs.attributes().hasAttribute("r");
                ok&=rs.attributes().hasAttribute("c");
                bool ok1=false;
                r=rs.attributes().value("r").toInt(&ok1);
                if(!ok1) return false;
                c=rs.attributes().value("c").toInt(&ok1);
                if(!ok1) return false;
            }
        }
        else if(token==QXmlStreamReader::EndElement) {
            names.removeLast();
        }
        else if(token==QXmlStreamReader::Characters) {
            if(names.last()=="row") {
                row=rs.text().toInt(&ok);
                if(!ok) {
                    return false;
                }
                readrow=true;
                if(readcolumn) {
                    if(matrix.row*matrix.column!=row*column) {
                        delete [] matrix.data;
                        matrix.alloc(row*column);
                    }
                    matrix.column=column;
                }
                matrix.row=row;
            }
            else if(names.last()=="column") {
                column=rs.text().toInt(&ok);
                if(!ok) {
                    return false;
                }
                readcolumn=true;
                if(readrow) {
                    if(matrix.row*matrix.column!=row*column) {
                        delete [] matrix.data;
                        matrix.alloc(row*column);
                    }
                    matrix.row=row;
                }
                matrix.column=column;
            }
            else if(names.last()=="data") {
                bool ok1=false;
                double d=rs.text().toDouble(&ok1);
                if(!ok1) {
                    return false;
                }
                matrix(r,c)=d;
            }
        }
    }
    return true;
}
