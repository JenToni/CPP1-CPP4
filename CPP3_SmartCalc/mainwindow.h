#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "View/graph.h"
#include "View/credit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Graph *graph;
    Credit *credit;

private slots:
    void digits_numbers();
    void operations();
    void functions();
    void on_pushButton_dot_clicked();
    void on_pushButton_AC_clicked();
    void on_pushButton_AC_2_clicked();
    void on_pushButton_eq_clicked();
    void keyPressEvent(QKeyEvent *event);
    void on_graphic_clicked();

    void on_credit_clicked();

private:
   Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
