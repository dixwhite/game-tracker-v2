#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tableView_clicked(const QModelIndex &index);
    void on_viewButton_clicked();
    void on_addButton_clicked();
    void on_allButton_clicked();

    void on_finishedButton_clicked();

    void on_unfinishedButton_clicked();

    void on_retiredButton_clicked();

    void on_editButton_clicked();

private:
    Ui::MainWindow *ui;
    QString currentName;
};

#endif // MAINWINDOW_H
