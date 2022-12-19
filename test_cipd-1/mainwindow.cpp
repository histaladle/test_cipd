#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPushButton>
#include <QMatrix4x4>
#include <QImage>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << QString::fromStdString(algorithm::test_permutation());
    statusLbl=new QLabel(this);
    ui->statusBar->addWidget(statusLbl);

    algorithm::Matrix<> mat1(3,3),mat2(3,3),mat3(3,3),mat4(3,3),mat5(3,3);
    mat1(0,0)=1;mat1(0,1)=2;mat1(0,2)=3;
    mat1(1,0)=4;mat1(1,1)=5;mat1(1,2)=6;
    mat1(2,0)=7;mat1(2,1)=8;mat1(2,2)=0;

    mat2(0,0)=1;mat2(0,1)=2;mat2(0,2)=1;
    mat2(1,0)=1;mat2(1,1)=1;mat2(1,2)=2;
    mat2(2,0)=2;mat2(2,1)=1;mat2(2,2)=1;

//    mat3=mat1*mat2;
    MnistTrainer::load_matrix("mat3.xml",mat3);
    qDebug() << QString::fromStdString(mat3.to_string());
    qDebug() << QString::fromStdString(mat1.multiply(mat2).to_string());
    mat4(0,0)=1;mat4(0,1)=3;mat4(0,2)=5;
    mat4(1,0)=2;mat4(1,1)=4;mat4(1,2)=6;
    mat4(2,0)=3;mat4(2,1)=5;mat4(2,2)=7;
    mat4.transposed();
//    qDebug() << QString::fromStdString(mat4.to_string());
//    qDebug() << mat2.determinant();

    mat2.inverted();
    qDebug() << QString::fromStdString(mat2.to_string());

    algorithm::Matrix<> mat6(2,3);
    mat6(0,0)=1;mat6(0,1)=2;mat6(0,2)=3;
    mat6(1,0)=3;mat6(1,1)=4;mat6(1,2)=5;
    mat6.transposed();
    qDebug() << QString::fromStdString(mat6.to_string());
    qDebug() << QString::fromStdString(mat6.transpose().to_string());

    int r=10,c=10;
    algorithm::Matrix<> mat10(r,c);
    for(int i=0;i<r*c;i++) {
        mat10.data[i]=1.0*(rand()%100)/100;
    }
    algorithm::Matrix<> mat20(2,4),mat21(4,3),mat22(2,3);
    mat20(0,0)=1;mat20(0,1)=0;mat20(0,2)=3;mat20(0,3)=-1;
    mat20(1,0)=2;mat20(1,1)=1;mat20(1,2)=0;mat20(1,3)=2;

    mat21(0,0)= 4;mat21(0,1)=1;mat21(0,2)=0;
    mat21(1,0)=-1;mat21(1,1)=1;mat21(1,2)=3;
    mat21(2,0)= 2;mat21(2,1)=0;mat21(2,2)=1;
    mat21(3,0)= 1;mat21(3,1)=3;mat21(3,2)=4;
    mat20.transposed();
    mat22=mat20.transpose()*mat21;
    qDebug() << QString::fromStdString(mat22.to_string());
//    qDebug() << QString::fromStdString(mat10.to_string());
//    QTime t;
//    t.start();
//    qDebug() << mat10.determinant();
//    qDebug() << "debug67" << t.elapsed();

//    t.start();
//    qDebug() << mat10.laplace_expansion();
//    qDebug() << "debug68" << t.elapsed();

//    NeutralNet nn(2,2,2);
//    qDebug() << "debug70" << QString::fromStdString(nn.w_ih.to_string());

