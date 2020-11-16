#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef struct Color{
    float r,g,b,o;
}Color;

Color c;

void readFile(string temp) {
    
    string line;
    ifstream file;
    file.open(temp);
    
    if(file.is_open()) {
        while( getline(file,line) ) {
            stringstream ss;
            float r,g,b,o;
            ss<<line;
            ss>>r>>g>>b>>o;
            
            c.r = r;
            c.g = g;
            c.b = b;
            c.o = o;

        }
        file.close();
    }
    else {
        cout<<"File not found";
    }

}

void display() {

    glClearColor(c.r,c.g,c.b,c.o);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnd();
    glFlush();  
}
 
int main(int argc, char** argv) {
    //Reading input from file.
    readFile("input.txt");

    glutInit(&argc, argv);
    glutCreateWindow("Q1 - Background Color set"); 
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(50, 50);

    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;
}