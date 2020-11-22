#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <boost/format.hpp>
#include <QtGui>
#include <CGAL/Point_2.h>
#include <CGAL/Cartesian.h>
#include <QLineF>
#include <QRectF>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>



using namespace CGAL;
using namespace std;

typedef Point_2< Cartesian<double> > Point;

 list<Point> readFile(string temp) {
    
    string line;
    ifstream file;
    file.open(temp);
    list<Point> points;
    if(file.is_open()) {
        while( getline(file,line) ) {
            stringstream ss;
            double n1,n2;
            ss<<line;
            ss>>n1>>n2;

            Point p(n1,n2);
            points.push_back(p);

        }
        file.close();
    }
    else {
        cout<<"File not found";
    }
    return points;
}

int main(int argc, char **argv)
{
    list<Point> points;

    points = readFile("input.txt");

    QApplication app(argc, argv);
    
    QGraphicsScene scene;
    scene.setSceneRect(0,0, 640,320);
    
    for (auto it=points.begin(); it != points.end(); ++it) {
        Point temp = *it;
        scene.addEllipse(temp.x(),temp.y() , 1,1);
    }
	
    QGraphicsView* view = new QGraphicsView(&scene);
    
    view->show();
    return app.exec();


}