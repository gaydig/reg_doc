#include "users.h"
#include "ui_users.h"

Users::Users(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Users)
{
    ui->setupUi(this);
    Users::initUnit();
    Users::initPost();
}

Users::~Users()
{
    delete ui;
}

void Users::initUnit()
{
    umodel=new QSqlTableModel;
    umodel->setTable("units");
    ui->comboBox->setModel(umodel);
    ui->comboBox->setModelColumn(2);
    umodel->select();
}

void Users::initPost()
{
    pmodel=new QSqlTableModel;
    pmodel->setTable("post");
    ui->comboBox_2->setModel(pmodel);
    ui->comboBox_2->setModelColumn(1);
    pmodel->select();
}

void Users::on_toolButton_clicked()
{
    Units *unit=new Units(this);
    if(unit->exec()==QDialog::Accepted)
    {
        qDebug()<<"new unit";
    }
}

void Users::on_toolButton_2_clicked()
{
    bool ok;
    QString post=QInputDialog::getText(this,trUtf8("Новая должность"),trUtf8("Должность"),QLineEdit::Normal,"",&ok);
    if(ok&&!post.isEmpty())
    {
        qDebug()<<post;
    }
}

void Users::on_buttonBox_accepted()
{
    lname=ui->lineEdit->text();
    fname=ui->lineEdit_2->text();
    sname=ui->lineEdit_3->text();
    QString idunit,idpost;
    QModelIndex indexunit=ui->comboBox->model()->index(ui->comboBox->currentIndex(),0);
    idunit=ui->comboBox->model()->data(indexunit).toString();
    QModelIndex indexpost=ui->comboBox_2->model()->index(ui->comboBox_2->currentIndex(),0);
    idpost=ui->comboBox_2->model()->data(indexpost).toString();
    QSqlQuery query;
    query.prepare("insert into users (lname,fname,sname,unit_id,post_id)"
                  "values(?,?,?,?,?)");
    query.bindValue(0,lname);
    query.bindValue(1,fname);
    query.bindValue(2,sname);
    query.bindValue(3,idunit);
    query.bindValue(4,idpost);
    if(!query.exec())
    {
        qDebug()<<query.lastError().text();
    }
}
