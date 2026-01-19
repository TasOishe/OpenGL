#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include<math.h>
#include <cmath>
#include <stdlib.h>
using namespace std;

float treeAngle = 0.0f;
float buggyPosX = 0.0f;
float buggySpeed = 0.0f;

float cloudOffsetX = 0.0f;
float cloudSpeed = 0.7f;
int cloudDir = 1;//1 e left to right, -1 e right to left

bool isNight = false;

#define MAX_DROPS 800
float dropX[MAX_DROPS];
float dropY[MAX_DROPS];
int totalDrops = 0;
bool isRaining = false;



//shape templates
void rect(float a, float b, float c, float d, float e, float f, float g, float h, int re, int gr, int bl) {
	glColor3ub(re, gr, bl);
	glBegin(GL_QUADS);
	glVertex2f(a, b);
	glVertex2f(c,d);
	glVertex2f(e,f);
    glVertex2f(g,h);

	glEnd();
}
void circ(float rad, float cx, float cy, int re, int gr, int bl) {
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
        {
            glColor3ub(re, gr, bl);
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=rad;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x+cx, y+cy );
        }

	glEnd();

}

void trig(float a, float b, float c, float d, float e, float f) {
	if (isNight)
        glColor3ub(0,0,0);
    else
        glColor3ub(56,162,199);
	glBegin(GL_POLYGON);
	glVertex2f(a, b);
	glVertex2f(c,d);
	glVertex2f(e,f);

	glEnd();
}

//01 mountains
void mountains(){
    if (isNight)
        rect(-650,0,-650,80, 650,80, 650,0, 0,0,0);
    else
        rect(-650,0,-650,80, 650,80, 650,0, 56,162,199);

    trig(-650,80, -612.40424, 94.10, -562.64982, 79.82);
    trig(-607.33285, 79.827, -542.55763, 106.03, -469.69254, 79.42);
    trig(-540, 80, -460, 120, -374.80249, 78.353);
    trig(-422.82404, 79.5, -310.87131, 110.80, -184.30637, 78.74);
    trig(-244.08953, 79.75,-194.01936, 96.32, -111.88988, 79.398);
    trig(-200, 80,-131.3416, 110,-40, 80);
    trig(-66.50253, 79.398, 0.16728, 111.225,66.61828, 80.38);
    trig(20, 80,84.97491, 103.14,140, 80);
    trig(107.41154, 79.57, 176.02306, 122,300, 80);
    trig(177.21286, 80, 264.0679, 108.92, 334.26581, 80.36);
    trig(310.07331, 80.36, 335.05901, 106.14, 424.21172, 80.31);
    trig(380, 80, 440, 100,489.09702, 79.38);
    trig(449.54788, 79.69,518.14092, 114.61, 586.98392, 79.76);
    trig(560, 80,604.91101, 101.85, 650,80);
}

//02 grass
void grass(){
    if (isNight)
        glColor3ub(81,151,41);
    else
        glColor3ub(116,187,77);

    glBegin(GL_QUADS);

    glVertex2f(-650,0);
    glVertex2f(650,0);
    glVertex2f(650,-450);
    glVertex2f(-650,-450);

    glEnd();

}

