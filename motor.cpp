#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14159
#define WIN_WIDTH 1366
#define WIN_HEIGHT 768
#define BIKE_LENGTH 3.3f
#define ROD_RADIUS 0.05f
#define GAS_TANK 0.3f
#define NUM_SPOKES 5
#define SPOKE_ANGLE 72
#define RADIUS_WHEEL 1.0f
#define TUBE_WIDTH 0.20f
#define RIGHT_ROD 2.35f
#define RIGHT_ANGLE 33.0f
#define MIDDLE_ROD 1.8f
#define MIDDLE_ANGLE 125.0f
#define BACK_CONNECTOR 0.5f
#define LEFT_ANGLE 50.0f
#define WHEEL_OFFSET 0.11f
#define WHEEL_LEN 0.8f
#define TOP_LEN 1.0f
#define FRONT_ROD 2.5f
#define CRANK_ROD 1.9f
#define CRANK_RODS 2.5f
#define CRANK_ANGLE 0.0f
#define HANDLE_ROD 1.2f
#define FRONT_INCLINE 38.0f
#define HANDLE_LIMIT 30.0f
#define INC_STEERING 2.0f
#define INC_SPEED 0.05f
int light_value = 0; //Mencerahkan seluruh objek

GLfloat pedalAngle, speed, steering; //Deklarasi posisi pedal, kecepatan, setir

GLfloat camx,camy,camz; //Deklarasi kamera berdasarkan sumbu x, y dan z
GLfloat anglex,angley,anglez; //Deklarasi sudut berdasarkan sumbu x, y dan z

GLint skybox[6], grass, background=1000 ;
const int SKY_FRONT=0,SKY_RIGHT=1,SKY_LEFT=2,SKY_BACK=3,SKY_UP=4,SKY_DOWN=5 ;

int prevx,prevy;
GLenum Mouse; //Mengatur sudut kamera pakai mouse

int flag = 0 ;
GLfloat xpos,zpos,direction; //Deklarasi posisi dan arah sepeda
void welcome_window(); //Jendela Selamat Datang
void operations_window(); //Jendela instruksi
void ZCylinder(GLfloat radius,GLfloat length); //Untuk membuat objek silinder sumbu z
void XCylinder(GLfloat radius,GLfloat length); //Untuk membuat objek silinder sumbu x
void drawFrame(void);
void gear( GLfloat inner_radius, GLfloat outer_radius,GLfloat width,GLint teeth, GLfloat tooth_depth ); //Untuk membuat gear motor
void drawTyre(void); //Deklarasi membuat ban
void drawSeat(void); //Deklarasi membuat tempat duduk
void init(void);
void reset(void); //Mengembalikan posisi awal
GLfloat radians(GLfloat);
GLfloat angleSum(GLfloat, GLfloat);

GLfloat degrees(GLfloat a) //Membuat objek belok dengan derajat
{
    return a*180.0f/PI;
}

GLfloat radians(GLfloat a) //Menjalankan Motor
{
    return a*PI/180.0f;
}

GLfloat angleSum(GLfloat a, GLfloat b) //Membuat motor belok
{
    a += b;
    if (a < 0) return a+2*PI;
    else if (a > 2*PI) return a-2*PI;
    else return a;
}

void writeText(float x,float y, float z, char *string) //Menampilkan kecepatan motor
{

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  glColor3f(1,0,0); //Untuk memberi warna tulisan
  glClear(GL_COLOR_BUFFER_BIT ); //Untuk membersihkan layar latar belakang

  glRasterPos3f(x, y, z); //Menentukan posisi raster untuk operasi piksel
  for(int i = 0; i< (int) strlen(string); i++)
  {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]); //Menentukan jenis dan ukuran font
  }
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
}

void bitmap_output(float x, float y, float z, char *string)
{
    int len, i;
    glRasterPos3f(x,y,z);
    len = (int) strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}


void ZCylinder(GLfloat radius,GLfloat length)
{
    GLUquadricObj *cylinder;
    cylinder=gluNewQuadric();
    glPushMatrix();
    glTranslatef(0.0f,0.0f,0.0f);
    gluCylinder(cylinder,radius,radius,length,15,5);
    glPopMatrix();
}

void XCylinder(GLfloat radius,GLfloat length)
{
    glPushMatrix();
    glRotatef(90.0f,0.0f,1.0f,0.0f);
    ZCylinder(radius,length);
    glPopMatrix();
}
