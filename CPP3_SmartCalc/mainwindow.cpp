#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QString>
#include "Controller/Controller.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(421,392);
    graph = new Graph;
    credit = new Credit;
    ui->setupUi(this);
    ui->lineEdit_eq->clear();
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_e,SIGNAL(clicked()),this, SLOT(operations()));
    connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_Open, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_Clouse, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(operations()));

    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    if (ui->lineEdit_eq->text().contains("Invalid Input"))
        ui->lineEdit_eq->setText("");
    QPushButton *button = (QPushButton *)sender();
    QString new_result = ui->lineEdit_eq->text() + button->text();
    ui->lineEdit_eq->setText(new_result);

}

void MainWindow::on_pushButton_dot_clicked() {
    if (ui->lineEdit_eq->text().contains("Invalid Input"))
        ui->lineEdit_eq->setText("");
    ui->lineEdit_eq->setText(ui->lineEdit_eq->text() + ".");
}

void MainWindow::operations() {
    if (ui->lineEdit_eq->text().contains("Invalid Input"))
        ui->lineEdit_eq->setText("");

    QPushButton *button = (QPushButton *)sender();
    QString new_result;
    new_result = ui->lineEdit_eq->text();

    if (button->text() == "÷" && !(ui->lineEdit_eq->text().endsWith("÷")) &&
                                 !(ui->lineEdit_eq->text().endsWith("/"))) {
        new_result += '/';
    } else if (button->text() == '*' &&
               !(ui->lineEdit_eq->text().endsWith('*'))) {
        new_result += "*";
    } else if (button->text() == '*' &&
               !(ui->lineEdit_eq->text().endsWith('*'))) {
        new_result += '*';
    } else if (button->text() == '+' &&
               !(ui->lineEdit_eq->text().endsWith('+'))) {
        new_result += '+';
    } else if (button->text() == '-' &&
               !(ui->lineEdit_eq->text().endsWith('-'))) {
        new_result += '-';
    } else if (button->text() == "pow" &&
               !(ui->lineEdit_eq->text().endsWith("pow"))) {
        new_result += '^';
    } else if (button->text() == "sqrt" &&
               !(ui->lineEdit_eq->text().endsWith("sqrt"))) {
        new_result += "sqrt(";
    } else if (button->text() == "mod" &&
               !(ui->lineEdit_eq->text().endsWith("mod"))) {
        new_result += "mod";
    } else if (button->text() == '(') {
        new_result += '(';
    } else if (button->text() == ')') {
        new_result += ')';
    } else if (button->text() == 'x' &&
               !(ui->lineEdit_eq->text().endsWith('x'))) {
        new_result += 'x';
    }else if (button->text() == 'e'){new_result += 'e';}
    ui->lineEdit_eq->setText(new_result);
}

void MainWindow::functions() {
    if (ui->lineEdit_eq->text().contains("Invalid Input"))
        ui->lineEdit_eq->setText("");
    QPushButton *button = (QPushButton *)sender();
    QString new_result;
    new_result = ui->lineEdit_eq->text() + button->text() + "(";
    ui->lineEdit_eq->setText(new_result);
}

void MainWindow::on_pushButton_AC_clicked() { ui->lineEdit_eq->setText(""); }

void MainWindow::on_pushButton_AC_2_clicked() {
    ui->lineEdit_eq->setText(
        ui->lineEdit_eq->text().left(ui->lineEdit_eq->text().size() - 1));
}


void MainWindow::on_pushButton_eq_clicked()

{
    std::string str = ui->lineEdit_eq->text().toStdString();
    s21::Controller S21_calk;
    double check = 0;
    if (S21_calk.validator(str) == ERROR ) {
        ui->lineEdit_eq->setText("Invalid Input");
    }else if(str.empty())
    {
        ui->lineEdit_eq->setText("");

    }
    else if (ui->lineEdit_eq->text().toDouble()){}
    else if(ui->lineEdit_eq->text() == 'x'){
        ui->lineEdit_eq->setText(ui->lineEdit->text());
    }
    else if (ui->lineEdit_eq->text().contains("x"))
    {
        double x = (ui->lineEdit->text()).toDouble();
        double answer = S21_calk.calculation(str, x);
        QString numberAnswer = QString::number(answer,'g',15);
        ui->lineEdit_eq->setText(numberAnswer);

    }else {
        double answer = S21_calk.calculation(str, 0);
        QString numberAnswer = QString::number(answer,'g',15);
        ui->lineEdit_eq->setText(numberAnswer);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter) {
        on_pushButton_eq_clicked();
    }
}



void MainWindow::on_graphic_clicked()
{
    graph->show();
}


void MainWindow::on_credit_clicked()
{
    credit->show();
}