//oi-03 platform
void platform(){
    if(isNight)
        glColor3ub(186,96,76);
    else
        glColor3ub(232,124,95);

    glBegin(GL_POLYGON);
    glVertex2f(-650,-450);
    glVertex2f(-650,-156.28);
    glVertex2f(-227.38,-96.28);
    glVertex2f(227.38,-96.28);
    glVertex2f(650,-155.86);
    glVertex2f(650,-450);

    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-227.38,-70);
    glVertex2f(227.38,-70);
    glVertex2f(227.38,-96.28);
    glVertex2f(-227.38,-96.28);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-31.80812, -76.02184);
    glVertex2f(0, -52.59935);
    glVertex2f(31.80812,-76.0218);
    glEnd();

}
//04 monument
void greypillarLeft(){
    if (isNight)
        glColor3ub(175,175,175);
    else
        glColor3ub(215,210,204);

    glBegin(GL_TRIANGLES);

    glVertex2f(-0.01f, 248.28f);
    glVertex2f(-31.81f, -76.02f);
    glVertex2f(0.0f, -52.6f);

    glVertex2f(-10.54f, 156.64f);
    glVertex2f(-61.95f, -76.74f);
    glVertex2f(-34.25f, -72.66f);

    glVertex2f(-23.78f, 100.88f);
    glVertex2f(-91.98f, -76.46f);
    glVertex2f(-62.87f, -73.35f);

    glVertex2f(-35.30f, 73.16f);
    glVertex2f(-122.35f, -76.56f);
    glVertex2f(-94.11f, -72.53f);

    glVertex2f(-71.87f, 13.87f);
    glVertex2f(-156.56f, -76.94f);
    glVertex2f(-124.64f, -73.56f);

    glVertex2f(-105.15f, -19.66f);
    glVertex2f(-188.03f, -77.45f);
    glVertex2f(-158.84f, -73.77f);

    glVertex2f(-166.22f, -58.66f);
    glVertex2f(-217.60f, -78.79f);
    glVertex2f(-196.20f, -77.79f);

    glColor3ub(184,178,168);
    glVertex2f(0.04202, -52.59935);
    glVertex2f(-17.23,11.81);
    glVertex2f(20.59,12);

    glEnd();
}

void greypillarRight()
{
    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f);
    greypillarLeft();
    glPopMatrix();
}


// shading of the monument
void drawLeftDarkShade()
{
    glColor3f(0.25f, 0.25f, 0.25f);

    glBegin(GL_TRIANGLES);

    glVertex2f(-0.01f, 248.28f);
    glVertex2f(-31.81f, -76.02f);
    glVertex2f(-37.25f, -75.66f);

    glVertex2f(-10.54f, 156.64f);
    glVertex2f(-61.95f, -76.74f);
    glVertex2f(-65.87f, -76.35f);

    glVertex2f(-23.78f, 100.88f);
    glVertex2f(-91.98f, -76.46f);
    glVertex2f(-97.11f, -75.53f);

    glVertex2f(-35.30f, 73.16f);
    glVertex2f(-122.35f, -76.56f);
    glVertex2f(-127.64f, -76.56f);

    glVertex2f(-71.87f, 13.87f);
    glVertex2f(-156.56f, -76.94f);
    glVertex2f(-161.84f, -76.77f);

    glVertex2f(-105.15f, -19.66f);
    glVertex2f(-188.03f, -77.45f);
    glVertex2f(-196.20f, -77.79f);

    glVertex2f(-166.22f, -58.66f);
    glVertex2f(-217.60f, -78.79f);
    glVertex2f(-207.83f, -78.79f);

    glEnd();
}


void drawRightDarkShade()
{
    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f);
    drawLeftDarkShade();
    glPopMatrix();
}

//05 lawn
void smallGrass(){
    rect(-437.5,-310.74,-317.44,-278.3,-251.5,-303.82,-376.5,-341.02, 138,160,14);
    rect(-550.56,-256.36,-439.16,-233.68,-372.32,-257.58,-492.22,-284.32, 138,160,14);
    rect(-627.12,-208.56,-525.04,-189.93,-467.51,-212.21,-580.54,-232.87 ,138,160,14);
    rect(-480,-180,-404.13,-164.6,-335.52,-185.3,-413.71,-201.4 ,138,160,14);
    rect(-343.18, -155.4,-255.8,-138.54,-183.34,-153.87,-278.02,-172.27 ,138,160,14);

    glColor3ub(138,160,14);

    glBegin(GL_TRIANGLES);

    glVertex2f(-411.3,-221.09);
    glVertex2f(-148.80383, -165.12662);
    glVertex2f(-215.9,-293.89);
    glEnd();

}


void smallGrassR()
{
    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f);
    smallGrass();
    glPopMatrix();
}

