#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <boost/format.hpp>
#include <QtGui>
#include <CGAL/Qt/GraphicsViewNavigation.h>
#include <CGAL/Point_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Cartesian.h>
#include <QLineF>
#include <QRectF>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

using namespace CGAL;
using namespace std;

typedef Point_2< Cartesian<double> > Point;

 map< Point, Point> readFile(string temp) {
    
    string line;
    ifstream file;
    file.open(temp);
    map<Point, Point> lines;
    if(file.is_open()) {
        while( getline(file,line) ) {
            stringstream ss;
            double a1,b1;
            double a2,b2;
            ss<<line;
            ss>>a1>>b1>>a2>>b2;

            Point p(a1,b1);
            Point q(a2,b2);

            lines.insert(pair<Point,Point> (p,q));

        }
        file.close();
    }
    else {
        cout<<"File not found";
    }
    return lines;
}

int main(int argc, char **argv)
{
    map<Point, Point> lines;

    string path = "bin/inputs/input1.txt";
    if(argc > 1) {
        string filename(argv[1]);
        path = "bin/inputs/" + filename;
    }
    
    lines = readFile(path);
    
    QApplication app(argc, argv);
    QPainter painter;
    QGraphicsScene scene;
    scene.setSceneRect(0,0, 500,500);
    
    for (auto it=lines.begin(); it != lines.end(); ++it) {
        Point p = it->first;
        Point q = it->second;
        
        scene.addLine(p.x(),p.y(), q.x(), q.y());
    }

	QGraphicsView* view = new QGraphicsView(&scene);
    
    view->show();
    return app.exec();


}