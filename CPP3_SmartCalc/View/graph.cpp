#include "graph.h"
#include "ui_graph.h"
#include <QMessageBox>
#include "../Controller/Controller.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph)
{
    setFixedSize(602,400);
    ui->setupUi(this);
    ui->X_min->setText("-100");
    ui->X_max->setText("100");
    ui->X_range->setText("100");
    ui->Y_range->setText("100");
}

Graph::~Graph()
{
    delete ui;
}

void Graph::on_pushButton_clicked()
{
    ui->widget->clearGraphs();

    bool ok;

    double x_min = QString(ui->X_min->text()).toDouble(&ok);
    double x_max = QString(ui->X_max->text()).toDouble(&ok);
    double x_range = QString(ui->X_range->text()).toDouble(&ok);
    double y_range = QString(ui->Y_range->text()).toDouble(&ok);

    if (x_range > 1000000) x_range = 1000000;
    if (y_range > 1000000) y_range = 1000000;
    if (x_min < -1000000) x_min = -1000000;
    if (x_max > 1000000) x_max = 1000000;

     std::string str = ui->Form->text().toStdString();
     s21::Controller S21_calk;

    if(str.empty()){

        ui->Form->setText("");

    } else if (ui->Form->text().toDouble()){}
    else if (x_max > x_min && S21_calk.validator(str) == OK){

         ui->widget->xAxis->setRange(-1 * x_range, x_range);
         ui->widget->yAxis->setRange(-1 * y_range, y_range);

         if (ui->point->isChecked())
             h = 0.01;
         else
             h = 0.1;

         xBegin = x_min;
         xEnd = x_max;
         if (ui->Form->text() == 'x'){
             for (X = xBegin; X < xEnd; X += h) {
                 x.push_back(X);
                 y.push_back(X);
             }
         }else
         {
         for (X = xBegin; X < xEnd; X += h) {
             x.push_back(X);
             y.push_back(S21_calk.calculation(str, X));
         }
         }

         ui->widget->addGraph();
         ui->widget->graph(0)->addData(x, y);

         if (ui->point->isChecked()) {
             ui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));
             ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
             ui->widget->graph(0)->setScatterStyle(
                 QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
         }

         // зум и сдвиг
         ui->widget->setInteraction(QCP::iRangeZoom, true);
         ui->widget->setInteraction(QCP::iRangeDrag, true);

         ui->widget->replot();

         x.clear();
         y.clear();


     }else
         ui->Form->setText("Invalid Input");

}

