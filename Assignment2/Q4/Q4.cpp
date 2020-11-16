#include<GL/glut.h> 
#include<bits/stdc++.h>

using namespace std;

/*
Task to handle:
    Reshaping of window;

*/

float x,y;
bool check=true;

void Init() {
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Line Drawing");
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

}

void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        check=true;
        x = mousex;
        y = 480 - mousey;
    }
    else {
        check = false;
    }
            
    glutPostRedisplay();
}

void motionfunc(int Mx, int My) {
    x = Mx;
    y = 480 - My;

    glutPostRedisplay();
}

void display(void)
{  
    glColor3f(0,0,0);
    glPointSize(5); 
    
    if(check) {
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
    }
    glFlush();    
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
    Init();  
    
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motionfunc);
    glutMainLoop();
}
