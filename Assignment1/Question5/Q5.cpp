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

vector< Point > readFile(string temp) {
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

    return points;
}

double findTriangleArea(Triangle triangle) {

    double area;
    area = (triangle.b.x() - triangle.a.x()) * (triangle.c.y() - triangle.a.y()) - (triangle.c.x() - triangle.a.x()) * (triangle.b.y() - triangle.a.y());
    area = area / 2.0;
    return area;
}

double findPolygonArea( vector< Point > points) {
    double area = 0;
    int midPoint = 0;
    for(int i=1; i < points.size() - 1; ++i) {
        Point a = points[0];
        Point b = points[i];
        Point c = points[i+1];

        Triangle triangle;
        triangle.a = a;
        triangle.b = b;
        triangle.c = c;

        double triArea = findTriangleArea(triangle);

        area += triArea;

        cout<<"Triangle 0 "<<i<<" "<<i+1<<endl;
        cout<<triArea<<endl;

    }

    return abs(area);
}

int main(int argc, char **argv)
{
    

    vector< Point > points = readFile("input.txt");
    
    double area = findPolygonArea(points);

    cout<<area<<endl;

    QApplication app(argc, argv);
    
    QGraphicsScene scene;

    scene.setSceneRect(0,0,500,500);

    int n = points.size();

    for(int i=0;i < n - 1; ++i) {
        Point p = points[i];
        Point q = points[i+1];

        scene.addLine(p.x(),p.y(),q.x(),q.y());

    }
    scene.addLine(points[0].x(),points[0].y(), points[n-1].x(), points[n-1].y());
    
    scene.addText(QString::fromStdString(to_string(area)));

    QGraphicsView* view = new QGraphicsView(&scene);
    view->show();
    app.exec();

    return 0;

}
