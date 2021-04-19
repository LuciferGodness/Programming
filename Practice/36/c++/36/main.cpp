#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const auto PI = 3.141592653589793;
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
    bool operator== (Point& p)
    {
        if (abs(p.get_x() - a1) < pow(10, -10) && abs(p.get_y() - a2) < pow(10, -10))
            return true;
        else
            return false;
    }

    bool operator!= (Point& p)
    {
        if (abs(p.get_x() - a1) > pow(10, -10) && abs(p.get_y() - a2) > pow(10, -10))
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

int main() {
    std::vector<Point> original;
    std::ifstream fin("data.txt");
    if (!fin.is_open()) {
        std::cout << "Can't open file" << std::endl;
        return 1;
    }
    else {
        while (!fin.eof()) {
            Point p;
            fin >> p;
            fin.ignore(2); // Точки разделены двумя символами ", "
            original.push_back(p);
        }
        fin.close();
    }

    std::vector<Point> simulacrum(original);
    for (auto& p : simulacrum) {
        cout << p;
        p.set_x(p.get_x() + 10);
        p.set_phi(p.get_phi() + 180 * PI / 180);
        p.set_y(-p.get_y());
        p.set_x(-p.get_x() - 10);
        std::cout << p << std::endl;
    }

    if (std::equal(original.begin(), original.end(), simulacrum.begin()))
        std::cout << "\nIt works!\n";
    else
        std::cout << "\nIt not works!\n";
}
