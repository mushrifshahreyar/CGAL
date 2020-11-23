#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

int width, height;
int x,y;
bool check;
int x_new,y_new;

void mouse(int button, int state, int mousex, int mousey) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    check = true;
    x_new = mousex;
    y_new = height - mousey;
    x = x_new;
    y = y_new;
  } else {
    check = false;
  }

  glutPostRedisplay();
}

void motionfunc(int Mx, int My) {
  x = x_new;
  y = y_new;
  x_new = Mx;
  y_new = height - My;

  glutPostRedisplay();
}


void display(void) {
  glColor3f(0, 0, 0);
  glLineWidth(5.0);
  if (check) {
    glBegin(GL_LINE_STRIP);
    glVertex2i(x, y);
    glVertex2i(x_new, y_new);
    glEnd();
  }
  glFlush();
}

void on_resize(int w, int h)
{

  width = w;
  height = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, width, 0.0, height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
    
  glClearColor(1,1,1,0);
  glClear(GL_COLOR_BUFFER_BIT);
  glutPostRedisplay();

}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  width = 640;
  height = 480;
  //Initialization    
  glutInitWindowSize(width, height);
  glutInitWindowPosition(10, 10);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Q4 - Mouse Drawing");
  gluOrtho2D(0.0, width, 0.0, height);
  glClearColor(1,1,1,0);
  glClear(GL_COLOR_BUFFER_BIT);
  
  //Setting functions
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMotionFunc(motionfunc);
  glutReshapeFunc(on_resize);
  glutMainLoop();
  
  return 0;
}
