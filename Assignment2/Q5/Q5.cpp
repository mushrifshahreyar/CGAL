#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

typedef struct Point_2{
    float x,y,z;
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
            ss>>temp.x>>temp.y>>temp.z;
            cout<<temp.x<<" "<<temp.y<<" "<<temp.z<<endl;
            points.push_back(temp);
        }
        file.close();
    }
    else {
        cout<<"File not found";
    }

}

void display() {

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for(int i=0;i<3;++i) {
        glBegin(GL_QUADS);

        if(i == 0) {
            glColor3f(1,0,0);
        }
        if(i == 1) {
            glColor3f(0,1,0);
        }
        if(i == 2) {
            glColor3f(0,0,1);
        }

        for(int j=i*4;j< (i*4)+4 ;++j) {

            glVertex3f(points[j].x, points[j].y, points[j].z);
        }
        glEnd();
    }
    // glBegin(GL_QUADS);
    // glColor3f(1,0,0);
    // glVertex3f(-0.5, 0.6, -0.8);
    // glVertex3f(-0.2, 0.9, -0.8);
    // glVertex3f(0.8, -0.1, 0.8);
    // glVertex3f(0.5, -0.4, 0.8);
    // glEnd();
    // glBegin(GL_QUADS);
    // glColor3f(0,1,0);
    // glVertex3f(0.0, 0.8, 0.8);
    // glVertex3f(0.3, 0.5, 0.8);
    // glVertex3f(-0.7, -0.5, -0.8);
    // glVertex3f(-1.0, -0.2, -0.8);
    // glEnd();
    // glBegin(GL_QUADS);
    // glColor3f(0,0,1);
    // glVertex3f(0.6, 0, -0.8);
    // glVertex3f(0.6, -0.3, -0.8);
    // glVertex3f(-0.9, -0.3, 0.8);
    // glVertex3f(-0.9, 0, 0.8);
    // glEnd();
    
    glFlush();  
}
 
int main(int argc, char** argv) {
    //Reading input from file.
    readFile("input.txt");
    
    glutInit(&argc, argv);
    glutCreateWindow("Q1 - Background Color set"); 
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(50, 50);
    glOrtho(-1.0, 1.0, -1.0, 1.0,-1.0,1.0);
    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;
}