#ifndef UNITS_H
#define UNITS_H

#include <QDialog>
#include <QtSql>

namespace Ui {
    class Units;
}

class Units : public QDialog
{
    Q_OBJECT

public:
    explicit Units(QWidget *parent = 0);
    ~Units();
    int number;
    QString name;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Units *ui;
};

#endif // UNITS_H
