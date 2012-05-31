#include "units.h"
#include "ui_units.h"

Units::Units(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Units)
{
    ui->setupUi(this);
}

Units::~Units()
{
    delete ui;
}

void Units::on_buttonBox_accepted()
{
    number=ui->lineEdit->text().toInt();
    name=ui->lineEdit_2->text().toUtf8();
    QSqlQuery query;
    query.prepare("insert into units (number,name)"
                  "values(?,?)");
    query.bindValue(0,number);
    query.bindValue(1,name);
    qDebug()<<number;
    qDebug()<<name;
    if(!query.exec())
    {
        qDebug()<<query.lastError().text();
    }
}