// shading of platform
void shades(){
    glColor3ub(148,58,41);
    glLineWidth(4);
    glBegin(GL_LINES);

    glVertex2f(-443.42,-309.37);
    glVertex2f(-316.97,-274.78);

    glVertex2f(-316.97,-274.78);
    glVertex2f(-247.84,-302.24);

    glVertex2f(-452.58,-311.56);
    glVertex2f(-376.67,-347.95);

    glVertex2f(-376.67,-347.95);
    glVertex2f(-239.05,-306.02);

    //2
    glVertex2f(-553.8,-255.1);
    glVertex2f(-440,-230);

    glVertex2f(-440,-230);
    glVertex2f(-368.1,-257.1);

    glVertex2f(-562.7,-256.08);
    glVertex2f(-494.04,-288.83);
    glVertex2f(-494.04,-288.83);
    glVertex2f(-359.9,-258.4);
    //3
    glVertex2f(-636.3,-206.7);
    glVertex2f(-524.7,-186.7);
    glVertex2f(-524.7,-186.7);
    glVertex2f(-464.7,-211.2);

    glVertex2f(-639.6,-207);
    glVertex2f(-581.6,-238);
    glVertex2f(-581.6,-238);
    glVertex2f(-456,-213.3);
    //4
    glVertex2f(-490.57741,-179.97612);
    glVertex2f(-414.17259,-206.20819);    glVertex2f(-414.17259,-206.20819);
    glVertex2f(-325.70845,-186.86434);    glVertex2f(-325.70845,-186.86434);
    glVertex2f(-404.18833,-163.21025);    glVertex2f(-404.18833,-163.21025);
    glVertex2f(-490.57741,-179.97612);
    //5
    glVertex2f(-376.60324,-158.33149);
    glVertex2f(-275.29304,-185.66916);
    glVertex2f(-143.89991,-160.25594);
    glVertex2f(-255.67982,-136.83745);    glVertex2f(-255.67982,-136.83745);
    glVertex2f(-376.60324,-158.33149);

    glVertex2f(-343.18378, -155.40315);
    glVertex2f(-278.02121, -172.26876);    glVertex2f(-278.02121, -172.26876);
    glVertex2f(-183.34382, -153.86992);    glVertex2f(-183.34382, -153.86992);
    glVertex2f(-343.18378, -155.40315);



    glEnd();


    ////////////////////////////mota shades
    glColor3ub(148,58,41);
    glLineWidth(8);
    glBegin(GL_LINES);
    //2
    glVertex2f(-589,-262.5);
    glVertex2f(-501.3,-305.2);
    glVertex2f(-501.3,-305.2);
    glVertex2f(-330.9,-263);
    //1
    glVertex2f(-480.2,-317.8);
    glVertex2f(-380.6,-368.06);
    glVertex2f(-380.6,-368.06);
    glVertex2f(-215.7,-316.1);

    //
    glVertex2f(-413.72647, -216.9784);
    glVertex2f(-283.97449, -188.72521);
    //
    glVertex2f(-275.29304,-185.66916);
    glVertex2f(-143.89991,-160.25594);
    //
    glVertex2f(-429.91549, -219.33222);
    glVertex2f(-650, -262.7878);

    //upor
    glVertex2f(0,-98.26);
    glVertex2f(-100,-98.26);    glVertex2f(-100,-98.26);
    glVertex2f(-209,-82);

    glVertex2f(-313.13965, -450);
    glVertex2f(-116.97899, -350);    glVertex2f(-116.97899, -350);
    glVertex2f(0, -350);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-159.22285, -101.6645);
    glVertex2f(-153.81289, -94.0004);
    glVertex2f(-153.96339, -90.13665);
    glVertex2f(-650, -163.44472);
    glVertex2f(-650, -179.58302);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-227.37652, -96.8752);
    glVertex2f(-177.989, -90.05918);
    glVertex2f(-227.32,-83.16);
    glEnd();

    rect(-70, -110,-0.50638, -110, 0.32813, -124,-69.66678, -124, 148,58,41);
    rect(-130.95591, -99.02467,-122.21895, -114.2723,-69.66678, -123.98,-70, -110, 148,58,41);




}

