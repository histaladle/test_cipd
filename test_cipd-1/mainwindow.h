#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "againstlandlord/game.h"
#include "algorithm/algorithm.h"
#include "algorithm/Matrix.h"
#include <QLabel>
#include <QButtonGroup>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTime>
#include <QDebug>
#include <QThread>
#include "algorithm/NeutralNet.h"
#include "MnistTrainer.h"
namespace Ui {
class MainWindow;
}
struct CardListUi
{
    QGroupBox *groupBox=nullptr;
    QGridLayout *groupLayout=nullptr;
    QList<QCheckBox*> checks;
    QVBoxLayout *bottomSpacerLayout=nullptr;
    QLabel *selCardsLbl=nullptr;
    QPushButton *play=nullptr;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    template<class T> static QList<T> stdVectorToQList(std::vector<T> vec)
    {
        QList<T> list;
        if(vec.size()==0) {
            return list;
        }
        for(size_t i=0;i<vec.size();i++) {
            list.append(vec[i]);
        }
        return list;
    }
    template<class T> static std::vector<T> qlistToStdVector(QList<T> list)
    {
        std::vector<T> vec;
        if(list.size()==0) {
            return vec;
        }
        for(int i=0;i<list.size();i++) {
            vec.push_back(list[i]);
        }
        return vec;
    }


private:
    CardListUi cardListUis[fal::PLAYER_NUM];

    CardListUi createCardListUi(fal::Player *player);
    void clearCardListUi(CardListUi &cardListUi);

private slots:
    void onCardToggled(int id,bool checked);
private:
    Ui::MainWindow *ui;
    QLabel *statusLbl=nullptr;
    fal::Game game;
};

#endif // MAINWINDOW_H
