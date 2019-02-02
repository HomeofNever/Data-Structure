#include <iostream>

#include "Rectangle.h"
#include "Point2D.h"
#include <math.h>

int main() {
//    // Create Some points
//    Point2D();
//    Point2D a = Point2D(1,1);
//    std::cout << a.x() << a.y() << std::endl;
//    Point2D b = Point2D(3,3);
//    std::cout << b.x() << b.y() << std::endl;
//    Point2D c = Point2D(-1,-1);
//    Point2D d = Point2D(10, 10);
//    Point2D e = Point2D(5,5);
//    Point2D l = Point2D(2,2);
//
////    Rectangle x = Rectangle(a, b);
////
////    std::cout << x.lower_left_corner().x() << x.lower_left_corner().y()
////              << x.upper_right_corner().x() << x.upper_right_corner().y() << std::endl;
////    print_rectangle(x);
//
//    Rectangle x = Rectangle(a, b);
//    Rectangle y = Rectangle(a, d);
//    Rectangle z = Rectangle(c, b);
//
//    // Print
//    print_rectangle(x);
//    print_rectangle(y);
//    print_rectangle(z);
//
//    // True case
//    bool t_point = y.is_point_within(e);
//    bool t = y.add_point(e);
//    y.add_point(l);
//    x.add_point(l);
//    // False case
//    std::cout << "f" << std::endl;
//    std::cout << d.x() << d.y() << std::endl;
//    bool f_point = z.is_point_within(d);
//    bool f = z.add_point(d);
//
//    std::cout << "case t: " << t_point << std::endl;
//    std::cout << "case f: " << f_point << std::endl;
//
//    print_rectangle(y);
//    print_rectangle(z);
//
//    std::cout << "both points" << std::endl;
//    std::vector<Point2D> res = points_in_both(x,y);
//    for (unsigned int i = 0; i < res.size(); i++)
//    {
//        std::cout << res[i].x() << ' ' << res[i].y() << std::endl;
//    }
    int a = 4;
    float c = std::ceil((float) a / 3) * 2;
    std::cout << (int)c << std::endl;
}