void shadesR()
{
    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f);
    shades();
    glPopMatrix();
}

//06 faraway bushes
void bgGrass(){
    rect(-650,0,-650,11,650,11,650,0, 66,167,91);
    circ(39,-620.7,13.43, 66,167,91);
    circ(22,-608,7.5 ,66,167,91);
    circ(23.7,-570.75,7.93 ,66,167,91);
    circ(21.4,-544,16.4 ,66,167,91);
    circ(19.5,-517.4,10.5 ,66,167,91);
    circ(25,-487.4,17.84 ,66,167,91);
    circ(23.7,-445.47,12.94 ,66,167,91);
    circ(24.6,-406.27,7.5 ,66,167,91);
    circ(22.2,-369.8,10.22 ,66,167,91);
    circ(13,-353.5,19.5 ,66,167,91);
    circ(24.5,-320.8,14.4 ,66,167,91);
    circ(20,-265.8,11.8 ,66,167,91);
    circ(21.8,-290,10.2 ,66,167,91);
    circ(20.4,-240.2,28.2 ,66,167,91);
    circ(19,-209.7,19 ,66,167,91);
    circ(21,-177.5,19 ,66,167,91);
    circ(25.8,-139.5,7.1 ,66,167,91);
    circ(39,-102.8,7.1 ,66,167,91);
    circ(21,80,11.9 ,66,167,91);
    circ(23.5,110,17.7 ,66,167,91);
    circ(21.8,145,30.3 ,66,167,91);
    circ(34,182.7,11.9 ,66,167,91);
    circ(30,234.9,14.8 ,66,167,91);
    circ(33.6,298,14.8 ,66,167,91);
    circ(28,353.9,13 ,66,167,91);/////////
    circ(26.8,380,32.2 ,66,167,91);
    circ(34,429.5,13.8 ,66,167,91);
    circ(33,483.6,11.9 ,66,167,91);
    circ(26.8,526.23,20.6 ,66,167,91);
    circ(25.2,564,30.2 ,66,167,91);
    circ(38.2,614.3,21.6 ,66,167,91);
}

//trees function
void drawtree(float x, float y, int a, int b, int c)
{
    glColor3f(0.55f, 0.27f, 0.07f);

    glBegin(GL_QUADS);
        glVertex2f(x - 8, y);
        glVertex2f(x + 8, y);
        glVertex2f(x + 8, y + 60);
        glVertex2f(x - 8, y + 60);
    glEnd();

    glPushMatrix();

    glTranslatef(x, y + 60, 0);
    glRotatef(sin(treeAngle) * 8.0f, 0, 0, 1);
    glTranslatef(-x, -(y + 60), 0);

    glColor3ub( a,  b,  c);

    for (int i = 0; i < 3; i++) {
        glBegin(GL_TRIANGLE_FAN);

        glVertex2f(x, y + 60 + i * 15);

        for (int j = 0; j <= 30; j++) {
            float theta = 2.0f * 3.1416f * j / 30;
            float dx = 18 * cos(theta);
            float dy = 18 * sin(theta);
            glVertex2f(x + dx, y + 60 + i * 15 + dy);
        }

        glEnd();
    }

    glPopMatrix();
}

