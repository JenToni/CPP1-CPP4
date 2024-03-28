/**
 * @file object.cc
 * @author sigridva lauralep
 * @date 11 Fedruary 2024
 * @brief File containing implementation of class Object, which keeps all
 * information about vertices and facets of each model
 *
 */
#include "object.h"

#include <algorithm>

s21::Object::Object() {}

std::string s21::Object::getFilepath() { return filepath; };

void s21::Object::parseModel(string filename) {
  ifstream fin;
  string line;
  fin.open(filename, std::ios_base::in);
  filepath = filename;

  std::filesystem::path p(filename);
  freeModel();
  coordinates.vertices = (double *)malloc(sizeof(double) * (DEFAULT_SIZE * 3));
  polygons.vertices_indexes =
      (unsigned int *)malloc(sizeof(unsigned int) * (DEFAULT_SIZE + 1));

  if (!coordinates.vertices || !polygons.vertices_indexes) {
    throw(std::overflow_error(MEMORY_LIMIT));
  }
  if (p.extension() != ".obj") {
    freeModel();
    throw std::invalid_argument(INCORRECT_EXTENSION);
  }

  if (!fin.is_open()) {
    freeModel();
    throw std::invalid_argument(INCORRECT_PATH);
  }

  while (getline(fin, line)) {
    if (line[0] == 'v' && line[1] != 't' && line[1] != 'n') {
      extractVerticleFromLine(line);  // parse verticle
    } else if (line[0] == 'f') {
      extractFacetFromLine(line);  // parse facet
    }
  }
  if (facets_num <= 2) {
    freeModel();
    throw std::invalid_argument(INCORRECT_FACET_NUMBER);
  }
}

s21::Object::~Object() { freeModel(); }

void s21::Object::freeModel() {
  if (coordinates.vertices) {
    free(coordinates.vertices);
  }
  coordinates.size = 0;
  coordinates.buffer_size = DEFAULT_SIZE * 3;
  coordinates.vertices = nullptr;
  if (polygons.vertices_indexes) {
    free(polygons.vertices_indexes);
  }
  facets_num = 0;
  vertices_num = 0;
  polygons_buffer_size = DEFAULT_SIZE;
  polygons.vertices_indexes = nullptr;

  x_min = __DBL_MAX__;
  y_min = __DBL_MAX__;
  z_min = __DBL_MAX__;
  x_max = __DBL_MIN__;
  y_max = __DBL_MIN__;
  z_max = __DBL_MIN__;
}

int s21::Object::getVerticesNum() { return vertices_num; }

unsigned int s21::Object::getFacesNum() { return facets_num; };

void s21::Object::extractVerticleFromLine(string line) {
  std::queue<double> q(excludeTokens(line));

  try {
    if (coordinates.buffer_size < (size_t)(coordinates.size + 3)) {
      coordinates.buffer_size += 1024;
      if (void *mem = std::realloc(coordinates.vertices,
                                   coordinates.buffer_size * sizeof(double))) {
        coordinates.vertices = static_cast<double *>(mem);
      } else {
        freeModel();
        throw(std::overflow_error(MEMORY_LIMIT));
      }
    }
    double x = q.front();
    q.pop();
    double y = q.front();
    double z = q.back();

    x_min = fmin(x_min, x);
    y_min = fmin(y_min, y);
    z_min = fmin(z_min, z);

    x_max = fmax(x_max, x);
    y_max = fmax(y_max, y);
    z_max = fmax(z_max, z);

    coordinates.vertices[coordinates.size++] = x;
    coordinates.vertices[coordinates.size++] = y;
    coordinates.vertices[coordinates.size++] = z;
    vertices_num++;
  } catch (std::invalid_argument()) {
    freeModel();
    throw(std::invalid_argument(INCORRECT_NUMBER));
  }
}

void s21::Object::extractFacetFromLine(string line) {
  std::queue<double> q = s21::excludeTokens(line);
  double intpart;
  bool isFisrtIndex = true;
  int size = q.size();
  int lastValue;
  while (!q.empty()) {
    int i = q.front();
    if (polygons_buffer_size < (size_t)(facets_num + 5)) {
      polygons_buffer_size += 1024;
      polygons.vertices_indexes =
          (unsigned int *)realloc(polygons.vertices_indexes,
                                  sizeof(unsigned int) * polygons_buffer_size);
      if (!polygons.vertices_indexes) {
        freeModel();
        throw(std::overflow_error(MEMORY_LIMIT));
      }
    }
    if ((i < 1 || std::modf(i, &intpart) != 0.0) && i != 1) {
      freeModel();
      throw(std::invalid_argument(INCORRECT_FACET));
    } else if (i > vertices_num) {
      freeModel();
      throw(std::invalid_argument(INCORRECT_FACET_LIMIT));
    }
    if (!isFisrtIndex && size != 2) {
      polygons.vertices_indexes[facets_num++] = i - 1;
      polygons.vertices_indexes[facets_num++] = i - 1;
    } else {
      polygons.vertices_indexes[facets_num++] = i - 1;
      lastValue = i - 1;
      isFisrtIndex = false;
    }
    q.pop();
  }
  if (size != 2) {
    polygons.vertices_indexes[facets_num++] = lastValue;
  }
}

