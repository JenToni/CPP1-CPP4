#include "credit.h"
#include "ui_credit.h"
#include "../Controller/Controller.h"
Credit::Credit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Credit)
{
    ui->setupUi(this);

}

Credit::~Credit()
{
    delete ui;
}

void Credit::on_calc_clicked()
{
    s21::Controller S21_credit;
    bool ok;
    // если передали не дабл то значение = 0
    double summ = QString(ui->summ->text()).toDouble(&ok);
    int month = QString(ui->month->text()).toInt(&ok);
    double percent = QString(ui->percent->text()).toDouble(&ok);
    ui->tableWidget->setRowCount(month);
    percent /=1200;
    if (ui->ann->isChecked()){
        double month_pay,total,over_pay,sum;
        S21_credit.credit_an(summ,month,percent,month_pay,total,over_pay,sum);
        ui->overpayment->setText(QString::number(over_pay, 'f',2));
        ui->total->setText(QString::number(total,'f',2));
        for (int i = 0; i < month; i++)
        {

            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(month_pay, 'f',2)));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(sum * percent, 'f',2)));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(month_pay - sum * percent , 'f',2)));
            sum -= (month_pay - (sum * percent));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(sum, 'f',2)));
        }

    }
    if (ui->dif->isChecked()){
        double total = 0 , month_pay = 0,remainder,p_debt, main_debt = summ / month;
        for (int i = 0; i < month; i++)
        {
            S21_credit.credit_dif(summ,month,percent ,total ,month_pay,remainder,p_debt,main_debt,i);
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(month_pay, 'f',2)));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(p_debt, 'f',2)));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(remainder - main_debt, 'f',2)));
        }
        ui->overpayment->setText(QString::number(total - summ, 'f',2));
        ui->total->setText(QString::number(total,'f',2));
    }

}


void Credit::on_clear_clicked()
{
    ui->tableWidget->clear();
    ui->overpayment->clear();
    ui->total->clear();
    ui->summ->clear();
    ui->month->clear();
    ui->percent->clear();
}
