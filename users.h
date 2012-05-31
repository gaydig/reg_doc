#ifndef USERS_H
#define USERS_H

#include <QDialog>
#include <QInputDialog>
#include <QDebug>
#include "units.h"

namespace Ui {
    class Users;
}

class Users : public QDialog
{
    Q_OBJECT

public:
    explicit Users(QWidget *parent = 0);
    ~Users();
    QString lname,fname,sname,unit,post;
    QSqlTableModel *umodel;
    QSqlTableModel *pmodel;
    void initUnit();
    void initPost();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_buttonBox_accepted();

private:
    Ui::Users *ui;
};

#endif // USERS_H
