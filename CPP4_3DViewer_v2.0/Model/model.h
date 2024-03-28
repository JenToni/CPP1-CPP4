/**
 * @file model.h
 * @author sigridva lauralep
 * @date 11 Fedruary 2024
 * @brief File containing Model of project 3D_viewer, implementing pattern MVC.
 *
 */

#ifndef MODEL_H
#define MODEL_H

#include <QObject>

#include "../View/mainwindow.h"
#include "object.h"

namespace s21 {
class Model : public QObject {
  Q_OBJECT

 private:
  Object *obj = nullptr;
  std::string filepath = "";
  double moveX = 0., moveY = 0., moveZ = 0.;
  tuple angles = {0, 0, 0};
  double scale = 1.;

 public:
  Model(QObject *pobj = 0);
  void reset();
  virtual ~Model();

 public slots:
  void ApplyCommand(Command &cmd);

 signals:
  void ModelToView(s21::Object &objectToRender);
};

}  // namespace s21

#endif  // MODEL_H
