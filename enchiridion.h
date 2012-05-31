#ifndef ENCHIRIDION_H
#define ENCHIRIDION_H

#include <QDialog>
#include <QtSql>
#include "units.h"
#include <QInputDialog>
#include "users.h"
#include "dirorg.h"
#include "repres.h"
#include "vdoc.h"

namespace Ui {
    class Enchiridion;
}

class Enchiridion : public QDialog
{
    Q_OBJECT

public:
    explicit Enchiridion(QWidget *parent = 0);
    ~Enchiridion();
    QSqlTableModel *unitmodel;
    QSqlTableModel *postmodel;
    QSqlRelationalTableModel *usermodel;
    QSqlTableModel *orgmodel;
    QSqlRelationalTableModel *repmodel;
    QSqlTableModel *casemodel;
    QSqlTableModel *vdocmodel;
    void initUnits();
    void initPost();
    void initUser();
    void initOrg();
    void initRep();
    void initCase();
    void initVdoc();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_buttonBox_accepted();

private:
    Ui::Enchiridion *ui;
};

#endif // ENCHIRIDION_H
