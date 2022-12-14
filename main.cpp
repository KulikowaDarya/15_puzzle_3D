#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
#include <GLUT/GLUT.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "libs/stb_image.h"
#include "libs/Game.hpp"
using namespace std;

Game game = Game();

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
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    int N = game.board.GetN() * game.board.GetM();
    N += game.menu.GetN() * game.menu.GetM();
    N += game.victory.GetN() * game.victory.GetM();
    for (int i = 1; i <= N; ++i) {
        string path = "images/" + to_string(i) + ".bmp";
        LoadTexture(i, path.c_str());
    }
}

void SpecialKeys(int key, int x, int y) {
    const int delta=10;
    if (key == GLUT_KEY_DOWN) {
        game.board.ChangeRotateX(delta);
        game.menu.ChangeRotateX(delta);
        game.victory.ChangeRotateX(delta);
    }
    else if (key == GLUT_KEY_UP) {
        game.board.ChangeRotateX(-delta);
        game.menu.ChangeRotateX(-delta);
        game.victory.ChangeRotateX(-delta);
    }
    else if (key == GLUT_KEY_RIGHT) {
        game.board.ChangeRotateZ(-delta);
        game.menu.ChangeRotateZ(-delta);
        game.victory.ChangeRotateZ(-delta);
    }
    else if (key == GLUT_KEY_LEFT) {
        game.board.ChangeRotateZ(delta);
        game.menu.ChangeRotateZ(delta);
        game.victory.ChangeRotateZ(delta);
    }
    glutPostRedisplay();
}

void BaseDisplay() {
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
    glTranslatef(0, 0, -7);
}

void Display() {
    BaseDisplay();
    if (game.Is_Show("menu")) {
        game.menu.Draw(true);
    } else if (game.Is_Show("board")) {
        int finished = game.board.Draw(true);
        if (finished == game.board.GetN() * game.board.GetM() - 1) {
            game.Switch("board", "victory");
        }
    } else if (game.Is_Show("victory")) {
        game.victory.Draw(true);
    }
    glFlush();
    glutSwapBuffers();
}

void FakeDisplay() {
    BaseDisplay();
    if (game.Is_Show("menu")) {
        game.menu.Draw(false);
    } else if (game.Is_Show("board")) {
        game.board.Draw(false);
    } else if (game.Is_Show("victory")) {
        game.victory.Draw(false);
    }
}

void OnClick(int &x, int &y) {
    FakeDisplay();
    unsigned char color[3];
    glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);
    if (game.Is_Show("menu")) {
        if (color[0] == game.NEW_GAME) {
            game.board.Restart();
            game.Switch("menu", "board");
            glutPostRedisplay();
        } else if (color[0] == game.EXIT) {
            exit(0);
        }
    } else if (game.Is_Show("board")) {
        game.board.Move(color[0]);
    } else if (game.Is_Show("victory")) {
        if (color[0] == game.RESTART) {
            game.Switch("victory", "board");
            game.board.Restart();
            glutPostRedisplay();
        } else if (color[0] == game.MENU) {
            game.Switch("victory", "menu");
            glutPostRedisplay();
        }
    }
}

void MouseKeys(int key, int state, int x, int y) {
    if (state == GLUT_DOWN && key == GLUT_LEFT_BUTTON) {
        OnClick(x, y);
    }
    glutPostRedisplay();
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
    glutMouseFunc(MouseKeys);
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutMainLoop();
  return 0;
}
