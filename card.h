#ifndef CARD_H
#define CARD_H

#include <QDialog>
#include "dirorg.h"
#include <QDebug>
#include "repres.h"
#include "users.h"
#include <QtSql>

namespace Ui {
    class Card;
}

class Card : public QDialog
{
    Q_OBJECT

public:
    explicit Card(QWidget *parent = 0);
    ~Card();
    void initOrg();
    QSqlTableModel *modelorg;
    QSqlRelationalTableModel *modelrep;
    void initRep();
    QSqlTableModel *modeluser;
    void initUser();
    QSqlTableModel *modelcase;
    void initCase();
    QSqlTableModel *modelunits;
    void initUnits();
    void initCard();
    QString org,repres,num_disp, date_disp, num_reg, date_reg, user, topic, name, num_app, num_list;

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_6_clicked();

    void on_toolButton_7_clicked();

    void on_toolButton_5_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_buttonBox_accepted();

private:
    Ui::Card *ui;
};

#endif // CARD_H
