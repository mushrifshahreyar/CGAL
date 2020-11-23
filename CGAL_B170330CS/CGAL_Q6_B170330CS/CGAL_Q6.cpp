#include <CGAL/Triangle_2.h>
#include <bits/stdc++.h>
#include <cstdlib>
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
#include <qcolor.h>
#include <qpolygon.h>

using namespace CGAL;
using namespace std;

typedef Point_2< Cartesian<double> > Point;

typedef struct Vertex {
    int vnum;
    Point v;
    bool ear;
    Vertex *next, *prev;

}Vertex;

typedef struct Triangle {
    Point a;
    Point b;
    Point c;
}Triangle;

Vertex *head = NULL;

void addVertex(Point point, int vno) {
    
    Vertex *temp = new Vertex;
    
    temp->vnum = vno;
    temp->ear = false;
    temp->v = point;
    
    if(head == NULL) {
        head = temp;
        head->next = head->prev = temp;
    }
    else {
        temp->next = head;
        temp->prev = head->prev;
        head->prev = temp;
        temp->prev->next = temp;
    }
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

bool leftOn(Point a, Point b, Point c) {
    if (findArea(a, b, c) >= 0) {
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
    else {
        return ((a.y() <= c.y()) && (c.y() <= b.y())) || ((a.y() >= c.y()) && (c.y() >= b.y()));
    }
}

bool intersect(Point a, Point b, Point c, Point d) {

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

bool diagonalie(Vertex *a, Vertex *b) {
    Vertex *c, *c1;
    c = head;
    do {
        c1 = c->next;
        if((c != a) && (c1 != a) && (c != b) && (c1 != b) && intersect(a->v, b->v, c->v, c1->v)) {
            return false;
        } 
        c = c->next;
    }while(c != head);

    return true;
}

bool inCone(Vertex *a, Vertex *b) {
    Vertex *a0, *a1;

    a1 = a->prev;
    a0 = a->next;
    
    if(leftOn(a->v, a1->v, a0->v)) {
        return left(a->v, b->v, a0->v) && left( b->v, a->v, a1->v);
    }
    return !(leftOn(a->v, b->v, a1->v) && leftOn(b->v, a->v, a0->v));
}

bool diagonal(Vertex *a, Vertex *b) {
    return inCone(a, b) && inCone(b, a) && diagonalie(a, b);
}

void earInit() {
    Vertex *v0, *v1, *v2;
    v1 = head;
    do {
        v2 = v1->next;
        v0 = v1->prev;
        v1->ear = diagonal(v0, v2);
        v1 = v1->next;
    }while(v1 != head);
}


vector<Triangle> triangulate(int nVertices) {
    Vertex *v0,*v1, *v2, *v3, *v4;
    int n = nVertices;
    earInit();
    vector<Triangle> triangles;
    
    while(n>3) {
        v2 = head;
        do {
            if(v2->ear) {
                v3 = v2->next; v4 = v3->next;
                v1 = v2->prev; v0 = v1->prev;
                
                Triangle t{v2->v,v1->v,v3->v};
                triangles.push_back(t);

                v1->ear = diagonal(v0, v3);
                v3->ear = diagonal(v1, v4);

                v1->next = v3;
                v3->prev = v1;

                head = v3;

                n--;
                break;
            }
            v2 = v2->next;
        }while(v2 != head);
    }
    v2 = v3->next;

    Triangle t{v2->v, v1->v, v3->v};
    triangles.push_back(t);
    
    return triangles;
}

vector<Point> readFile(string temp) {
    
    string line;
    ifstream file;
    file.open(temp);
    vector<Point> points;
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

void createPolygon(vector<Point> points) {
    int n= points.size();
    for(int i=0;i<n;++i) {
        addVertex(points[i], i);           
    }
    Vertex *temp = head;
    do {
        cout<<temp->vnum<<" "<<temp->v.x()<<" "<<temp->v.y()<<endl;
        temp = temp->next;
    }while(temp != head);
}

void printPolygon(QGraphicsScene *scene, vector<Triangle> triangles) {
    int r=10;
    int g=10;
    int b=10;
    for(int i=0;i<triangles.size();++i) {
        QPolygon poly;
        poly.push_back(QPoint(triangles[i].a.x(), triangles[i].a.y()));
        poly.push_back(QPoint(triangles[i].b.x(), triangles[i].b.y()));
        poly.push_back(QPoint(triangles[i].c.x(), triangles[i].c.y()));
    
        QPen pen(Qt::black, 1, Qt::SolidLine);
        
        QBrush brush;
        brush.setColor(QColor(r,g,b));
        if(i%3 == 0) {
            r +=110;
            r = r % 255;
        }
        else if(i % 2 == 0) {
            b *= 65;
            b = b % 255;
        }
        else {
            g += 100;
            g = g % 255;
        }
        brush.setStyle(Qt::SolidPattern);

        QPainterPath path;
        path.addPolygon(poly);

        (*scene).addPolygon(poly,pen,brush);
    }
}

void printOutlinePolygon(QGraphicsScene *scene, vector<Point> points) {

    int n = points.size();

    for(int i=0;i<n-1;++i) {
        (*scene).addLine(points[i].x(),points[i].y(), points[i+1].x(), points[i+1].y());
    }
    (*scene).addLine(points[n-1].x(),points[n-1].y(), points[0].x(), points[0].y());

}
int main(int argc, char **argv)
{
    
    string path = "bin/inputs/input1.txt";
    if(argc > 1) {
        string filename(argv[1]);
        path = "bin/inputs/" + filename;
    }
    
    vector< Point > points = readFile(path);
    
    createPolygon(points);

    vector<Triangle> triangles = triangulate(points.size());
    
    QApplication app(argc, argv);
    
    QGraphicsScene scene;
    scene.setSceneRect(0,0, 640,320);
    int n = points.size();

    // printOutlinePolygon(&scene, points);
    
    printPolygon(&scene, triangles);
    
    QGraphicsView* view = new QGraphicsView(&scene);
    
    view->show();
    return app.exec();
}