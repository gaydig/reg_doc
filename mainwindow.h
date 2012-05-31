#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "card.h"
#include <QDebug>
#include <QtSql>
#include "enchiridion.h"
#include <QStandardItem>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connectdb();
    QSqlDatabase mydb;
    void fillTree(int parentId,QStandardItem *parentItem);
    QSqlRelationalTableModel *maintablemodel;
    void initmaintable();

private slots:
    void on_action_triggered();

    void on_action_2_triggered();

    void on_treeView_clicked(QModelIndex index);
    void on_tableView_doubleClicked(QModelIndex index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
