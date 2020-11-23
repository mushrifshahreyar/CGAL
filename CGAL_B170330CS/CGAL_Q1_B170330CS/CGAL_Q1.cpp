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

    string path = "bin/inputs/input1.txt";
    if(argc > 1) {
        string filename(argv[1]);
        path = "bin/inputs/" + filename;
    }
    
    points = readFile(path);

    QApplication app(argc, argv);
    
    QGraphicsScene scene;
    scene.setSceneRect(0,0, 640,320);
    
    for (auto it=points.begin(); it != points.end(); ++it) {
        Point temp = *it;
        
        QBrush brush;
        brush.setColor(QColor(1,1,1));
        brush.setStyle(Qt::SolidPattern);
        QPen pen(Qt::black, 1, Qt::SolidLine);
        scene.addEllipse(temp.x(),temp.y() , 5,5,pen,brush);
    }
	
    QGraphicsView* view = new QGraphicsView(&scene);
    
    view->show();
    return app.exec();


}