#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/Calck.h"
namespace s21 {
class Controller {
 public:
  Controller() {}
  ~Controller() {}

  double calculation(std::string &str, double x);
  bool validator(std::string &str);

  void credit_an(double &summ,int &month, double &percent,double &month_pay,double &total,double &over_pay,double &sum);
  void credit_dif(double &summ,int &month, double &percent ,double &total , double &month_pay,double &remainder,double &p_debt, double & main_debt, int &i );

 private:
  s21::Calck *Calck_;
};  // Controller

}  // namespace s21
#endif  // CONTROLLER_H
