#include <GL/glut.h>
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
    glColor3f(1,0,0);
    glPointSize(5); 
    glBegin(GL_LINES);
        for(int i=0;i<points.size();++i) {
            for(int j=0;j<points.size();++j) {
                
                glVertex2f(points[i].x, points[i].y);
                glVertex2f(points[j].x, points[j].y);
                
            }
        }
    glEnd();

    glFlush();  
}
 
int main(int argc, char** argv) {
    string path = "bin/inputs/input1.txt";
    if(argc > 1) {
        string filename(argv[1]);
        path = "bin/inputs/" + filename;
    }
    
    readFile(path);
    
    glutInit(&argc, argv);
    glutCreateWindow("Q6 - Polygon Pattern"); 
    glutInitWindowSize(640,480);
    glutInitWindowPosition(50, 50);
    gluOrtho2D(-1.0, 1.0, -1.0, 1);
    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;
}