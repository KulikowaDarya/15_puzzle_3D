#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
#include <GLUT/GLUT.h>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<random>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include "libs/stb_image.h"
#include "libs/Board.hpp"
using namespace std;

Board board = Board();

void LoadTexture(GLuint tex, const char * filename) {
    glEnable(GL_TEXTURE_2D);
        int width, height, channels;
        unsigned char *image = stbi_load(filename, &width, &height, &channels, 4);

        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        gluBuild2DMipmaps(GL_TEXTURE_2D, channels, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        stbi_image_free(image);
    glDisable(GL_TEXTURE_2D);
}

void Init(void) {
    glClearColor (0.3, 0.3, 0.3, 0.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    string path = "images/";
    int i = 1;
    for (const auto & entry : filesystem::directory_iterator(path)) {
        LoadTexture(i++, entry.path().c_str());
    }
}

void SpecialKeys(int key, int x, int y) {
    const int delta=10;
    if (key == GLUT_KEY_DOWN)
        board.ChangeRotateX(delta);
    else if (key == GLUT_KEY_UP)
        board.ChangeRotateX(-delta);
    else if (key == GLUT_KEY_RIGHT)
        board.ChangeRotateZ(-delta);
    else if (key == GLUT_KEY_LEFT)
        board.ChangeRotateZ(delta);
    glutPostRedisplay();
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    {
        glTranslatef(0, 0, -10);
        GLfloat position[] = {0.0, 0.0, 0.0, 0.0};
        glLightfv(GL_LIGHT0, GL_POSITION, position);
    }
    glPopMatrix();
    board.Draw();
    glFlush();
    glutSwapBuffers();
}

void Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5 * (float)w / (float)h, 0.5 * (float)w / (float)h, -0.5, 0.5, 1, 1e9);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("15 puzzle");
    Init();
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutMainLoop();
  return 0;
}