#include "card.h"
#include "ui_card.h"

Card::Card(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Card)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    Card::initOrg();
    Card::initRep();
    Card::initUser();
    Card::initCase();
    Card::initUnits();
}

Card::~Card()
{
    delete ui;
}

void Card::initOrg()
{
    modelorg=new QSqlTableModel;
    modelorg->setTable("dir_org");
    ui->comboBox->setModel(modelorg);
    ui->comboBox->setModelColumn(3);
    modelorg->select();
}

void Card::initRep()
{
    QString id;
    QModelIndex index=ui->comboBox->model()->index(ui->comboBox->currentIndex(),0);
    id=ui->comboBox->model()->data(index).toString();
    modelrep=new QSqlRelationalTableModel;
    modelrep->setTable("repres");
    ui->comboBox_2->setModel(modelrep);
    modelrep->setFilter(QString("org_id=%1").arg(id));
    ui->comboBox_2->setModelColumn(3);
    modelrep->select();
}

void Card::initUser()
{
    modeluser=new QSqlTableModel;
    modeluser->setTable("users");
    ui->comboBox_6->setModel(modeluser);
    ui->comboBox_6->setModelColumn(4);
    ui->comboBox_5->setModel(modeluser);
    ui->comboBox_5->setModelColumn(4);
    modeluser->select();
}

void Card::initCase()
{
    modelcase=new QSqlTableModel;
    modelcase->setTable("cases");
    ui->comboBox_3->setModel(modelcase);
    ui->comboBox_3->setModelColumn(1);
    modelcase->select();
}

void Card::initUnits()
{
    modelunits=new QSqlTableModel;
    modelunits->setTable("units");
    ui->comboBox_4->setModel(modelunits);
    ui->comboBox_4->setModelColumn(2);
    modelunits->select();
}

void Card::on_toolButton_clicked()
{
    DirOrg *org=new DirOrg(this);
    if(org->exec()==QDialog::Accepted)
    {
        qDebug()<<"new organization";
    }
}

void Card::on_toolButton_2_clicked()
{
    Repres *newrep=new Repres(this);
    if(newrep->exec()==QDialog::Accepted)
    {
        qDebug()<<"new representtation";
    }
}

void Card::on_toolButton_3_clicked()
{
    Users *user=new Users(this);
    if(user->exec()==QDialog::Accepted)
    {
        qDebug()<<"new user";
    }
}

void Card::on_toolButton_4_clicked()
{
    bool ok;
    QString newcase=QInputDialog::getText(this,trUtf8("Новая должность"),trUtf8("Должность"),QLineEdit::Normal,"",&ok);
    if(ok&&!newcase.isEmpty())
    {
        qDebug()<<newcase;
    }
}

void Card::on_toolButton_6_clicked()
{
    Units *unit=new Units(this);
    if(unit->exec()==QDialog::Accepted)
    {
        qDebug()<<"new unit";
    }
}

void Card::on_toolButton_7_clicked()
{
    Users *user=new Users(this);
    if(user->exec()==QDialog::Accepted)
    {
        qDebug()<<"new user";
    }
}

void Card::on_toolButton_5_clicked()
{
    bool ok;
    QStringList items;
    QSqlQuery query;
    query.exec("select lname from users;");
    while(query.next())
    {
        items<<query.value(0).toString();
    }
    QString item=QInputDialog::getItem(this,trUtf8("Выбор исполнителя"),trUtf8("Исполнитель"),items,0,false,&ok);
    if(ok&&!item.isEmpty())
    {
        qDebug()<<item;
    }
}


void Card::on_comboBox_currentIndexChanged(int index)
{
    qDebug()<<index;
    initRep();
}

void Card::on_buttonBox_accepted()
{
    QString id;
    QModelIndex index=ui->comboBox->model()->index(ui->comboBox->currentIndex(),0);
    org=ui->comboBox->model()->data(index).toString();
    index=ui->comboBox_2->model()->index(ui->comboBox_2->currentIndex(),0);
    repres=ui->comboBox_2->model()->data(index).toString();
    num_disp=ui->lineEdit->text();
    date_disp=ui->dateEdit_2->text();
    num_reg=ui->lineEdit_3->text();
    date_reg=ui->dateEdit->text();
    index=ui->comboBox_6->model()->index(ui->comboBox_6->currentIndex(),0);
    user=ui->comboBox_6->model()->data(index).toString();
    topic=ui->textEdit->toPlainText();
    name=ui->lineEdit_5->text();
    qDebug()<<repres<<" "<<num_disp<<" "<<date_disp<<" "<<num_reg<<" "
            <<date_reg<<" "<<user<<" "<<topic<<" "<<name;
}

void Card::initCard()
{
    //ui->comboBox->model()
}
