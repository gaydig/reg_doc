#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::connectdb();
    QStandardItemModel *treeModel = new QStandardItemModel();
    QStandardItem *parentItem = treeModel->invisibleRootItem();
    fillTree(0, parentItem);
    ui->treeView->setModel(treeModel);
    maintablemodel= new QSqlRelationalTableModel(0);
    MainWindow::initmaintable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    Card *ndoc=new Card(this);
    if(ndoc->exec()==QDialog::Accepted)
    {
        qDebug()<<"New document";
    }
}

void MainWindow::connectdb()
{
    mydb=QSqlDatabase::addDatabase("QSQLITE");
   // mydb.setHostName("localhost");
    mydb.setDatabaseName("osp.db");
    //mydb.setUserName("root");
    //mydb.setPassword("");
    //bool ok=mydb.open();
    if(!mydb.open())
    {
        qDebug() << "Error connecting"<<mydb.lastError().text();
    } else {
        qDebug() << "Connected";
    }
}

void MainWindow::on_action_2_triggered()
{
    Enchiridion *spr=new Enchiridion(this);
    spr->exec();
}

void MainWindow::fillTree(int parentId, QStandardItem *parentItem)
{
    QSqlQuery query;
    QStringList parentList;
    query.prepare("SELECT * FROM vid_doc WHERE parent_id = :parent");
    query.bindValue(0,parentId);
    if(!query.exec()) qDebug()<<"Error query\n "<<query.lastError().text();
    while(query.next())
    {
        parentList.append(query.value(0).toString()+"~~"+query.value(1).toString());
    }
    if (parentList.size()>0)
    for (int i=0;i<parentList.size();++i)
    {
    QStringList parsedList;
    parsedList = parentList.at(i).split("~~");
    QStandardItem *childItem = new QStandardItem(parsedList.at(1));
    parentItem->appendRow(childItem);
    fillTree(parsedList.at(0).toInt(), childItem);
    }
}


void MainWindow::initmaintable()
{
    maintablemodel->clear();
    maintablemodel->setTable("doc");
    maintablemodel->setRelation(1,QSqlRelation("cases","id","name"));
    maintablemodel->setRelation(9,QSqlRelation("users","id","lname"));
    maintablemodel->setRelation(7,QSqlRelation("dir_org","id","name"));
    //maintablemodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    maintablemodel->setHeaderData(1,Qt::Horizontal,QObject::trUtf8("№ дела"));
    maintablemodel->setHeaderData(4,Qt::Horizontal,QObject::trUtf8("Номер отправки"));
    maintablemodel->setHeaderData(6,Qt::Horizontal,QObject::trUtf8("Номер регистрации"));
    maintablemodel->setHeaderData(7,Qt::Horizontal,QObject::trUtf8("Организация"));
    maintablemodel->setHeaderData(9,Qt::Horizontal,QObject::trUtf8("Фамилия"));
    maintablemodel->setHeaderData(11,Qt::Horizontal,QObject::trUtf8("Дата отправки"));
    maintablemodel->setHeaderData(12,Qt::Horizontal,QObject::trUtf8("Дата регистрации"));
    maintablemodel->setHeaderData(13,Qt::Horizontal,QObject::trUtf8("Наименование"));
    maintablemodel->setHeaderData(14,Qt::Horizontal,QObject::trUtf8("Комментарии"));
    ui->tableView->setModel(maintablemodel);
    //ui->tableView->horizontalHeader()->swapSections(1,5);
    //ui->tableView->horizontalHeader()->swapSections(0,1);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(2);
    ui->tableView->hideColumn(3);
    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(8);
    ui->tableView->hideColumn(10);
    ui->tableView->resizeColumnsToContents();
    //ui->tableView->resizeColumnToContents(7);
    //ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    maintablemodel->select();
}

void MainWindow::on_treeView_clicked(QModelIndex index)
{
    QSqlQuery query;
    int id;
    QString name=index.data(Qt::DisplayRole).toString();
    query.prepare("SELECT id FROM vid_doc WHERE name=:name;");
    query.bindValue(0,name);
    qDebug()<<"Clicked"<<name;
    if(!query.exec()) qDebug()<<"Error query\n "<<query.lastError().text();
    while(query.next())
    {
        id=query.value(0).toInt();
        qDebug()<<id;
    }
    maintablemodel->setFilter(QString("vid_doc_id=%1").arg(id));
    maintablemodel->select();
    qDebug()<<id;
}

void MainWindow::on_tableView_doubleClicked(QModelIndex index)
{
    QString name=ui->tableView->model()->data(index).toString();
    qDebug()<<name;
    QSqlQuery query;
    int id;
    query.prepare("SELECT doc.id FROM doc,cases WHERE doc.case_id=cases.id and cases.name=:name;");
    query.bindValue(0,name);
    if(!query.exec()) qDebug()<<"Error query\n "<<query.lastError().text();
    while(query.next())
    {
        id=query.value(0).toInt();
    }
    if(id)
    {
        Card *ndoc=new Card(this);
        qDebug()<<id;
        if(ndoc->exec()==QDialog::Accepted)
        {
            qDebug()<<"New document";
            query.prepare("SELECT name FROM doc WHERE id=:id;");
            query.bindValue(0,id);
            if(!query.exec()) qDebug()<<"Error query\n "<<query.lastError().text();
        }
    }
}
