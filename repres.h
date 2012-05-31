#ifndef REPRES_H
#define REPRES_H

#include <QDialog>
#include "dirorg.h"
#include <QDebug>
#include <QtSql>

namespace Ui {
    class Repres;
}

class Repres : public QDialog
{
    Q_OBJECT

public:
    explicit Repres(QWidget *parent = 0);
    ~Repres();
    void initOrg();
    QSqlTableModel *modelorg;

private slots:
    void on_toolButton_clicked();

private:
    Ui::Repres *ui;
};

#endif // REPRES_H
