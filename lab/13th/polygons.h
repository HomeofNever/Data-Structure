//
// Created by luox6 on 2019/4/23.
//

#ifndef INC_13TH_POLYGONS_H
#define INC_13TH_POLYGONS_H


#include <string>
#include <vector>
#include "utilities.h"

class Polygon {
public:
    Polygon(const std::string &name, const std::vector<Point> &points): _name(name), _points(points) {
      buildVectors();
    };
    virtual ~Polygon(){};

    std::string getName() const {
      return _name;
    }

    bool hasEqSide() {
      for (int i = 0; i < _vectors.size(); i++) {
        if (EqualSides(_vectors[i].Length(), _vectors[(i+1) % _vectors.size()].Length())) {
          return true;
        }
      }

      return false;
    }

    bool HasAllEqualSides() {
      for (int i = 0; i < _vectors.size(); i++) {
        if (!EqualSides(_vectors[i].Length(), _vectors[(i+1) % _vectors.size()].Length())) {
          return false;
        }
      }

      return true;
    }

protected:
    std::string _name;
    std::vector<Point> _points;
    std::vector<Vector> _vectors;

private:
    void buildVectors() {
      for (int i = 0; i < _points.size(); i++) {
          _vectors.push_back(Vector(_points[i], _points[(i+1) % _points.size()]));
      }
    }
};

class Triangle : public Polygon{
public:
    Triangle(const std::string &name, const std::vector<Point> &points): Polygon(name, points) {
      if (points.size() != 3) {
        std::cerr << "Points " + std::to_string(points.size()) + " does not match 3" << std::endl;
        throw 1;
      }
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(const std::string &name, const std::vector<Point> &points): Triangle (name, points) {
      if (!hasEqSide()) {
        std::cerr <<  "Same Side No Found" << std::endl;
        throw 2;
      }
    }
};

class EquilateralTriangle : public IsoscelesTriangle {
public:
    EquilateralTriangle(const std::string &name, const std::vector<Point> &points): IsoscelesTriangle (name, points) {
      if (!HasAllEqualSides()) {
        std::cerr << "Not All Sides are the same" << std::endl;
        throw 3;
      }
    }
};

class Quadrilateral : public Polygon{
public:
    Quadrilateral(const std::string &name, const std::vector<Point> &points): Polygon (name, points) {
      if (points.size() != 4) {
        std::cerr << "Not 4" << std::endl;
        throw 5;
      }
    }
};

class Rectangle : public Quadrilateral {
public:
    Rectangle(const std::string &name, const std::vector<Point> &points): Quadrilateral (name, points) {
      if (!all90()) {
        std::cerr << "Not all 90" << std::endl;
        throw 6;
      }
    }

    bool all90() {
      for (int i = 0; i < _points.size(); i++) {
        if (!EqualAngles(Angle(
                _points[i], _points[(i+1) % _points.size()], _points[(i+2) % _points.size()]
        ), 90)) {
          return false;
        }
      }

      return true;
    }
};

class Square : public Rectangle {
public:
    Square(const std::string &name, const std::vector<Point> &points) : Rectangle (name, points) {
      if (!HasAllEqualSides()) {
        std::cerr << "Not all eq side" << std::endl;
        throw 7;
      }
    }
};

#endif //INC_13TH_POLYGONS_H
