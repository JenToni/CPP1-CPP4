#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>

namespace Ui {
class Credit;
}

class Credit : public QWidget
{
    Q_OBJECT

public:
    explicit Credit(QWidget *parent = nullptr);
    ~Credit();

public slots:
    void on_calc_clicked();
    void on_clear_clicked();

private:
    Ui::Credit *ui;

};

#endif // CREDIT_H
