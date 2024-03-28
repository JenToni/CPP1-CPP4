#include "Calck.h"

#include <algorithm>
#include <cmath>
#include <sstream>


double s21::Calck::main_calculation(std::string &str, double x) {
  return double(calculate(revnotation(parser(str, x))));
}

void s21::Calck::main_credit_an(double &summ,int &month, double &percent,double &month_pay,double &total,double &over_pay,double &sum){

  month_pay = (summ * percent)/(1 - powf(1 + percent,-month));
  total = month_pay * month;
  over_pay = total - summ;
  sum = summ;

}

void s21::Calck::main_credit_dif(double &summ,int &month, double &percent ,double &total , double &month_pay,double &remainder,double &p_debt, double & main_debt, int &i ){
  remainder = summ-(main_debt * i);
  p_debt = remainder * percent;
  month_pay = p_debt + main_debt;
  total += month_pay;
}

double s21::Calck::calculate(std::stack<s21::Node> Node) {
  std::stack<s21::Node> buff;
    double number = 0;
  if (Node.size() == 1) return Node.top().value;
  while (!Node.empty()) {
     number = 0;
    while (Node.top().priority == number) {
      buff.push(Node.top());
      Node.pop();
    }
    number = buff.top().value;
    if (buff.size() >= 2 && Node.top().type <= Pow) {
      buff.pop();
    }
    if (Node.top().type == Add) {
      buff.top().value += number;
      Node.pop();
      continue;
    }
    if (Node.top().type == Sub) {
      buff.top().value -= number;
      Node.pop();
      continue;
    }
    if (Node.top().type == Div) {
      buff.top().value /= number;
      Node.pop();
      continue;
    }
    if (Node.top().type == Mul) {
      buff.top().value *= number;
      Node.pop();
      continue;
    }
    if (Node.top().type == Mod) {
      buff.top().value = fmod(buff.top().value, number);
      Node.pop();
      continue;
    }
    if (Node.top().type == Pow) {
      buff.top().value = powf(buff.top().value, number);
      Node.pop();
      continue;
    }
    if (Node.top().type == Sin) {
      buff.top().value = sin(buff.top().value);
      Node.pop();
      continue;
    }
    if (Node.top().type == Cos) {
      buff.top().value = cos(buff.top().value);
      Node.pop();
      continue;
    }
    if (Node.top().type == Tan) {
      buff.top().value = tan(buff.top().value);
      Node.pop();
      continue;
    }
    if (Node.top().type == Acos) {
      buff.top().value = acos(buff.top().value);
      Node.pop();
      continue;
    }
    if (Node.top().type == Asin) {
      buff.top().value = asin(buff.top().value);
      Node.pop();
      continue;
    }
    if (Node.top().type == Atan) {
      buff.top().value = atan(buff.top().value);
      Node.pop();
      continue;
    }
    if (Node.top().type == Sqrt) {
      buff.top().value = sqrt(buff.top().value);
      Node.pop();
      continue;
    }
    if (Node.top().type == Ln) {
      buff.top().value = log(buff.top().value);
      Node.pop();
      continue;
    }
    if (Node.top().type == Log) {
      buff.top().value = log10(buff.top().value);
      Node.pop();
      continue;
    }
  }
  return buff.top().value;
}

