#include "vdoc.h"
#include "ui_vdoc.h"

VDoc::VDoc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VDoc)
{
    ui->setupUi(this);
    VDoc::DocInit();
}

VDoc::~VDoc()
{
    delete ui;
}

void VDoc::DocInit()
{
    modelvdoc=new QSqlTableModel;
    modelvdoc->setTable("vid_doc");
    ui->comboBox->setModel(modelvdoc);
    ui->comboBox->setModelColumn(1);
    modelvdoc->select();
}

void VDoc::on_buttonBox_accepted()
{
    name=ui->lineEdit->text();
    QString iddoc;
    QModelIndex indexdoc=ui->comboBox->model()->index(ui->comboBox->currentIndex(),0);
    iddoc=ui->comboBox->model()->data(indexdoc).toString();
    QSqlQuery query;
    query.prepare("insert into vid_doc (name,parent_id)"
                  "values(?,?)");
    query.bindValue(0,name);
    query.bindValue(1,iddoc);
    if(!query.exec())
    {
        qDebug()<<query.lastError().text();
    }
    VDoc::DocInit();
}
