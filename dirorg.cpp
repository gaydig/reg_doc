#include "dirorg.h"
#include "ui_dirorg.h"

DirOrg::DirOrg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DirOrg)
{
    ui->setupUi(this);
}

DirOrg::~DirOrg()
{
    delete ui;
}

void DirOrg::on_buttonBox_accepted()
{
    name=ui->lineEdit->text();
    fullname=ui->textEdit->document()->toPlainText();
    address=ui->textEdit_2->document()->toPlainText();
    qDebug()<<name<<fullname<<address;
    QSqlQuery query;
    query.prepare("insert into dir_org (name,fullname,address)"
                  "values(?,?,?)");
    query.bindValue(0,name);
    query.bindValue(1,fullname);
    query.bindValue(2,address);
    //qDebug()<<number;
    //qDebug()<<name;
    if(!query.exec())
    {
        qDebug()<<query.lastError().text();
    }
}