//    QFile csvfile("d:/work/developing/mnist_train.csv");
//    QByteArray ba;
//    QString textline;
//    QStringList texts;
//    QList<int> linedata;
//    int imw=28,imh=28;
//    QImage image(imw,imh,QImage::Format_ARGB32);
//    if(csvfile.exists() && csvfile.open(QFile::ReadOnly)) {
//        ba=csvfile.readLine();
//        textline=ba;
//        texts=textline.split(",");
//        for(int i=0;i<texts.size();i++) {
//            linedata.append(texts[i].toInt());
//        }
//    }
//    csvfile.close();
//    for(int h=0;h<image.height();h++) {
//        for(int w=0;w<image.width();w++) {
//            image.setPixel(w,h,qRgba(0,0,0,linedata[h*image.width()+w]));
//        }
//    }
    QLabel *lbl=new QLabel(ui->tab_net);
//    lbl->setPixmap(QPixmap::fromImage(image));
    ui->gridLayout_tab_net->addWidget(lbl);

    MnistTrainer nntrainer;
    qDebug() << "debug14" << nntrainer.neutralnet.inputNodes
             << nntrainer.neutralnet.hiddenNodes;
//    nntrainer.run();

    std::vector<fal::Card> cardvec;
    for(int i=0;i<fal::PLAYER_NUM;i++) {
        fal::sort(game.players[i]->cards);
    }
    for(int i=0;i<fal::PLAYER_NUM;i++) {
        int playerindex=i;
        cardListUis[i]=createCardListUi(game.players[i]);
        for(int j=0;j<cardListUis[i].checks.size();j++) {
            connect(cardListUis[i].checks[j],&QCheckBox::stateChanged,this,[this,playerindex](int) {
                QCheckBox *check=nullptr;
                std::vector<fal::Card> selcardvec;
                for(int i=0;i<this->cardListUis[playerindex].checks.size();i++) {
                    check=cardListUis[playerindex].checks[i];
                    if(check->isChecked()) {
                        selcardvec.push_back(this->game.players[playerindex]->cards[size_t(i)]);
                    }
                }
                fal::Combination comb(selcardvec);
                QString s;
                int comtype=comb.getCombinationType();
                if(comtype==fal::Combination::ErrorCombination) {
                    s="error combination";
                }
                else if(comtype==fal::Combination::UnknownCombination) {
                    s="unknown combination";
                }
                else {
                    fal::Combination::sortInPlay(selcardvec);
                    for(size_t i=0;i<selcardvec.size();i++) {
                        if(selcardvec[i].getColor()==fal::Card::Red) {
                            s.append("<font color=#ff0000>");
                        }
                        s.append("[");
                        s.append(QString::fromStdString(selcardvec[i].getText()));
                        s.append(" ");
                        s.append(QString::fromStdString(selcardvec[i].getSuitText()));
                        s.append("]");
                        if(selcardvec[i].getColor()==fal::Card::Red) {
                            s.append("</font>");
                        }
                        if(i%5==4) {
                            s.append("<br/>");
                        }
                    }
                }
                this->cardListUis[playerindex].selCardsLbl->setText(s);
            });
        }
        connect(cardListUis[i].play,&QPushButton::released,this,[this,playerindex](){
            for(int i=0;i<cardListUis[playerindex].checks.size();i++) {
                if(cardListUis[playerindex].checks[i]->isChecked()) {
                    cardListUis[playerindex].groupLayout->removeWidget(cardListUis[playerindex].checks[i]);
                    cardListUis[playerindex].checks[i]->deleteLater();
                    cardListUis[playerindex].checks.removeAt(i);
                    this->game.players[playerindex]->cards.erase(this->game.players[playerindex]->cards.begin()+i);
                    i--;
                }
            }
        });
    }
    for(int i=0;i<fal::PLAYER_NUM;i++) {
        ui->gridLayout_tab_card->addWidget(cardListUis[i].groupBox,0,i);
    }

    qDebug() << "debug65" << game.players[0]->cards.size()
             << game.players[1]->cards.size()
             << game.players[2]->cards.size();
    QPushButton *btn=new QPushButton("clear",this);
    connect(btn,&QPushButton::released,this,[this](){
        for(int i=0;i<fal::PLAYER_NUM;i++) {
            clearCardListUi(cardListUis[i]);
        }
    });
    ui->gridLayout_tab_card->addWidget(btn,ui->gridLayout_central->rowCount(),0);
}

