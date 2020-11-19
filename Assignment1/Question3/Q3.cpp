#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <boost/format.hpp>
#include <CGAL/Point_2.h>
#include <CGAL/Cartesian.h>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <string>
#include <QString>

using namespace CGAL;
using namespace std;

typedef Point_2<Cartesian<double>> Point;
typedef Line_2<Cartesian<double>> Segment;

vector<pair<Point, Point>> readFile(string temp) {
    string line;
    ifstream file;
    file.open(temp);
    vector<pair<Point, Point>> lines;
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss;
            double a1, b1;
            double a2, b2;
            ss << line;
            ss >> a1 >> b1 >> a2 >> b2;

            Point p(a1, b1);
            Point q(a2, b2);

            lines.push_back(make_pair(p, q));
        }
        file.close();
    }
    else {
        cout << "File not found";
    }
    return lines;
}

double findArea(Point a, Point b, Point c) {
    double area;
    area = (b.x() - a.x()) * (c.y() - a.y()) - (c.x() - a.x()) * (b.y() - a.y());
    area = area / 2.0;
    return area;
}

bool collinear(Point a, Point b, Point c) {

    if (findArea(a, b, c) == 0) {
        return true;
    }
    return false;
}

bool left(Point a, Point b, Point c) {
    if (findArea(a, b, c) > 0) {
        return true;
    }
    return false;
}

bool Xor(bool a, bool b) { 
    return !a ^ !b;
}

bool intersectProp(Point a, Point b, Point c, Point d) { 
    if (collinear(a, b, c) || collinear(a, b, d) || collinear(c, d, a) || collinear(c, d, b)) {
        return false;
    }
    return (Xor(left(a, b, c), left(a, b, d)) && (Xor(left(c, d, a), left(c, d, b))));
}

bool between(Point a, Point b, Point c) {
    if (!collinear(a, b, c)) {
        return false;
    }
    if (a.x() != b.x()) {
        return ((a.x() <= c.x()) && (c.x() <= b.x())) || ((a.x() >= c.x()) && (c.x() >= b.x()));
    }
    return ((a.y() <= c.y()) && (c.y() <= b.y())) || ((a.y() >= c.y()) && (c.y() >= b.y()));
}

bool findIntersection(Point a, Point b, Point c, Point d) {

    if (intersectProp(a, b, c, d)) {
        return true;
    }
    else {
        if (between(a, b, c) || between(a, b, d) || between(c, d, a) || between(c, d, b)) {
            return true;
        }
    }

    return false;
}

Point findPoint(Point p1, Point q1, Point p2, Point q2) {
    double m1,c1;
    bool line1 = false;
    bool line2 = false;
    double m2,c2;
    if(p1.x() != q1.x()) {
        m1 = ((q1.y() - p1.y()) / (q1.x() - p1.x()));
        c1 = p1.y() - (m1 * p1.x());
    } 
    else {
        line1 = true;
    }
    
    if(p2.x() != q2.x()) {
        m2 = ((q2.y() - p2.y()) / (q2.x() - p2.x()));
        c2 = p2.y() - (m2 * p2.x());
    } 
    else {
        line2 = true;
    }

    if(line1) {
        double x = p1.x();
        double y = (m2 * x) + c2;
        
        return Point(x,y);
    }
    else if(line2) {
        double x = p2.x();
        double y = (m1 * x) + c1;
        
        return Point(x,y);
    }
    else { 
        double x = ((c1 - c2) / (m2 - m1));
        double y = (((m2 * c1) - (m1 * c2))/(m2 - m1));
        
        return Point(x,y);
    }
}

int main(int argc, char **argv) {
    vector<pair<Point, Point>> lines;

    lines = readFile("input.txt");

    QApplication app(argc, argv);

    vector<QGraphicsScene> scenes;

    for (int i = 0; i < lines.size() - 1; ++i) {

        for (int j = i + 1; j < lines.size(); ++j) {
            QGraphicsScene scene;
            Point p1 = lines[i].first;
            Point q1 = lines[i].second;

            Point p2 = lines[j].first;
            Point q2 = lines[j].second;

            
            scene.addText(QString::fromStdString("Line : " + to_string(i+1) + " " + to_string(j+1)));

            if (findIntersection(p1, q1, p2, q2)) {
            
                Point intPoint = findPoint(p1,q1,p2,q2);
                
                string x_str = to_string(intPoint.x());
                string y_str = to_string(intPoint.y());
                
                string finalStr = "\n( " + x_str + " , " + y_str + "\n";

                scene.addText(QString::fromStdString(finalStr));
                
            }
            else {
                
                string finalStr = "\nNot intersecting";
                scene.addText(QString::fromStdString(finalStr));
            }

            

            scene.setSceneRect(0, 0, 500, 500);

            scene.addLine(p1.x(), p1.y(), q1.x(), q1.y());
            scene.addLine(p2.x(), p2.y(), q2.x(), q2.y());

            QGraphicsView *view = new QGraphicsView(&scene);
            view->show();

            app.exec();
        }
    }

    return 0;
}