void s21::Object::normalizeVertices() noexcept {
  double normalizedX, normalizedY, normalizedZ;
  double max = 0;
  double center_x, center_y, center_z;

  center_x = x_min + (x_max - x_min) / 2;
  center_y = y_min + (y_max - y_min) / 2;
  center_z = z_min + (z_max - z_min) / 2;

  for (int i = 0; i < vertices_num * 3; i += 3) {
    coordinates.vertices[i + static_cast<int>(Axes::X)] -= center_x;
    coordinates.vertices[i + static_cast<int>(Axes::Y)] -= center_y;
    coordinates.vertices[i + static_cast<int>(Axes::Z)] -= center_z;
  }

  normalizedX = x_max - x_min;
  normalizedY = y_max - y_min;
  normalizedZ = z_max - z_min;

  if (normalizedX >= normalizedY && normalizedX >= normalizedZ)
    max = normalizedX;
  if (normalizedY >= normalizedX && normalizedY >= normalizedZ)
    max = normalizedY;
  if (normalizedZ >= normalizedX && normalizedZ >= normalizedY)
    max = normalizedZ;

  double scal = (0.5 - (0.5 * (-1))) / max;

  for (int i = 0; i < vertices_num * 3; i += 3) {
    coordinates.vertices[i + static_cast<int>(Axes::X)] *= scal;
    coordinates.vertices[i + static_cast<int>(Axes::Y)] *= scal;
    coordinates.vertices[i + static_cast<int>(Axes::Z)] *= scal;
  }
}

double *s21::Object::getVetices() { return coordinates.vertices; }

unsigned int *s21::Object::getFacets() { return polygons.vertices_indexes; }

std::queue<double> s21::excludeTokens(string s) {
  setlocale(LC_ALL, "C");
  std::queue<double> q;
  bool next_number = true;
  double var;
  std::size_t pos;
  for (size_t i = 0; i < s.length(); i++) {
    string num = "";
    if ((isdigit(s[i]) || s[i] == '-') && !next_number) {
      while (s[i] != '/' && s[i] != ' ' && s[i] != '\n' && s[i] != '\0') {
        std::replace(num.begin(), num.end(), ',', '.');
        num += s[i++];
      }
      if ((std::istringstream(num) >> var >> std::ws).eof()) {
        var = std::stod(num, &pos);
      } else {
        throw(std::invalid_argument(INCORRECT_NUMBER));
      }

      q.push(var);
      next_number = true;
    }
    if (s[i] == ' ') {
      next_number = false;
    }
  }

  return q;
}

void s21::Object::scaleModel(double oldScale, double newScale) {
  for (int i = 0; i < vertices_num * 3; i += 3) {
    coordinates.vertices[i + 0] *= newScale / oldScale;
    coordinates.vertices[i + 1] *= newScale / oldScale;
    coordinates.vertices[i + 2] *= newScale / oldScale;
  }
}

double s21::Object::getElement(int i) {
  double ans = 0;
  if (coordinates.vertices) {
    ans = coordinates.vertices[i];
  }

  return ans;
}

/////@brief Вращение
/////@param obj Струтура модели
/////@param angle  Угол в градусах
/////@param axis enum: X = 0, Y = 1, Z = 2
void s21::Object::rotateModel(double angle, int axis) {
  DegreesToRadians(&angle);

  if (axis == 0) {
    for (int r = 0; r < vertices_num * 3; r += 3) {
      double temp_y = coordinates.vertices[r + 1];
      double temp_z = coordinates.vertices[r + 2];
      coordinates.vertices[r + 1] = cos(angle) * temp_y + sin(angle) * temp_z;
      coordinates.vertices[r + 2] = -sin(angle) * temp_y + cos(angle) * temp_z;
    }
  } else if (axis == 1) {
    for (int r = 0; r < vertices_num * 3; r += 3) {
      double temp_x = coordinates.vertices[r + 0];
      double temp_z = coordinates.vertices[r + 2];
      coordinates.vertices[r + 0] = cos(angle) * temp_x - sin(angle) * temp_z;
      coordinates.vertices[r + 2] = sin(angle) * temp_x + cos(angle) * temp_z;
    }
  } else if (axis == 2) {
    for (int r = 0; r < vertices_num * 3; r += 3) {
      double temp_y = coordinates.vertices[r + 1];
      double temp_x = coordinates.vertices[r + 0];
      coordinates.vertices[r + 0] = cos(angle) * temp_x + sin(angle) * temp_y;
      coordinates.vertices[r + 1] = -sin(angle) * temp_x + cos(angle) * temp_y;
    }
  }
}

/////@brief Передвижение фигуры
/////@param Model* obj
/////@param axis enum: 0 = X, 1 = Y, 2 = Z
/////@param value  значение перемещения
void s21::Object::moveModel(double value, int axis) {
  for (int r = 0; r < vertices_num * 3; r += 3) {
    coordinates.vertices[r + axis] += value;
  }
}

/////@brief Градусы в радианы
/////@param degrees Угол в градусах
void s21::Object::DegreesToRadians(double *degrees) {
  *degrees = *degrees * (M_PI / 180.);
}
