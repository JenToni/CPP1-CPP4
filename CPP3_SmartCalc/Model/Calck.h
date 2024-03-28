#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include <stack>
#include <string>

enum { ERROR, OK };

typedef enum {
  number_x = 0,
  add_sub = 1,  // -+
  mod = 2,      // Mod * /
  POW = 3,      // ^
  trig = 4,     // type 8-16
} priority;

typedef enum {
  und = -1,
  number = 0,    // '0-9'
  x,             // 'X'
  Add,           // '+'
  Sub,           // '-'
  Div,           // '/'
  Mul = 5,       // '*'
  Mod,           // 'Mod'
  Pow,           // '^'
  Sin,           // sin(x)
  Cos,           // cos(x)
  Tan = 10,      // tan(x)
  Acos,          // acos(x)
  Asin,          // asin(x)
  Atan,          // atan(x)
  Sqrt,          // sqrt(x)
  Ln = 15,       // ln(x)
  Log,           // log(x)
  OpenBracket,   // '('
  CloseBracket,  // ')'
} type;

namespace s21 {

typedef struct Node {
  double value;
  int type;
  int priority;
} Node;

class Calck {
 public:
  Calck() {}
  ~Calck() {}
  double main_calculation(std::string &str, double x);
  bool main_validator(std::string &str);
  void main_credit_an(double &summ, int &month, double &percent,
                      double &month_pay, double &total, double &over_pay,
                      double &sum);
  void main_credit_dif(double &summ, int &month, double &percent, double &total,
                       double &month_pay, double &remainder, double &p_debt,
                       double &main_debt, int &i);

 private:
  std::stack<Node> Node_;

  // main_calculation
  std::stack<Node> parser(std::string str, double x);
  std::stack<Node> revnotation(std::stack<Node> Node);
  double calculate(std::stack<Node> Node);

  // main_validator
  int check_symbol(std::string &str);
  int modd(std::string &str, int *i);
  int search_in_trig(std::string &str, int *i, int *result);

  bool main_examination(std::string &str, int &i, bool &result, bool trig);
  bool search_trig(std::string &str, int &i);

  bool is_operator(char a);
  bool is_trig(char a);

  // after the ...
  bool after_the_number(char a);
  bool after_the_operator(char a);
  bool after_the_open_bracket(char a);
  bool after_the_degree(char a);
  bool after_the_mod(char a);
  void replace_Exp(std::string &str, std::string Exp, std::string Math);

};  // Calck

}  // namespace s21

#endif  // SRC_S21_SMARTCALC_H_
