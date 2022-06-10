/*=====================================
UENF-CCT-LCMAT-Ciência da Computação
Aluno: Guilherme Oliveira M. Tavares
Data: 10/06/2022
Disciplina: Computação Gráfica
Professor: Luis Antonio Rivera Escriba
Trabalho 03 - Partículas
=======================================*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include <GL/glut.h>

#include "global.h"
#include "transformation.h"
#include "matrix.h"
#include "particle.h"
#include "surface.h"
#include "window.h"

int main(int argc, char** argv)
{
  srand(time(NULL));
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_RGBA);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("Particulas");

  init();

  glutReshapeFunc(reshape);
  glutSpecialFunc(keyboard);
  glutMotionFunc(motion);
  glutMouseFunc(mouse);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  createGLUTMenus();

  glutMainLoop();
  return 0;
}

