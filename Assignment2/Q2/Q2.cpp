#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef struct Point_2{
    float x,y;
}Point_2;

vector<Point_2> points;

void readFile(string temp) {
    
    string line;
    ifstream file;
    file.open(temp);
    
    if(file.is_open()) {
        while( getline(file,line) ) {
            stringstream ss;
            ss<<line;
            Point_2 temp;
            ss>>temp.x>>temp.y;
            
            points.push_back(temp);
        }
        file.close();
    }
    else {
        cout<<"File not found";
    }

}

void display() {

    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);
    glPointSize(5);
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    glBegin(GL_POINTS);
        for(int i=0;i<points.size();++i) {
            glVertex2f(points[i].x, points[i].y);
        }
    glEnd();
    glFlush();  
}
 
int main(int argc, char** argv) {
    //Reading input from file.
    readFile("input.txt");
    
    glutInit(&argc, argv);
    glutCreateWindow("Q1 - Points Marking"); 
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(50, 50);

    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;
}