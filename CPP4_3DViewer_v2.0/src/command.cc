/**
 * @file command.cpp
 * @author sigridva lauralep
 * @date 11 Fedruary 2024
 * @brief File containing implementation of class Command, which implements
 * pattern Command.
 *
 */
#include "command.h"

#include <iostream>

namespace s21 {

Command::Command(QObject *parent) : QObject{parent} {
  emit SendToGLWidget(*this);
}

Command::Command(Command &cmd2) : QObject(nullptr) {
  projection_type = cmd2.projection_type;
  angles = cmd2.angles;
  translate = cmd2.translate;
  rgbBackground = cmd2.rgbBackground;
  rgbVertice = cmd2.rgbVertice;
  rgbEdge = cmd2.rgbEdge;
  pointerToVertices_ = cmd2.pointerToVertices_;
  verticesNum_ = cmd2.verticesNum_;
  pointerToFacets_ = cmd2.pointerToFacets_;
  facetsNum_ = cmd2.facetsNum_;
  lineType = cmd2.lineType;
  width_lines = cmd2.width_lines;
}

Command Command::operator=(Command &cmd2) {
  projection_type = cmd2.projection_type;
  angles = cmd2.angles;
  translate = cmd2.translate;
  rgbBackground = cmd2.rgbBackground;
  rgbVertice = cmd2.rgbVertice;
  rgbEdge = cmd2.rgbEdge;
  pointerToVertices_ = cmd2.pointerToVertices_;
  verticesNum_ = cmd2.verticesNum_;
  pointerToFacets_ = cmd2.pointerToFacets_;
  facetsNum_ = cmd2.facetsNum_;
  lineType = cmd2.lineType;
  return *this;
}

void Command::setFilePath(const std::string &newFilePath) {
  filePath = newFilePath;
}

std::string Command::getFilePath() { return filePath; }

void Command::setGl() { emit SendToGLWidget(*this); }

void Command::setObjInfo(double *pointerToVertices, int verticesNum,
                         unsigned int *pointerToFacets,
                         int facetsNum) noexcept {
  pointerToVertices_ = pointerToVertices;
  verticesNum_ = verticesNum;
  pointerToFacets_ = pointerToFacets;
  facetsNum_ = facetsNum;
  emit SendToGLWidget(*this);
}

unsigned int *Command::getFacets() noexcept { return pointerToFacets_; }

double *Command::getVertices() noexcept { return pointerToVertices_; }

unsigned int Command::getVerticesNum() noexcept { return verticesNum_; }

unsigned int Command::getFacetsNum() noexcept { return facetsNum_; }

bool Command::getFirstInit() noexcept { return firstInit; }

void Command::clear() noexcept {
  anglesRotate = {0, 0, 0};
  translate = {0, 0, 0};
  scale = 1.;
}

void Command::setLineType(int type) noexcept {
  lineType = type;
  emit SendToGLWidget(*this);
}

int Command::getTypeLine() noexcept { return lineType; }

void Command::setVerticeType(int type) noexcept {
  verticeType = type;
  emit SendToGLWidget(*this);
}

int Command::getVerticeType() noexcept { return verticeType; }

void Command::setEdgeWidth(int width) noexcept {
  width_lines = width;
  emit SendToGLWidget(*this);
}

int Command::getEdgeWidth() noexcept { return width_lines; }

void Command::setVerticeWidth(int width) noexcept {
  width_dots = width;
  emit SendToGLWidget(*this);
}

int Command::getVerticeWidth() noexcept { return width_dots; }

void Command::setProjection(int type) noexcept {
  projection_type = type;
  emit SendToGLWidget(*this);
}

int Command::getProjection() noexcept { return projection_type; }

void Command::setRotationX(float x, bool GLWidgetConnect) noexcept {
  anglesRotate.axisX = x;
  if (GLWidgetConnect) {
    emit SendToGLWidget(*this);
  } else {
    firstInit = YES;
  }
}

void Command::setRotationY(float y, bool GLWidgetConnect) noexcept {
  anglesRotate.axisY = y;
  if (GLWidgetConnect) {
    emit SendToGLWidget(*this);
  } else {
    firstInit = YES;
  }
}

void Command::setRotationZ(float z) noexcept {
  anglesRotate.axisZ = z;
  firstInit = YES;
}

tuple *Command::getAngles() noexcept { return &anglesRotate; }

void Command::setScale(float s, float normalization,
                       bool GLWidgetConnect) noexcept {
  scale = s / normalization;
  if (GLWidgetConnect) {
    emit SendToGLWidget(*this);
  }
}

void Command::setTranslateX(float x) noexcept { translate.axisX = x / 100; }

void Command::setTranslateY(float y) noexcept { translate.axisY = y / 100; }

void Command::setTranslateZ(float z) noexcept { translate.axisZ = z / 100; }

void Command::setVerticeColors(const float &r, const float &g,
                               const float &b) noexcept {
  colorsVertice_.axisX = r;
  colorsVertice_.axisY = g;
  colorsVertice_.axisZ = b;
  emit SendToGLWidget(*this);
}

void Command::setEdgeColors(const float &r, const float &g,
                            const float &b) noexcept {
  colorsEdge_.axisX = r;
  colorsEdge_.axisY = g;
  colorsEdge_.axisZ = b;
  emit SendToGLWidget(*this);
}

void Command::setBackColors(const float &r, const float &g,
                            const float &b) noexcept {
  colorsBackground_.axisX = r;
  colorsBackground_.axisY = g;
  colorsBackground_.axisZ = b;
  emit SendToGLWidget(*this);
}

tuple &Command::getBackgroundColor() { return colorsBackground_; }

tuple &Command::getVerticeColor() { return colorsVertice_; }

tuple &Command::getEdgeColor() { return colorsEdge_; }

tuple *Command::getTranslate() { return &translate; }

float Command::getScale() noexcept { return scale; }
}  // namespace s21
