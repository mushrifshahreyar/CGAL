#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <boost/format.hpp>
#include <CGAL/Point_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Cartesian.h>
#include <QLineF>
#include <QRectF>
#include <QString>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <string>

using namespace CGAL;
using namespace std;

typedef Point_2< Cartesian<double> > Point;
typedef Line_2< Cartesian<double> > Segment;

typedef struct Triangle {
    Point a,b,c;
}Triangle;

Triangle readFile(string temp) {
    string line;
    ifstream file;
    file.open(temp);
    vector< Point > points;
    Triangle triangle;
    if(file.is_open()) {
        while( getline(file,line) ) {
            stringstream ss;
            double a1,b1;

            ss<<line;
            ss>>a1>>b1;

            Point p(a1,b1);
            points.push_back(p);
        }
        file.close();
    }
    else {
        cout<<"File not found";
    }

    triangle.a = points[0];
    triangle.b = points[1];
    triangle.c = points[2];
    
    return triangle;
}

double findArea(Triangle triangle) {

    double area;
    area = (triangle.b.x() - triangle.a.x()) * (triangle.c.y() - triangle.a.y()) - (triangle.c.x() - triangle.a.x()) * (triangle.b.y() - triangle.a.y());
    area = area / 2.0;
    area = abs(area);
    return area;
}

int main(int argc, char **argv)
{
    

    Triangle triangle = readFile("input.txt");
    double area = findArea(triangle);

    cout<<area<<endl;

    QApplication app(argc, argv);
    
    QGraphicsScene scene;

    scene.setSceneRect(0,0,500,500);
    scene.addLine(triangle.a.x(), triangle.a.y(), triangle.b.x(), triangle.b.y());
    scene.addLine(triangle.b.x(), triangle.b.y(), triangle.c.x(), triangle.c.y());
    scene.addLine(triangle.a.x(), triangle.a.y(), triangle.c.x(), triangle.c.y());

    scene.addText(QString::fromStdString(to_string(area)));

    QGraphicsView* view = new QGraphicsView(&scene);
    view->show();
    app.exec();

    return 0;

}
