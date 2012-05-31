#ifndef DIRORG_H
#define DIRORG_H

#include <QDialog>
#include <QTextDocument>
#include <QDebug>
#include <QtSql>

namespace Ui {
    class DirOrg;
}

class DirOrg : public QDialog
{
    Q_OBJECT

public:
    explicit DirOrg(QWidget *parent = 0);
    ~DirOrg();
    QString name,fullname,address;
    //QTextDocument *doc;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DirOrg *ui;
};

#endif // DIRORG_H
