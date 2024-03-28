#include "Controller.h"

double s21::Controller::calculation(std::string &str, double x) {
    return this->Calck_->main_calculation(str, x);
}
bool s21::Controller::validator(std::string &str) {
    return this->Calck_->main_validator(str);
}

void s21::Controller::credit_an(double &summ,int &month, double &percent,double &month_pay,double &total,double &over_pay,double &sum){
    this->Calck_->main_credit_an(summ,month, percent,month_pay,total,over_pay,sum);
}
void s21::Controller::credit_dif(double &summ,int &month, double &percent ,double &total , double &month_pay,double &remainder,double &p_debt, double & main_debt, int &i ){

    this->Calck_->main_credit_dif(summ,month,percent ,total ,month_pay,remainder,p_debt,main_debt,i);

}