std::stack<s21::Node> s21::Calck::parser(std::string str, double x) {
  std::stack<s21::Node> pars_Node;
  double value = 0;
  int len = str.length();
  for (int i = 0, p = 0; i < len; i++) {
    if (isdigit(str[i]) ) {
      value = std::stod(&str[i]);
      pars_Node.push({value, number, number_x});
      std::ostringstream stream;
      stream << value;
      std::string value_str = stream.str();
      i += value_str.length() - 1;
      if (isdigit(str[i+1])) return pars_Node;
    } else if (str[i] == 'x') {
      pars_Node.push({x, number, number_x});
    } else if (str[i] == '(') {
      pars_Node.push({0, OpenBracket, und});
    } else if (str[i] == ')') {
      pars_Node.push({0, CloseBracket, und});
    } else if (str[i] == '+') {
      if (pars_Node.top().type == OpenBracket || pars_Node.top().type == und) {
        pars_Node.push({0, number, number_x});
        pars_Node.push({0, Add, add_sub});
      } else
        pars_Node.push({0, Add, add_sub});
    } else if (str[i] == '-') {
      if (pars_Node.top().type == OpenBracket || pars_Node.top().type == und) {
        pars_Node.push({0, number, number_x});
        pars_Node.push({0, Sub, add_sub});
      } else
        pars_Node.push({0, Sub, add_sub});
    } else if (str[i] == '*') {
      pars_Node.push({0, Mul, mod});
    } else if (str[i] == '/') {
      pars_Node.push({0, Div, mod});
    } else if (str[i] == '^') {
      pars_Node.push({0, Pow, POW});
    } else if (str.find("cos", i, 3) != std::string::npos) {
      pars_Node.push({0, Cos, trig});
      i += 2;
    } else if (str.find("sin", i, 3) != std::string::npos) {
      pars_Node.push({0, Sin, trig});
      i += 2;
    } else if (str.find("tan", i, 3) != std::string::npos) {
      pars_Node.push({0, Tan, trig});
      i += 2;
    } else if (str.find("asin", i, 4) != std::string::npos) {
      pars_Node.push({0, Asin, trig});
      i += 3;
    } else if (str.find("acos", i, 4) != std::string::npos) {
      pars_Node.push({0, Acos, trig});
      i += 3;
    } else if (str.find("atan", i, 4) != std::string::npos) {
      pars_Node.push({0, Atan, trig});
      i += 3;
    } else if (str.find("sqrt", i, 4) != std::string::npos) {
      pars_Node.push({0, Sqrt, trig});
      i += 3;
    } else if (str.find("ln", i, 2) != std::string::npos) {
      pars_Node.push({0, Ln, trig});
      i += 1;
    } else if (str.find("log", i, 3) != std::string::npos) {
      pars_Node.push({0, Ln, trig});
      i += 2;
    } else if (str.find("mod", i, 3) != std::string::npos) {
      pars_Node.push({0, Mod, mod});
      i += 2;
    }
  }
  std::stack<s21::Node> revers_Node;
  while (!pars_Node.empty()) {
    revers_Node.push(pars_Node.top());
    pars_Node.pop();
  }
  return revers_Node;
}

std::stack<s21::Node> s21::Calck::revnotation(std::stack<Node> Node) {
  std::stack<s21::Node> N_ready;
  std::stack<s21::Node> N_sup;
  while (!Node.empty()) {
    if (Node.top().priority == number_x) {
      N_ready.push(Node.top());
      Node.pop();
      continue;
    }
    if (Node.top().priority != number_x && Node.top().type != OpenBracket &&
        Node.top().type != CloseBracket) {
      if (!N_sup.empty() && Node.top().priority <= N_sup.top().priority &&
          N_sup.top().priority != und) {
        while (!N_sup.empty() && Node.top().priority <= N_sup.top().priority &&
               N_sup.top().priority != und) {
          N_ready.push(N_sup.top());
          N_sup.pop();
        }
        continue;
      } else
        N_sup.push(Node.top());
    }
    if (Node.top().type == OpenBracket) {
      N_sup.push(Node.top());
    }
    if (Node.top().type == CloseBracket) {
      while (N_sup.top().type != OpenBracket) {
        N_ready.push(N_sup.top());
        N_sup.pop();
      }
      N_sup.pop();
    }
    Node.pop();
  }
  while (!N_sup.empty()) {
    N_ready.push(N_sup.top());
    N_sup.pop();
  }
  std::stack<s21::Node> revers_Node;
  while (!N_ready.empty()) {
    revers_Node.push(N_ready.top());
    N_ready.pop();
  }
  return revers_Node;
}

bool s21::Calck::main_validator(std::string &str) {
  int i = 0;
  bool result = OK;
  bool trig = 0;
  auto it = std::remove(str.begin(), str.end(), ' ');
  str.erase(it, str.end());
  if (str.find('e') != str.npos) {
    replace_Exp(str, "e+", "*10^");
    replace_Exp(str, "e-", "/10^");
  }
  if (str.find('E') != str.npos) {
    replace_Exp(str, "E+", "*10^");
    replace_Exp(str, "E-", "/10^");
  }

  return main_examination(str, i, result, trig);
}

