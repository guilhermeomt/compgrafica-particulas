/*=====================================
UENF-CCT-LCMAT-Ciência da Computação
Aluno: Guilherme Oliveira M. Tavares
Data: 10/06/2022
Disciplina: Computação Gráfica
Professor: Luis Antonio Rivera Escriba
Trabalho 03 - Partículas
=======================================*/

#define SENS_ROT 10.0
#define SENS_OBS 10.0
#define SENS_TRANS 10.0

#define TIME_STEP 0.1

#define MAX_PARTICLES 100
#define random() ((float) rand()/ RAND_MAX)

GLfloat ASPECTO, ANGULO;
GLfloat obsX, obsY, obsZ;
GLfloat ptc_x, ptc_y, ptc_z;
GLfloat rotX, rotY;
GLfloat obsX_ini, obsY_ini, obsZ_ini;
GLfloat rotX_ini, rotY_ini;
GLfloat scaleX, scaleY, scaleZ;

int x_ini, y_ini, bot;
int originX, originY;

typedef struct {
  GLfloat pos[3];
  GLfloat vel[3];
  GLfloat ace[3];
  GLfloat mass;
  GLfloat color[3];
  GLfloat timelife;
  GLfloat transparency;
} part;

part Particles[MAX_PARTICLES][MAX_PARTICLES];

void createParticles(int i, int j) {
  GLfloat alpha, beta;
  GLfloat radius = 0.1 * random() + 0.06;
  alpha = 2 * M_PI * random();
  beta = M_PI * random();

  Particles[i][j].pos[0] = ptc_x; // posicao em x
  Particles[i][j].pos[1] = ptc_y; // posicao em y
  Particles[i][j].pos[2] = ptc_z;  // posicao em z

  Particles[i][j].vel[0] = radius * cos(alpha) * sin(beta);  // velocidade em x
  Particles[i][j].vel[1] = radius * cos(beta);               // velocidade em y
  Particles[i][j].vel[2] = radius * sin(alpha) * sin(beta);  // velocidade em z   

  Particles[i][j].ace[0] = 0.0;    // acelera em x
  Particles[i][j].ace[1] = 0.025;  // acelera em y 
  Particles[i][j].ace[2] = 0.0;    // acelera em z

  Particles[i][j].mass = 0.01 * random();  // massa da particula

  Particles[i][j].color[0] = random();        // R
  Particles[i][j].color[1] = 0.1 * random();    // G 
  Particles[i][j].color[2] = 0.01 * random();;  // B  

  Particles[i][j].timelife = 0.8 + 0.98 * random();  // define o tempo de vida da particula
  Particles[i][j].transparency = 1.0;                  // grau de transaperencia da particula
}

void initParticles() {
  int i, j;

  for (i = 0; i < MAX_PARTICLES; i++) {
    for (j = 0; i < MAX_PARTICLES; i++) {
      createParticles(i, j);
    }
  }
}

void extinguishParticles(int i, int j) {
  if (Particles[i][j].timelife < 0.001) {
    createParticles(i, j);
  }
}

void drawParticles(void) {
  int i, j;

  glDisable(GL_DEPTH_TEST);            //"Rastro"
  glEnable(GL_BLEND);                  //Habilita a transparencia
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);   //Ativa a Transparência
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    //Perspectiva    

  for (i = 0; i < MAX_PARTICLES; i++) {
    for (j = 0; j < MAX_PARTICLES; j++) {

      glColor4f(Particles[i][j].color[0], Particles[i][j].color[1], Particles[i][j].color[2], Particles[i][j].transparency);
      glPointSize(5.0);
      glPushMatrix();
      glBegin(GL_POINTS);
      glVertex3f(Particles[i][j].pos[0], Particles[i][j].pos[1], Particles[i][j].pos[2]);
      glEnd();
      glPopMatrix();

      // calculando EDO com Euler
      Particles[i][j].pos[0] += TIME_STEP * Particles[i][j].vel[0];
      Particles[i][j].pos[1] += TIME_STEP * Particles[i][j].vel[1];
      Particles[i][j].pos[2] += TIME_STEP * Particles[i][j].vel[2];

      Particles[i][j].vel[0] += TIME_STEP * Particles[i][j].ace[0];
      Particles[i][j].vel[1] += TIME_STEP * Particles[i][j].ace[1];
      Particles[i][j].vel[2] += TIME_STEP * Particles[i][j].ace[2];

      Particles[i][j].timelife -= 0.01;
      Particles[i][j].transparency -= 0.01;
      extinguishParticles(i, j);
    }
  }

  glDisable(GL_BLEND);
}