//33 update for trees
void update(int value) {
    treeAngle += 0.1f;
    if (treeAngle > 2 * 3.1416f)
        treeAngle -= 2 * 3.1416f;

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

//07 swaying trees
void treeLeft(){
    drawtree(-614,-118, 0,120,0);
    drawtree(-577,-113, 0,120,0);
    drawtree(-540, -108, 0,120,0);
    drawtree(-503, -103, 0,120,0);
    drawtree(-466,  -98, 0,120,0);
    drawtree(-429,  -93, 0,120,0);
    drawtree(-392,  -88, 0,120,0);
    drawtree(-355,  -83, 0,120,0);
    drawtree(-318,  -78, 0,120,0);
    drawtree(-281,  -73, 0,120,0);
    drawtree(-244,  -68, 0,120,0);
    drawtree(-207,  -63, 0,120,0);
    drawtree(-170,  -58, 0,120,0);
    drawtree(-133, -53, 0,120,0);
    drawtree(-96,  -48, 0,120,0);

    ////////
    drawtree(-632, -142, 0, 153, 0);
    drawtree(-595, -137, 0, 153, 0);
    drawtree(-558, -132, 0, 153, 0);
    drawtree(-521, -127, 0, 153, 0);
    drawtree(-484, -122, 0, 153, 0);
    drawtree(-447, -117, 0, 153, 0);
    drawtree(-410, -112, 0, 153, 0);
    drawtree(-373, -107, 0, 153, 0);
    drawtree(-336, -102, 0, 153, 0);
    drawtree(-299, -97, 0, 153, 0);
    drawtree(-262, -92, 0, 153, 0);
    drawtree(-225, -87, 0, 153, 0);
    drawtree(-188, -82, 0, 153, 0);
    drawtree(-151, -77, 0, 153, 0);
}

void treeRight()
{
    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f);
    treeLeft();
    glPopMatrix();
}

//08 pool
void pool(){
    rect(-65.25,-140, 65.25,-140,120,-343,-120,-343, 255,255,255);
    rect(-107,-337,107,-337, 62,-145,-62,-145, 77,151,220);


}

//09 buggy
void buggy(){
    glPushMatrix();
        glTranslatef(510, -370, 0);   // approximate center og buggy
        glScalef(1.2f, 1.2f, 1.0f);   // scaled up slightly
        glTranslatef(-510, 370, 0);

    glTranslatef(buggyPosX, 0.0f, 0.0f);

    rect(493.83419, -357.42,508.73612, -357.67,507.97839, -373.3,490.80329, -373.59, 238,191,119 );
    rect(526.41637, -357.67,541.31829, -357.174,540.30799, -372.58,523.89062, -373.59, 238,191,119 );

    rect(435, -372,435, -397,588, -397,588, -372, 34,127,227);
    glColor3ub(0,0,0);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(435, -372);
    glVertex2f(435, -397);
    glVertex2f(588, -397);
    glVertex2f(588, -372);
    glEnd();

    circ(19, 462,-396, 1,1,1 );
    circ(19,561,-396, 1,1,1);
    circ(10, 462,-396, 68,68,68 );
    circ(10,561,-396, 68,68,68);

    glColor3ub(0,0,0);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(454.33465, -372.89377);
    glVertex2f(467.73937, -338.79918);
    glVertex2f(462.49404, -357.0121);
    glVertex2f(477.66998, -372.31);
    glVertex2f(565.36065, -338.94);
    glVertex2f(565.45768, -372.11);
    glEnd();

    rect(453, -328,453, -338,580, -338,580, -328, 253,193,35);
        glColor3ub(0,0,0);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(453, -328);
    glVertex2f(453, -338);
    glVertex2f(580, -338);
    glVertex2f(580, -328);
    glEnd();

glPopMatrix();

}

//34 update for buggy
void updateCar(int value)
{
    buggyPosX += buggySpeed;

    if (buggyPosX < -1100)
        buggyPosX = 650;

    glutPostRedisplay();
    glutTimerFunc(16, updateCar, 0);
}

//10 clouds
void clouds(){

    glPushMatrix();
    glTranslatef(cloudOffsetX, 0, 0);
    //a
    circ(44, -464.2,307, 230,230,230);
    circ(44, -409,310.3, 230,230,230);
    circ(44, -462,345, 230,230,230);
    circ(44, -508,314, 230,230,230);

    //b
    circ(44, -60,233, 230,230,230);
    circ(44, -107,200,230,230,230);
    circ(44, -10,197, 230,230,230);
    circ(44, -65,196, 230,230,230);

    //c
    circ(44,390.5,278, 230,230,230);
    circ(44,436,312, 230,230,230);
    circ(44, 491,273, 230,230,230);
    circ(44, 432,271,230,230,230);

    glPopMatrix();
}
//35 update for clouds
void updateClouds(int value)
{
    cloudOffsetX += cloudSpeed * cloudDir;

    if (cloudOffsetX > 800)
        cloudOffsetX = -800;
    if (cloudOffsetX < -800)
        cloudOffsetX = 800;

    glutPostRedisplay();
    glutTimerFunc(16, updateClouds, 0);
}

