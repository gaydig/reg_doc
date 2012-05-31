#include "enchiridion.h"
#include "ui_enchiridion.h"

Enchiridion::Enchiridion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Enchiridion)
{
    ui->setupUi(this);
    Enchiridion::initUnits();
    Enchiridion::initPost();
    Enchiridion::initUser();
    Enchiridion::initOrg();
    Enchiridion::initRep();
    Enchiridion::initCase();
    Enchiridion::initVdoc();

}

Enchiridion::~Enchiridion()
{
    delete ui;
}

void Enchiridion::initUnits()
{
  unitmodel=new QSqlTableModel;
  unitmodel->setTable("units");
  unitmodel->setHeaderData(1,Qt::Horizontal,QObject::trUtf8("Наименование"));
  unitmodel->setHeaderData(2,Qt::Horizontal,QObject::trUtf8("Номер"));
  unitmodel->select();
  unitmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
  ui->tableView->setModel(unitmodel);
  ui->tableView->setColumnHidden(0,true);
  ui->tableView->resizeColumnsToContents();
}

void Enchiridion::initPost()
{
    postmodel=new QSqlTableModel;
    postmodel->setTable("post");
    postmodel->setHeaderData(1,Qt::Horizontal,QObject::trUtf8("Должность"));
    postmodel->select();
    postmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_2->setModel(postmodel);
    ui->tableView_2->setColumnHidden(0,true);
    ui->tableView_2->resizeColumnsToContents();
}

void Enchiridion::initUser()
{
    usermodel=new QSqlRelationalTableModel;
    usermodel->setTable("users");
    usermodel->setRelation(1,QSqlRelation("post","id","name"));
    usermodel->setRelation(2,QSqlRelation("units","id","number"));
    usermodel->setHeaderData(1,Qt::Horizontal,QObject::trUtf8("Должность"));
    usermodel->setHeaderData(2,Qt::Horizontal,QObject::trUtf8("Отдел"));
    usermodel->setHeaderData(3,Qt::Horizontal,QObject::trUtf8("Имя"));
    usermodel->setHeaderData(4,Qt::Horizontal,QObject::trUtf8("Фамилия"));
    usermodel->setHeaderData(5,Qt::Horizontal,QObject::trUtf8("Отчество"));
    usermodel->select();
    usermodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_3->setModel(usermodel);
    ui->tableView_3->setColumnHidden(0,true);
    ui->tableView_3->resizeColumnsToContents();
    ui->tableView_3->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_3));
}

void Enchiridion::initOrg()
{
    orgmodel=new QSqlTableModel;
    orgmodel->setTable("dir_org");
    orgmodel->setHeaderData(1,Qt::Horizontal,QObject::trUtf8("Адрес"));
    orgmodel->setHeaderData(2,Qt::Horizontal,QObject::trUtf8("Полное наименование"));
    orgmodel->setHeaderData(3,Qt::Horizontal,QObject::trUtf8("Наименование"));
    orgmodel->select();
    orgmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_4->setModel(orgmodel);
    ui->tableView_4->setColumnHidden(0,true);
    ui->tableView_4->resizeColumnsToContents();
}

void Enchiridion::initRep()
{
    repmodel=new QSqlRelationalTableModel;
    //repmodel->setQuery("select rep.id,rep.name,rep.post,rep.phone,org.name from repres rep,dir_org org where rep.org_id=org.id;");
    repmodel->setTable("repres");
    repmodel->setRelation(1,QSqlRelation("dir_org","id","name"));
    repmodel->setHeaderData(1,Qt::Horizontal,QObject::trUtf8("Организация"));
    repmodel->setHeaderData(2,Qt::Horizontal,QObject::trUtf8("Адрес эл.почты"));
    repmodel->setHeaderData(3,Qt::Horizontal,QObject::trUtf8("ФИО"));
    repmodel->setHeaderData(4,Qt::Horizontal,QObject::trUtf8("Телефон"));
    repmodel->setHeaderData(5,Qt::Horizontal,QObject::trUtf8("Должность"));
    repmodel->select();
    repmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_5->setModel(repmodel);
    ui->tableView_5->setColumnHidden(0,true);
    ui->tableView_5->resizeColumnsToContents();
    ui->tableView_5->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_5));
}

void Enchiridion::initCase()
{
    casemodel=new QSqlTableModel;
    //casemodel->setQuery("select id,name from case;");
    casemodel->setTable("cases");
    casemodel->setHeaderData(1,Qt::Horizontal,QObject::trUtf8("Наименование"));
    casemodel->select();
    casemodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_6->setModel(casemodel);
    ui->tableView_6->setColumnHidden(0,true);
    ui->tableView_6->resizeColumnsToContents();
}

