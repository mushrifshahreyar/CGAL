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
typedef Line_2< Cartesian<double> > Segment;

 vector< pair< Point, Point> > readFile(string temp) {
    
    string line;
    ifstream file;
    file.open(temp);
    vector< pair<Point, Point> > lines;
    if(file.is_open()) {
        while( getline(file,line) ) {
            stringstream ss;
            double a1,b1;
            double a2,b2;
            ss<<line;
            ss>>a1>>b1>>a2>>b2;

            Point p(a1,b1);
            Point q(a2,b2);

            lines.push_back(make_pair(p,q) );

        }
        file.close();
    }
    else {
        cout<<"File not found";
    }
    return lines;
}

struct lineEquation {
    double m,c;
};

void findLine(Point p1, Point q1, Point p2, Point q2) {
    struct lineEquation line1;
    line1.m = ((q1.y() - p1.y()) / (q1.x() - p1.x()));
    line1.c = p1.y() - (line1.m * p1.x());

    cout<<line1.m<<" "<<line1.c<<endl;

    struct lineEquation line2;
    line2.m = ((q2.y() - p2.y()) / (q2.x() - p2.x()));
    line2.c = p2.y() - (line2.m * p2.x());

    cout<<line2.m<<" "<<line2.c<<endl;

    double x = ((line1.c - line2.c) / (line2.m - line1.m));
    double y = (((line2.m * line1.c) - (line1.m * line2.c))/(line2.m - line1.m));
    cout<<x<<" "<<y<<endl;
    // return line1;
}

int main(int argc, char **argv)
{
    vector< pair< Point, Point> > lines;

    lines = readFile("input.txt");

    QApplication app(argc, argv);
    
    vector<QGraphicsScene> scenes;
    
    for (int i = 0; i<lines.size(); ++i) {

        for(int j=0; i<lines.size();++j) {
            Point p1 = lines[i].first;
            Point q1 = lines[i].second;
            
            ++i;
    
            
            Point p2 = lines[i].first;
            Point q2 = lines[i].second;
    
            findLine(p1,q1,p2,q2);
    
            QGraphicsScene scene;
    
            scene.setSceneRect(0,0, 500,500);
    
            scene.addLine(p1.x(),p1.y(), q1.x(), q1.y());
            scene.addLine(p2.x(),p2.y(), q2.x(), q2.y());
    
            QGraphicsView* view = new QGraphicsView(&scene);
            view->show();
    
            app.exec();
        }
        // scenes.push_back(scene);
    }

    cout<<scenes.size()<<"\n";
    
    
    // view->show();

	return 0;

}