bool s21::Calck::main_examination(std::string &str, int &i, bool &result,
                                  bool trig) {
  int len = str.length();
  int point = 0;
  int open_bracket = trig == 0 ? 0 : 1;
  int clouse_bracket = 0;
  for (; (i < len && result != ERROR && trig == 0) ||
         (trig == 1 && open_bracket != clouse_bracket && result != ERROR);
       i++) {
    if (isdigit(str[i])) {
      if (!after_the_number(str[i + 1]) && i + 1 != len) result = ERROR;
    } else if (str[i] == '.') {
      if (!isdigit(str[i + 1]) || !isdigit(str[i - 1]) || point == 1 || i == 0)
        result = ERROR;
      point = 1;
    } else if (str[i] == 'x') {
      if (!is_operator(str[i + 1]) && str[i + 1] != ')' && i +1!= len ) {
        result = ERROR;
      }
    } else if (str[i] == 'e' || str[i] == 'E') {
      if (!isdigit(str[i - 1]) || i == 0) {
        result = ERROR;
      }
    } else if (is_operator(str[i])) {
      point = 0;
      if (!after_the_operator(str[i + 1]) || i + 1 == len) {
        result = ERROR;
      }
    } else if (str[i] == '(') {
      open_bracket++;
      if (!after_the_open_bracket(str[i + 1])) {
        result = ERROR;
      }
    } else if (str[i] == ')') {
      clouse_bracket++;
      if (!after_the_open_bracket(str[i + 1]) && str[i + 1] != ')' &&
          i + 1 != len) {
        result = ERROR;
      }
    } else if (str[i] == '^') {
      if (!after_the_degree(str[i + 1])) {
        result = ERROR;
      }
    } else if (str.find("mod", i, i + 3) != std::string::npos) {
      i += 3;
      if (!after_the_mod(str[i + 1])) {
        result = ERROR;
      }
    } else if (search_trig(str, i)) {
      if (i + 1 == len || !after_the_open_bracket(str[i + 1])) {
        result = ERROR;
      } else {
        i++;
        result = main_examination(str, i, result, 1);
        i--;
      }
    }else
      result = ERROR;
  }
  if (open_bracket != clouse_bracket) result = ERROR;
  return result;
}

bool s21::Calck::search_trig(std::string &str, int &i) {
  bool result = ERROR;
  if ((str.find("cos(", i, 4) != std::string::npos) ||
      (str.find("sin(", i, 4) != std::string::npos) ||
      (str.find("tan(", i, 4) != std::string::npos) ||
      (str.find("log(", i, 4) != std::string::npos)) {
    i += 3;
    result = OK;
  } else if ((str.find("cos(", i, 4) != std::string::npos) ||
             (str.find("cos(", i, 4) != std::string::npos) ||
             (str.find("cos(", i, 4) != std::string::npos) ||
             (str.find("cos(", i, 4) != std::string::npos)) {
    i += 4;
    result = OK;
  } else if (str.find("ln(", i, 3) != std::string::npos) {
    i += 2;
    result = OK;
  }
  return result;
}

bool s21::Calck::is_operator(char a) {
  return (a == '*' || a == '/' || a == '+' || a == '-' || a == 'm' || a == '^');
}

bool s21::Calck::is_trig(char a) {
  return (a == 'c' || a == 's' || a == 't' || a == 'a');
}

// after the ...
bool s21::Calck::after_the_number(char a) {
  return (isdigit(a) || is_operator(a) || a == '.' || a == ')' || a == 'e' ||
          a == 'E');
}

bool s21::Calck::after_the_operator(char a) {
  return (isdigit(a) || is_trig(a) || a == 'l' || a == 'm' || a == 'x' ||
          a == '(');
}

bool s21::Calck::after_the_open_bracket(char a) {
  return (isdigit(a) || is_trig(a) || a == 'l' || a == 'm' || a == 'x' ||
          a == '(' || a == '+' || a == '-');
}

bool s21::Calck::after_the_degree(char a) {
  return (isdigit(a) || is_trig(a) || a == 'l' || a == 'x' || a == '(' ||
          a == '+' || a == '-');
}

bool s21::Calck::after_the_mod(char a) {
  return (isdigit(a) || is_trig(a) || a == 'l' || a == 'x' || a == '(');
}

void s21::Calck::replace_Exp(std::string &str, std::string Exp,
                             std::string Math) {
  size_t pos = 0;
  while ((pos = str.find(Exp)) != str.npos) {
    str.replace(pos, Exp.size(), Math);
  }
}