void Enchiridion::initVdoc()
{
    vdocmodel=new QSqlTableModel;
    //vdocmodel->setQuery("select id,name from vid_doc;");
    vdocmodel->setTable("vid_doc");
    vdocmodel->setHeaderData(1,Qt::Horizontal,QObject::trUtf8("Вид документа"));
    vdocmodel->select();
    vdocmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_7->setModel(vdocmodel);
    ui->tableView_7->setColumnHidden(0,true);
    ui->tableView_7->setColumnHidden(2,true);
    ui->tableView_7->resizeColumnsToContents();

}

void Enchiridion::on_pushButton_2_clicked()
{
    Units *unit=new Units(this);
    if(unit->exec()==QDialog::Accepted&&!unit->name.isEmpty())
    {
        unitmodel->submit();
    }
}

void Enchiridion::on_pushButton_clicked()
{
         QModelIndex index;
         index=ui->tableView->currentIndex();
         //qDebug()<<index;
         ui->tableView->model()->removeRow(index.row());
         ui->tableView->model()->submit();
}

void Enchiridion::on_pushButton_4_clicked()
{
    QSqlRecord record;
    int row;
    bool ok;
    QString newpost=QInputDialog::getText(this,trUtf8("Новая должность"),trUtf8("Должность"),QLineEdit::Normal,"",&ok);
    if(ok&&!newpost.isEmpty())
    {
        qDebug()<<newpost;
        record=postmodel->record();
        record.setValue("name",newpost);
        row=postmodel->rowCount();
        postmodel->insertRow(row);
        ok=postmodel->setRecord(row,record);
        postmodel->submit();
    }
}

void Enchiridion::on_pushButton_3_clicked()
{
    QModelIndex index;
    index=ui->tableView_2->currentIndex();
    //qDebug()<<index;
    ui->tableView_2->model()->removeRow(index.row());
    ui->tableView_2->model()->submit();
}

void Enchiridion::on_pushButton_6_clicked()
{
    Users *user=new Users(this);
    if(user->exec()==QDialog::Accepted)
    {
        usermodel->select();
    }
}

void Enchiridion::on_pushButton_5_clicked()
{
    QModelIndex index;
    index=ui->tableView_3->currentIndex();
    ui->tableView_3->model()->removeRow(index.row());
    ui->tableView_3->model()->submit();
}

void Enchiridion::on_pushButton_8_clicked()
{
    DirOrg *orgform=new DirOrg(this);
    if(orgform->exec()==QDialog::Accepted)
    {
        //qDebug()<<"new";
        //ui->tableView_4->model()->submit();
        orgmodel->select();
    }
}

void Enchiridion::on_pushButton_7_clicked()
{
    QModelIndex index;
    index=ui->tableView_4->currentIndex();
    ui->tableView_4->model()->removeRow(index.row());
    ui->tableView_4->model()->submit();
}

void Enchiridion::on_pushButton_10_clicked()
{
    Repres *rep=new Repres(this);
    if(rep->exec()==QDialog::Accepted)
    {
        repmodel->submit();
    }
}

void Enchiridion::on_pushButton_9_clicked()
{
    QModelIndex index;
    index=ui->tableView_5->currentIndex();
    ui->tableView_5->model()->removeRow(index.row());
    ui->tableView_5->model()->submit();
}

void Enchiridion::on_pushButton_11_clicked()
{
    QModelIndex index;
    index=ui->tableView_6->currentIndex();
    ui->tableView_6->model()->removeRow(index.row());
    ui->tableView_6->model()->submit();
}

void Enchiridion::on_pushButton_12_clicked()
{
    QSqlRecord record;
    int row;
    bool ok;
    QString newcase=QInputDialog::getText(this,trUtf8("Новое дело"),trUtf8("Дело"),QLineEdit::Normal,"",&ok);
    if(ok&&!newcase.isEmpty())
    {
        qDebug()<<newcase;
        record=casemodel->record();
        record.setValue("name",newcase);
        row=casemodel->rowCount();
        casemodel->insertRow(row);
        ok=casemodel->setRecord(row,record);
        casemodel->submit();
    }
}

void Enchiridion::on_pushButton_13_clicked()
{
    QModelIndex index;
    index=ui->tableView_7->currentIndex();
    ui->tableView_7->model()->removeRow(index.row());
    ui->tableView_7->model()->submit();
}

void Enchiridion::on_pushButton_14_clicked()
{
    VDoc *vid_doc=new VDoc(this);
    if(vid_doc->exec()==QDialog::Accepted)
    {
        vdocmodel->select();
    }
}

void Enchiridion::on_buttonBox_accepted()
{
    unitmodel->submitAll();
    postmodel->submitAll();
    usermodel->submitAll();
    orgmodel->submitAll();
    repmodel->submitAll();
    casemodel->submitAll();
    vdocmodel->submitAll();
}
