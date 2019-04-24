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

    bool HasARightAngle() {
      for (int i = 0; i < _points.size(); i++) {
        if (RightAngle(Angle(
                _points[i], _points[(i+1) % _points.size()], _points[(i+2) % _points.size()]
        ))) {
          return true;
        }
      }

      return false;
    };

    bool HasAllEqualAngles() {
      double angle = -1;
      for (int i = 0; i < _points.size(); i++) {
        if (angle == -1) {
          angle = Angle(_points[i], _points[(i + 1) % _points.size()], _points[(i + 2) % _points.size()]);
        }else {
          if (angle != Angle(_points[i], _points[(i + 1) % _points.size()], _points[(i + 2) % _points.size()])) {
            return false;
          }
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

class RightTriangle : virtual public Triangle {
public:
    RightTriangle(const std::string &name, const std::vector<Point> &points): Triangle(name, points) {
      if (!HasARightAngle()) {
        std::cerr << "No 90 found" << std::endl;
        throw 1;
      }
    }
};

class IsoscelesTriangle : virtual public Triangle {
public:
    IsoscelesTriangle(const std::string &name, const std::vector<Point> &points): Triangle (name, points) {
      if (!hasEqSide()) {
        std::cerr <<  "Same Side No Found" << std::endl;
        throw 2;
      }
    }
};

class IsoscelesRightTriangle : public RightTriangle, public IsoscelesTriangle {
public:
    IsoscelesRightTriangle(const std::string &name, const std::vector<Point> &points) :
      RightTriangle(name, points), IsoscelesTriangle(name, points), Triangle(name, points) {
      // Nothing
    }
};


class EquilateralTriangle : public IsoscelesTriangle {
public:
    EquilateralTriangle(const std::string &name, const std::vector<Point> &points):
      IsoscelesTriangle (name, points), Triangle(name, points) {
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
        if (!RightAngle(Angle(
                _points[i], _points[(i+1) % _points.size()], _points[(i+2) % _points.size()]
        ))) {
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
