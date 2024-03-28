#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QVector>

namespace Ui {
class Graph;
}

class Graph : public QWidget
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Graph *ui;
    double xBegin, xEnd,h ,X;
    int N;
    QVector<double> x,y;

};

#endif // GRAPH_H
