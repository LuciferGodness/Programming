#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

double sqr(double a);
bool equal(double a, double b, double e = 1E-10);

enum class cs {
    Cartesian,
    Polar
};

class Point
{
private:
    double a1, a2;
    cs coord_system;
public:
    double new_a1, new_a2;
    Point(double a1 = 0, double a2 = 0, cs coord_system = cs::Cartesian) :a1(a1), a2(a2), coord_system(coord_system) {};
    //bool operator== (Point& p)
    //{
      //  if (abs(p.get_x() - a1) < pow(10, -10) && abs(p.get_y() - a2) < pow(10, -10))
        //    return true;
        //else
         //   return false;
    //}

    //bool operator!= (Point& p)
    //{
      //  if (abs(p.get_x() - a1) > pow(10, -10) && abs(p.get_y() - a2) > pow(10, -10))
        //    return true;
        //else
          //  return false;
    //}

    bool operator== (Point v)
    {
        if (abs(get_x() - v.get_x()) < pow(10, -10) && abs(get_y() - v.get_y()) < pow(10, -10))
            return true;
        else
            return false;
    }

    friend istream& operator>> (istream& in, Point& p)
    {
        double p1, p2;
        in.ignore(1);
        in >> p1;
        in.ignore(1);
        in >> p2;
        in.ignore(1);
        p.set_x(p1);
        p.set_y(p2);
        return in;
    }

    friend ostream& operator<< (ostream& out, Point& p)
    {
        return out << '(' << p.get_x() << ", " << p.get_y() << ')';
    }

    double get_x()
    {
        new_a1 = a1;
        return a1;
    }

    double get_y()
    {
        new_a2 = a2;
        return a2;
    }

    void set_x(double a1)
    {
        this->a1 = a1;
    }

    void set_y(double a2)
    {
        this->a2 = a2;
    }

    double get_r()
    {
        new_a1 = sqrt(a1*a1+a2*a2);
        return sqrt(a1*a1+a2*a2);
    }

    double get_phi()
    {
        new_a2 = atan2(a2,a1);
        return atan2(a2,a1);
    }

    void set_r(double r)
    {
        a1 = cos(get_phi())*r;
        a2 = sin(get_phi())*r;
    }

    void set_phi(double phi)
    {
        a1 = cos(phi)*get_r();
        a2 = sin(phi)*get_r();
    }
};

class Vector
{
public:
    Point vect;
    Vector() :vect(1,0) {};
    Vector(Point end) :vect(end.get_x(), end.get_y()) {};
    Vector(Point begin, Point end) :vect(end.get_x() - begin.get_x(), end.get_y() - begin.get_y()) {};

    bool operator== (Vector vect1)
    {
        if(vect == vect1.vect)
            return true;
        else
            return false;
    }

    Vector operator-()
    {
        Point invert = vect;
        invert.set_x(-(invert.get_x()));
        invert.set_y(-(invert.get_y()));
        return Vector(invert);
    }

    Vector operator+(Vector vect1)
    {
        Point sum = vect;
        sum.set_x(vect.get_x()+vect1.vect.get_x());
        sum.set_y(vect.get_y()+vect1.vect.get_y());
        return Vector(sum);
    }

    Vector operator-(Vector vect1)
    {
        Point dif = vect;
        dif.set_x(vect.get_x()-vect1.vect.get_x());
        dif.set_y(vect.get_y()-vect1.vect.get_y());
        return Vector(dif);
    }

    Vector operator*(double m)
    {
        Point com = vect;
        com.set_x(vect.get_x()*m);
        com.set_y(vect.get_y()*m);
        return Vector(com);
    }

    double length()
    {
        return vect.get_r();
    }

    double operator*(Vector vect1)
    {
        return length() * vect1.length() * cos(vect.get_phi() - vect1.vect.get_phi());
    }
};

int main()
{
    Vector a(Point(1, 2)), b(Point(-2, 0), Point(-1, 2));
    if (a == b && b == a) cout << "Equality test passed\n";
    else cout << "Equality test failed\n";

    Vector na(Point(-1, -2)), ox(Point(1, 0)), nox(Point(-1, 0)), oy(Point(0, 1)), noy(Point(0, -1));
    if (a == -na && na == -a && -ox == nox && -oy == noy) cout << "Invert test passed\n";
    else cout << "Invert test failed\n";

    if (ox + oy + oy == a && -ox == -a + oy + oy) cout << "Summation test passed\n";
    else cout << "Summation test failed\n";

    if (-ox + oy == oy - ox && -oy + ox == ox - oy) cout << "Subtraction test passed\n";
    else cout << "Subtraction test failed\n";

    if (ox * 3 == ox + ox + ox &&
        oy * 3 == oy + oy + oy &&
        ox * (-3) == -ox - ox - ox &&
        oy * (-3) == -oy - oy - oy) cout << "Multiplication by number test passed\n";
    else cout << "Multiplication by number test failed\n";

    if (equal(ox.length(), 1) &&
        equal(oy.length(), 1) &&
        equal((ox * 3 + oy * 4).length(), 5)) cout << "Length test passed\n";
    else cout << "Length test failed\n";

    if (equal(ox*ox, sqr(ox.length())) &&
        equal(oy*oy, sqr(oy.length())) &&
        equal((ox*3 + oy*4)*(ox*3 + oy*4), sqr((ox*3 + oy*4).length()))) cout << "Multiplication by Vector test passed\n";
    else cout << "Multiplication by Vector test failed\n";
}

bool equal(double a, double b, double e) {
    if (-e < a - b && a - b < e) return true;
    else return false;
}

double sqr(double a) {
    return a * a;
}
