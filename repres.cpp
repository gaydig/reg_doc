#include "repres.h"
#include "ui_repres.h"

Repres::Repres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Repres)
{
    ui->setupUi(this);
    Repres::initOrg();
}

Repres::~Repres()
{
    delete ui;
}

void Repres::on_toolButton_clicked()
{
    DirOrg *org=new DirOrg(this);
    if(org->exec()==QDialog::Accepted)
    {
        qDebug()<<"new org";
        modelorg->select();
    }
}

void Repres::initOrg()
{
    modelorg=new QSqlTableModel;
    modelorg->setTable("dir_org");
    ui->comboBox->setModel(modelorg);
    ui->comboBox->setModelColumn(3);
    modelorg->select();
}