CardListUi MainWindow::createCardListUi(fal::Player *player)
{
    QList<fal::Card> cards=stdVectorToQList(player->cards);
    CardListUi cardListUi;

    QCheckBox *check=nullptr;
    QString s;

    cardListUi.groupBox=new QGroupBox(this);
    cardListUi.groupLayout=new QGridLayout(cardListUi.groupBox);

    for(int i=0;i<cards.size();i++) {
        check=new QCheckBox(cardListUi.groupBox);
        s.clear();

//        s.append(QString::fromStdString(cards[i].getText()));
        s.append(QString::number(cards[i].point));
        s.append(" ");
//        s.append(QString::fromStdString(cards[i].getSuitText()));
        s.append(QString::number(cards[i].suit));

        if(cards[i].getColor()==fal::Card::Red) {
            check->setStyleSheet("color:#ff0000");
        }
        check->setText(s);
        cardListUi.groupLayout->addWidget(check,i,0);
        cardListUi.checks.append(check);
    }

    QVBoxLayout *vlayout=new QVBoxLayout();
    cardListUi.bottomSpacerLayout=vlayout;
    vlayout->addStretch(0);

    cardListUi.groupLayout->addLayout(vlayout,cardListUi.groupLayout->rowCount(),0,1,1,Qt::AlignCenter);

    QLabel *lbl=new QLabel(cardListUi.groupBox);
    cardListUi.selCardsLbl=lbl;
    cardListUi.groupLayout->addWidget(cardListUi.selCardsLbl,cardListUi.groupLayout->rowCount(),0,1,1,Qt::AlignLeft|Qt::AlignVCenter);

    QPushButton *btn=new QPushButton("play",cardListUi.groupBox);
    cardListUi.play=btn;
    cardListUi.groupLayout->addWidget(cardListUi.play,cardListUi.groupLayout->rowCount(),0,1,1,Qt::AlignLeft|Qt::AlignVCenter);

    return cardListUi;
}

void MainWindow::clearCardListUi(CardListUi &cardListUi)
{
    for(int i=0;i<cardListUi.checks.size();i++) {
        cardListUi.checks[i]->deleteLater();
    }
    cardListUi.checks.clear();
    cardListUi.bottomSpacerLayout->deleteLater();
    cardListUi.bottomSpacerLayout=nullptr;
    cardListUi.groupLayout->deleteLater();
    cardListUi.groupLayout=nullptr;
    cardListUi.groupBox->deleteLater();
    cardListUi.groupBox=nullptr;
}

void MainWindow::onCardToggled(int id,bool checked)
{
    Q_UNUSED(id);
    Q_UNUSED(checked);

    QList<fal::Card> cards;
//    int checkid;
//    for(int i=0;i<lordCardListUi.checks.size();i++) {
//        if(lordCardListUi.checks[i]->isChecked()) {
//            checkid=lordCardListUi.btnGroup->id(lordCardListUi.checks[i]);
//            cards.append(lordCards[checkid]);
//        }
//    }
    QString s;
    fal::Combination comb(qlistToStdVector(cards));
    if(comb.getCombinationType()==fal::Combination::ErrorCombination) {
        statusLbl->setText("error combination");
    }
    else if(comb.getCombinationType()==fal::Combination::UnknownCombination) {
        statusLbl->setText("unknown combination");
    }
    else {
        std::vector<fal::Card> cardvec=qlistToStdVector(cards);
        fal::Combination::sortInPlay(cardvec);
        cards=stdVectorToQList(cardvec);
        s.clear();
        for(int i=0;i<cards.size();i++) {
            s.append("[");
            s.append(QString::fromStdString(cards[i].getText()));
            s.append(" ");
            s.append(QString::fromStdString(cards[i].getSuitText()));
            s.append("]");
            if(cards[i].getColor()==fal::Card::Red) {
                s.prepend("<font color=#ff0000>");
                s.append("</font>");
            }
        }
        statusLbl->setText(s);
    }
    qDebug() << "debug10";
}

MainWindow::~MainWindow()
{
    delete ui;
}
