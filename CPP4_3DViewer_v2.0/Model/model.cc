/**
 * @file model.cc
 * @author lauralep sigridva
 * @date 11 Fedruary 2024
 * @brief File containing implementation of class Model, which keeps all methods
 * for working with Model (MVC).
 *
 */
#include "model.h"

s21::Model::Model(QObject *pobj) : QObject(pobj) { obj = new s21::Object(); }

void s21::Model::reset() {
  moveX = moveY = moveZ = 0.;
  angles = {0, 0, 0};
  scale = 1.;
}

s21::Model::~Model() { delete obj; }

void s21::Model::ApplyCommand(Command &cmd) {
  if (filepath != cmd.getFilePath() && cmd.getFilePath() != "") {
    reset();
    filepath = cmd.getFilePath();
    obj->parseModel(filepath);
    obj->normalizeVertices();
  }

  if (filepath != "") {
    if (angles.axisX != cmd.getAngles()->axisX) {
      double rotation = cmd.getAngles()->axisX > angles.axisX
                            ? cmd.getAngles()->axisX - angles.axisX
                            : -(angles.axisX - cmd.getAngles()->axisX);

      angles.axisX = cmd.getAngles()->axisX;
      obj->rotateModel(rotation, static_cast<int>(Axes::X));
    }

    if (angles.axisY != cmd.getAngles()->axisY) {
      double rotation = cmd.getAngles()->axisY > angles.axisY
                            ? cmd.getAngles()->axisY - angles.axisY
                            : -(angles.axisY - cmd.getAngles()->axisY);

      angles.axisY = cmd.getAngles()->axisY;
      obj->rotateModel(rotation, static_cast<int>(Axes::Y));
    }

    if (angles.axisZ != cmd.getAngles()->axisZ) {
      double rotation = cmd.getAngles()->axisZ > angles.axisZ
                            ? cmd.getAngles()->axisZ - angles.axisZ
                            : -(angles.axisZ - cmd.getAngles()->axisZ);

      angles.axisZ = cmd.getAngles()->axisZ;
      obj->rotateModel(rotation, static_cast<int>(Axes::Z));
    }

    if (moveX != cmd.getTranslate()->axisX) {
      obj->moveModel((cmd.getTranslate()->axisX - moveX),
                     static_cast<int>(Axes::X));
      moveX = cmd.getTranslate()->axisX;
    }

    if (moveY != cmd.getTranslate()->axisY) {
      obj->moveModel((cmd.getTranslate()->axisY - moveY),
                     static_cast<int>(Axes::Y));
      moveY = cmd.getTranslate()->axisY;
    }

    if (moveZ != cmd.getTranslate()->axisZ) {
      obj->moveModel((cmd.getTranslate()->axisZ - moveZ),
                     static_cast<int>(Axes::Z));
      moveZ = cmd.getTranslate()->axisZ;
    }
    if (scale != cmd.getScale()) {
      obj->scaleModel(scale, cmd.getScale());
      scale = cmd.getScale();
    }
  }
  emit ModelToView(*obj);
}