//11,12 sun & Moon
void sunmoon(){
    if (isNight)
        circ(62,-350,352, 191,195,204);
    else
        circ(62, 380,344, 255,232,124);
}

//13 flag
void flag(){
    if (isNight){}
    else{
        rect(-2.09308, -215.0548,45.82406, -242.819,40.898, -272.37,-2.5409, -250.43, 5,120,53);
        circ(10, 17,-244.12, 211,57,50);

        glColor3ub(180,180,185);
        glLineWidth(5);
        glBegin(GL_LINES);

        glVertex2f(-2.09308, -215.05487);
        glVertex2f(-2.09308, -374.92794);
        glEnd();
    }

}

//14 rain
void addDrop() {
    if (totalDrops < MAX_DROPS) {
        dropX[totalDrops] = -650 + rand() % 1300;
        dropY[totalDrops] = 450+ rand() % 50;
        totalDrops++;
    }
}
//36 update for rain
void updateRain(int value) {
    if (isRaining) {
        for (int i = 0; i < totalDrops; i++) {
            dropY[i] -= 25.0f + rand() % 15;

            if (dropY[i] < -450) {
                dropX[i] = -650 + rand() % 1300;
                dropY[i] = 450 + rand() % 50;
            }
        }

        for (int i=0; i<8;i++)
            addDrop();
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateRain, 0);
}
void drawRaindrops() {
    glColor3f(0.6f, 0.7f, 1.0f);
        glLineWidth(1);
    glBegin(GL_LINES);
    for (int i = 0; i < totalDrops; i++) {
        float len = 20 + rand() % 15;
        glVertex2f(dropX[i], dropY[i]);
        glVertex2f(dropX[i], dropY[i] - len);
    }
    glEnd();
}

//31 mouse int for clouds, rain
void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_RIGHT_BUTTON)
        {
            cloudDir *= -1;
        }

        if (button == GLUT_LEFT_BUTTON)
        {
            isRaining = true;
        }

        if (button == GLUT_MIDDLE_BUTTON)
        {
            isRaining = false;
            totalDrops = 0;
        }
    }
}



//32 keyboard int for buggy, day/night
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        buggySpeed -= 3.0f;
        break;

    case 'd':
        buggySpeed = 0.0f;
        break;

    case 'n':
        isNight = true;
        break;

    case 'm':
        isNight = false;
        break;
    }
    glutPostRedisplay();

}

void drawScene()
{
    if (isNight)
    glClearColor(0.05f, 0.05f, 0.2f, 1.0f);
    else
    glClearColor(0.514f, 0.780f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    mountains();
    sunmoon();
    clouds();
    bgGrass();
    grass();


    treeLeft();
    treeRight();

    platform();

    greypillarLeft();
    greypillarRight();
    drawLeftDarkShade();
    drawRightDarkShade();

    shades();
    shadesR();
    smallGrass();
    smallGrassR();

    pool();
    flag();
    buggy();
    drawRaindrops();

    glutSwapBuffers();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(1300, 900);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("National Monument");

    glutDisplayFunc(drawScene);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-650, 650, -450, 450);
    glMatrixMode(GL_MODELVIEW);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);


    glutTimerFunc(30, update, 0);// tree sway
    glutTimerFunc(16, updateCar, 0);   // car movement
    glutTimerFunc(16, updateClouds, 0);// cloud
    glutTimerFunc(0, updateRain, 0);


    glutMainLoop();
    return 0;
}
