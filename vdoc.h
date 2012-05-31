#ifndef VDOC_H
#define VDOC_H

#include <QDialog>
#include <QtSql>

namespace Ui {
    class VDoc;
}

class VDoc : public QDialog
{
    Q_OBJECT

public:
    explicit VDoc(QWidget *parent = 0);
    ~VDoc();
    QSqlTableModel *modelvdoc;
    void DocInit();
    QString name;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::VDoc *ui;
};

#endif // VDOC_H
