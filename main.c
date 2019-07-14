#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "string.h"
#include <il.h>                                    /** DEVIL KUTUPHANESI EKLENIYOR */
#include <ilu.h>
#include <ilut.h>


char name[30];
const int genislik=1920;
const int yukseklik=1000;
int secenek, sayac;

void ekran_depo(void);
void bastan_ciz(void);                              /** GEREKLI DEGISKENLER VE FONKSIYONLAR */
void arayuz(void);

GLsizei mouseX, mouseY;
GLubyte renk[3]={0,0,0};
GLubyte depo[1920][1000][3];


void isimverme (const char* isim){

    //KAYDEDILECEK VEYA ACILACAK DOSYAYA ISIM VERME
    if (sayac==1)
    {
       printf("Kaydetemek istediginiz dosyanin isimini giriniz: ");
    }
    else if(sayac==2)
    {
       printf("Acmak istediginiz dosyanin isimini giriniz: ");
    }
    gets(isim);

 }

void ac(const char* resimDosyasi)
{

    //DOSYA ACMA
    ILuint ResimAd = 0;
    ilGenImages(1, &ResimAd);
    ilBindImage(ResimAd);
    ilLoadImage(resimDosyasi);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilEnable(IL_ORIGIN_SET);
    ilCopyPixels(0, 0, 0 , genislik, yukseklik, 1, IL_RGB, IL_UNSIGNED_BYTE, depo);
    ilBindImage(0);
    ilDeleteImage(ResimAd);

    printf("Resim acildi: %s\n", resimDosyasi);

}

void kaydet(const char* resimDosyasi)
{
    //DOSYA KAYDETME
    ILuint ResimAd = ilGenImage();
    ilBindImage(ResimAd);
    ilutGLScreen();
    ilEnable(IL_FILE_OVERWRITE);
    ilSaveImage(resimDosyasi);
    ilDeleteImage(ResimAd);

   printf("Resim Kaydedildi: %s\n", resimDosyasi);
}

void ekran_depo()
{     //EKRANIN ANLIK DURUMUNU KAYDETME
      glReadPixels(0,0, genislik, yukseklik, GL_RGB, GL_UNSIGNED_BYTE, depo);
}

void bastan_ciz()
{     //FAREYI BIRAKANA KADAR CIZMEMESINI SAGLAR
      glRasterPos2i(0, yukseklik);
      glDrawPixels(genislik, yukseklik, GL_RGB, GL_UNSIGNED_BYTE, depo);
      glFlush();
}

void ciz(int x, int y) //CIZIM YAPMA FONKSIYONLARI
{

      float deger = (x-mouseX)*(x-mouseX) + (y-mouseY)*(y-mouseY);
      float derece= sqrt(deger);                                     //DAIRE CIZMEK ICIN KULLANDIGIMIZ DEGERLER



      if (secenek!= 6 && secenek!=7 && secenek!=8 )
      {
            glClear(GL_COLOR_BUFFER_BIT);
            bastan_ciz();
      }




     switch(secenek){

          GLfloat pointsize;
          GLfloat width;

     case 1:


          pointsize=0.1;
          glPointSize(pointsize);
          glColor3f(0.9, 0.9, 0.9);       //AC VE KAYDET ÝLE ALAKALI
          glBegin(GL_POINTS);
          glVertex2i(x,y);
          glEnd();
          glFlush();




      break;

    case 2:

          glLineWidth(width);
          width=1.7;
          glutSetCursor(GLUT_CURSOR_CROSSHAIR);
          glColor3ub(renk[0], renk[1], renk[2]);
          glBegin(GL_LINE_LOOP);
          int a;                                                //DAÝRE CÝZME
          for (a=0 ; a<=360 ; a++)
          {
             float rad= a*3.14159265/180;
             glVertex2i(mouseX + cos(rad)*derece, mouseY + sin(rad)*derece);
          }
          glEnd();
          glLineWidth(1.f);
          glFlush();
          break;

      float xderece;
      float yderece;
      float xmerkez;
      float ymerkez;

    case 3:

           glLineWidth(width);
           width=1.7;
           xderece = (x-mouseX)/2;
           yderece = (y-mouseY)/2;
           xmerkez = (x+mouseX)/2;
           ymerkez = (y+mouseY)/2;
           glutSetCursor(GLUT_CURSOR_CROSSHAIR);
           glColor3ub(renk[0], renk[1], renk[2]);              //ELÝPS CIZME

           glBegin(GL_LINE_LOOP);
           int i;
           for (i=0 ; i <=360 ; i++)
           {
                 float rad= i*3.14159265/180;
                 glVertex2i(xmerkez + cos(rad)*xderece, ymerkez + sin(rad)*yderece);
           }
           glEnd();
           glLineWidth(1.f);
           glFlush();
         break;

    case 4:
            glLineWidth(width);
            width=1.7;
            glutSetCursor(GLUT_CURSOR_CROSSHAIR);
            glColor3ub(renk[0], renk[1], renk[2]);
            glBegin(GL_LINE_LOOP);
            glVertex2i(mouseX,mouseY);
            glVertex2i(mouseX,y);                       //DIKDORTGEN CIZME
            glVertex2i(x,y);
            glVertex2i(x,mouseY);
            glEnd();
            glLineWidth(1.f);
            glFlush();

      break;

    case 5:


            glLineWidth(width);
            width=1.7;
            glutSetCursor(GLUT_CURSOR_CROSSHAIR);
            glColor3ub(renk[0], renk[1], renk[2]);
            glBegin(GL_LINE_LOOP);
            glVertex2i(mouseX,mouseY);                  //UCGEN CIZME
            glVertex2i(mouseX,y);
            glVertex2i(x,y);
            glEnd();
            glLineWidth(1.f);
            glFlush();
     break;

    case 6:
            if (x<82 || y<6){
            x=85;
            y=7;
       }
          pointsize=1.6;
          glPointSize(pointsize);
          glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);        //KALEM
          glColor3ub(renk[0], renk[1], renk[2]);
          glBegin(GL_POINTS);
          glVertex2i(x,y);
          glEnd();
          glFlush();
      break;

    case 7:
           if (x<82 || y<9){
            x=85;
            y=11;
       }
          glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
          glColor3ub(renk[0], renk[1], renk[2]);
          glBegin(GL_POLYGON);
          glVertex2i(x-3.8,y-3.8);
          glVertex2i(x-3.8,y+3.8);                         //FIRCA
          glVertex2i(x+3.8,y+3.8);
          glVertex2i(x+3.8,y-3.8);
          glEnd();
          glFlush();
      break;

    case 8:

           if (x<89 || y<15){
            x=92;
            y=17;
           }
          glutSetCursor(GLUT_CURSOR_CROSSHAIR);
          glColor3ub(255,255,255);
          glBegin(GL_POLYGON);
          glVertex2i(x-10,y-10);                           //SILGI
          glVertex2i(x-10,y+10);
          glVertex2i(x+10,y+10);
          glVertex2i(x+10,y-10);
          glEnd();
          glFlush();
      break;


    case 9:


          glLineWidth(width);
          width=1.7;
          glutSetCursor(GLUT_CURSOR_CROSSHAIR);
          glBegin(GL_LINES);
          glColor3ub(renk[0], renk[1], renk[2]);
          glVertex2i(mouseX, mouseY);                   //CIZGI
          glVertex2i(x, y);
          glEnd();
          glLineWidth(1.f);
          glFlush();


          break;
        }
}

void mouse(int btn, int belirt, int x, int y)  //FARENIN KONUMUNU ALARAK CIZ FONKSIYONUNA AKTARAN FONKIYON
{

      if(btn==GLUT_LEFT_BUTTON && belirt==GLUT_DOWN)
      {
            mouseX=x;
            mouseY=y;


            if (x>5 && x<50 && y>5 && y<70)
                  secenek=9;
            if (x>5 && x<74 && y>75 && y<140)
                  secenek=2;
            if (x>5 && x<74 && y>145 && y<210)
                  secenek=3;
            if (x>5 && x<74 && y>215 && y<280)
                  secenek=4;
            if (x>5 && x<74 && y>285 && y<350)
                  secenek=5;
            if (x>5 && x<74 && y>355 && y<420)
                  secenek=6;
            if (x>5 && x<74 && y>425 && y<490)
                  secenek=7;
            if (x>5 && x<74 && y>495 && y<560)
                  secenek=8;

            if (x>5 && x<74 && y>565&& y<770)
            {
                      glReadPixels(x,yukseklik-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,renk);

            }

            if(x>5 && x<74 && y>790 && y<855)
            {
                     arayuz();
                     secenek=1;
            }
             if(x>5 && x<74 && y>860 && y<925)
            {
                    secenek=1;
                    sayac=1;
                    isimverme(name);
                    kaydet(name);


            }
            if(x>5 && x<74 && y>930 && y<995)
            {
                    secenek=1;
                    sayac=2;
                    isimverme(name);
                    ac(name);

            }
            if (x>5 && x<37.5 && y>775 && y<790){   //RENK PALETÝ

                    glColor3ub(0,0,0);
                    glBegin(GL_LINE_LOOP);
                    glVertex2i(5,564);
                    glVertex2i(5,771);
                    glVertex2i(74,770);
                    glVertex2i(74,564);
                    glEnd();
                    glFlush();


                    glBegin(GL_POLYGON);
                    glColor3ub(255,0,0);
                    glVertex2i(5,564);
                    glColor3ub(0,255,0);
                    glVertex2i(5,770);
                    glColor3ub(0,0,255);
                    glVertex2i(73,770);
                    glColor3ub(0,0,0);
                    glVertex2i(73,564);
                    glEnd();
                    glFlush();

            }
            if (x>42.5 && x<74 && y>775 && y<790){  //RENK PALETÝ

            glBegin(GL_POLYGON);
                    glColor3f(0.9,0.9,0.9);
                    glVertex2i(4,563);
                    glVertex2i(4,772);
                    glVertex2i(75,772);
                    glVertex2i(75,563);
                    glEnd();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 565);
                    glVertex2i(5, 590);
                    glVertex2i(37.5, 590);
                    glVertex2i(37.5, 565);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(255, 255, 0);
                    glVertex2i(5.93, 565.5);
                    glVertex2i(5.93, 589);
                    glVertex2i(36.95, 589);
                    glVertex2i(36.95, 565.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.5, 565);
                    glVertex2i(42.5, 590);
                    glVertex2i(74, 590);
                    glVertex2i(74, 565);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(0, 255, 0);
                    glVertex2i(43.4, 565.5);
                    glVertex2i(43.4, 589);
                    glVertex2i(73.5, 589);
                    glVertex2i(73.5, 565.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 595);
                    glVertex2i(5, 620);
                    glVertex2i(37.5, 620);
                    glVertex2i(37.5, 595);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(0, 0, 255);
                    glVertex2i(5.93, 595.5);
                    glVertex2i(5.93, 619);
                    glVertex2i(36.95, 619);
                    glVertex2i(36.95, 595.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.5, 595);
                    glVertex2i(42.5, 620);
                    glVertex2i(74, 620);
                    glVertex2i(74, 595);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(255, 0, 0);
                    glVertex2i(42.7, 595.5);
                    glVertex2i(42.7, 619);
                    glVertex2i(73.5, 619);
                    glVertex2i(73.5, 595.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 625);
                    glVertex2i(5, 650);
                    glVertex2i(37.5, 650);
                    glVertex2i(37.5, 625);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(255, 128, 0);
                    glVertex2i(5.93, 625.5);
                    glVertex2i(5.93, 649);
                    glVertex2i(36.95, 649);
                    glVertex2i(36.95, 625.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.5, 625);
                    glVertex2i(42.5, 650);
                    glVertex2i(74, 650);
                    glVertex2i(74, 625);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(0, 255, 255);
                    glVertex2i(43.4, 625.5);
                    glVertex2i(43.4, 649);
                    glVertex2i(73.5, 649);
                    glVertex2i(73.5, 625.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 655);
                    glVertex2i(5, 680);
                    glVertex2i(37.5, 680);
                    glVertex2i(37.5, 655);
                    glEnd();
            glBegin(GL_POLYGON);
                    glColor3ub(128, 0, 255);
                    glVertex2i(5.93, 655.5);
                    glVertex2i(5.93, 679);
                    glVertex2i(36.95, 679);
                    glVertex2i(36.95, 655.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.5, 655);
                    glVertex2i(42.5, 680);
                    glVertex2i(74, 680);
                    glVertex2i(74, 655);
                    glEnd();
            glBegin(GL_POLYGON);
                    glColor3ub(255, 0, 255);
                    glVertex2i(42.7, 655.5);
                    glVertex2i(42.7, 679);
                    glVertex2i(73.5, 679);
                    glVertex2i(73.5, 655.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 685);
                    glVertex2i(5, 710);
                    glVertex2i(37.5, 710);
                    glVertex2i(37.5, 685);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(165, 42, 42);
                    glVertex2i(5.93, 685.5);
                    glVertex2i(5.93, 709);
                    glVertex2i(36.95, 709);
                    glVertex2i(36.95, 685.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.5, 685);
                    glVertex2i(42.5, 710);
                    glVertex2i(74, 710);
                    glVertex2i(74, 685);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(255, 182, 193);
                    glVertex2i(42.8, 685.5);
                    glVertex2i(42.8, 709);
                    glVertex2i(73.5, 709);
                    glVertex2i(73.5, 685.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 715);
                    glVertex2i(5, 740);
                    glVertex2i(37.5, 740);
                    glVertex2i(37.5, 715);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(255, 222, 173);
                    glVertex2i(5.93, 715.5);
                    glVertex2i(5.93, 739);
                    glVertex2i(36.95, 739);
                    glVertex2i(36.95, 715.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.5, 715);
                    glVertex2i(42.5, 740);
                    glVertex2i(74, 740);
                    glVertex2i(74, 715);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(0, 100, 0);
                    glVertex2i(42.7, 715.5);
                    glVertex2i(42.7, 739);
                    glVertex2i(73.5, 739);
                    glVertex2i(73.5, 715.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 745);
                    glVertex2i(5, 770);
                    glVertex2i(37.5, 770);
                    glVertex2i(37.5, 745);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(128, 128, 128);
                    glVertex2i(5.93, 745.5);
                    glVertex2i(5.93, 769);
                    glVertex2i(36.95, 769);
                    glVertex2i(36.95, 745.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.5, 745);
                    glVertex2i(42.5, 770);
                    glVertex2i(74, 770);
                    glVertex2i(74, 745);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.8, 745.5);
                    glVertex2i(42.8, 769);
                    glVertex2i(73.5, 769);
                    glVertex2i(73.5, 745.5);
                    glEnd();
                    glFlush();


            }
      }

     if(btn==GLUT_LEFT_BUTTON && belirt==GLUT_UP  )
      {
         ekran_depo();
      }
}
void arayuz() //PROGRAM ARAYUZUNU CIZEN FONKSIYONLAR
{
                glClearColor(0.9,0.9,0.9,1.0);
                glClear (GL_COLOR_BUFFER_BIT);
                glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 5);
                    glVertex2i(5, 70);
                    glVertex2i(74, 70);
                    glVertex2i(74, 5);
                glEnd();
                glBegin(GL_LINE_LOOP);
                    glColor3ub(255, 0, 0);
                    glVertex2i(66, 66);
                    glVertex2i(10, 10);
                glEnd();
                glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 75);
                    glVertex2i(5, 140);
                    glVertex2i(74, 140);
                    glVertex2i(74, 75);
                glEnd();
                glColor3f(255.0f, 0.0f, 0.0f);


            int i;
            float deger = 600;
            float yaricap = sqrt(deger);
            glBegin(GL_LINE_LOOP);
            for (i=0; i <= 360; i++)
            {
               float derece = i*3.14159/180;
               glVertex2i(40 + cos(derece)*yaricap,110+ sin(derece)*yaricap);
            }
            glEnd();

               glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 145);
                    glVertex2i(5, 210);
                    glVertex2i(74, 210);
                    glVertex2i(74, 145);
                glEnd();
              glBegin(GL_LINE_LOOP);

                     glColor3f(255.0f, 0.0f, 0.0f);
                        for (i =0; i <= 360; i++)
                        {
                           float derece = i*3.14159/180;
                           glVertex2i(  39+cos(derece)*24,25 + 153+sin(derece)*18);
                        }
                glEnd();
                glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 215);
                    glVertex2i(5, 280);
                    glVertex2i(74, 280);
                    glVertex2i(74, 215);
                glEnd();

               glColor3ub(255, 0, 0);
               glRasterPos3f(18,385,0);
               yazi_yaz("Kalem");
               glRasterPos3f(15,400,0);
               yazi_yaz("Cizimi");

               glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 285);
                    glVertex2i(5, 350);
                    glVertex2i(74, 350);
                    glVertex2i(74, 285);
                glEnd();


              glColor3ub(255, 0, 0);
                glRasterPos3f(18,530,0);
               yazi_yaz("Silgi");
              glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 355);
                    glVertex2i(5, 420);
                    glVertex2i(74, 420);
                    glVertex2i(74, 355);
                glEnd();



                glColor3ub(255,0,0);
                glBegin(GL_LINE_LOOP);
                glVertex2i(22,227);
                glVertex2i(22,270);
                glVertex2i(56,270);
                glVertex2i(56,227);
                glEnd();
                glFlush();
                glDisable(GL_LINE_STIPPLE);

             glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5,425);
                    glVertex2i(5,490);
                    glVertex2i(74,490);
                    glVertex2i(74,425);
                glEnd();
                glColor3ub(255, 0, 0);
                glRasterPos3f(18,460,0);
                yazi_yaz("Firca");

                 glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5,495);
                    glVertex2i(5,560);
                    glVertex2i(74,560);
                    glVertex2i(74,495);
                glEnd();

                glBegin(GL_LINE_LOOP);
                    glColor3ub(255, 0, 0);
                    glVertex2i(39, 295);
                    glVertex2i(63, 340);
                    glVertex2i(15, 340);
                glEnd();
                 glBegin(GL_POLYGON);
                    glColor3f(0.9,0.9,0.9);
                    glVertex2i(4,563);
                    glVertex2i(4,772);
                    glVertex2i(75,772);
                    glVertex2i(75,563);
                    glEnd();
                    glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 565);
                    glVertex2i(5, 590);
                    glVertex2i(37.5, 590);
                    glVertex2i(37.5, 565);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(255, 255, 0);
                    glVertex2i(5.93, 565.5);
                    glVertex2i(5.93, 589);
                    glVertex2i(36.95, 589);
                    glVertex2i(36.95, 565.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.5, 565);
                    glVertex2i(42.5, 590);
                    glVertex2i(74, 590);
                    glVertex2i(74, 565);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(0, 255, 0);
                    glVertex2i(43.4, 565.5);
                    glVertex2i(43.4, 589);
                    glVertex2i(73.5, 589);
                    glVertex2i(73.5, 565.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 595);
                    glVertex2i(5, 620);
                    glVertex2i(37.5, 620);
                    glVertex2i(37.5, 595);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(0, 0, 255);
                    glVertex2i(5.93, 595.5);
                    glVertex2i(5.93, 619);
                    glVertex2i(36.95, 619);
                    glVertex2i(36.95, 595.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.5, 595);
                    glVertex2i(42.5, 620);
                    glVertex2i(74, 620);
                    glVertex2i(74, 595);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(255, 0, 0);
                    glVertex2i(42.7, 595.5);
                    glVertex2i(42.7, 619);
                    glVertex2i(73.5, 619);
                    glVertex2i(73.5, 595.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 625);
                    glVertex2i(5, 650);
                    glVertex2i(37.5, 650);
                    glVertex2i(37.5, 625);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(255, 128, 0);
                    glVertex2i(5.93, 625.5);
                    glVertex2i(5.93, 649);
                    glVertex2i(36.95, 649);
                    glVertex2i(36.95, 625.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.5, 625);
                    glVertex2i(42.5, 650);
                    glVertex2i(74, 650);
                    glVertex2i(74, 625);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(0, 255, 255);
                    glVertex2i(43.4, 625.5);
                    glVertex2i(43.4, 649);
                    glVertex2i(73.5, 649);
                    glVertex2i(73.5, 625.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 655);
                    glVertex2i(5, 680);
                    glVertex2i(37.5, 680);
                    glVertex2i(37.5, 655);
                    glEnd();
            glBegin(GL_POLYGON);
                    glColor3ub(128, 0, 255);
                    glVertex2i(5.93, 655.5);
                    glVertex2i(5.93, 679);
                    glVertex2i(36.95, 679);
                    glVertex2i(36.95, 655.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.5, 655);
                    glVertex2i(42.5, 680);
                    glVertex2i(74, 680);
                    glVertex2i(74, 655);
                    glEnd();
            glBegin(GL_POLYGON);
                    glColor3ub(255, 0, 255);
                    glVertex2i(42.7, 655.5);
                    glVertex2i(42.7, 679);
                    glVertex2i(73.5, 679);
                    glVertex2i(73.5, 655.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 685);
                    glVertex2i(5, 710);
                    glVertex2i(37.5, 710);
                    glVertex2i(37.5, 685);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(165, 42, 42);
                    glVertex2i(5.93, 685.5);
                    glVertex2i(5.93, 709);
                    glVertex2i(36.95, 709);
                    glVertex2i(36.95, 685.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.5, 685);
                    glVertex2i(42.5, 710);
                    glVertex2i(74, 710);
                    glVertex2i(74, 685);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(255, 182, 193);
                    glVertex2i(42.8, 685.5);
                    glVertex2i(42.8, 709);
                    glVertex2i(73.5, 709);
                    glVertex2i(73.5, 685.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 715);
                    glVertex2i(5, 740);
                    glVertex2i(37.5, 740);
                    glVertex2i(37.5, 715);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(255, 222, 173);
                    glVertex2i(5.93, 715.5);
                    glVertex2i(5.93, 739);
                    glVertex2i(36.95, 739);
                    glVertex2i(36.95, 715.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.5, 715);
                    glVertex2i(42.5, 740);
                    glVertex2i(74, 740);
                    glVertex2i(74, 715);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(0, 100, 0);
                    glVertex2i(42.7, 715.5);
                    glVertex2i(42.7, 739);
                    glVertex2i(73.5, 739);
                    glVertex2i(73.5, 715.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 745);
                    glVertex2i(5, 770);
                    glVertex2i(37.5, 770);
                    glVertex2i(37.5, 745);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(128, 128, 128);
                    glVertex2i(5.93, 745.5);
                    glVertex2i(5.93, 769);
                    glVertex2i(36.95, 769);
                    glVertex2i(36.95, 745.5);
                    glEnd();
                    glFlush();
            glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.5, 745);
                    glVertex2i(42.5, 770);
                    glVertex2i(74, 770);
                    glVertex2i(74, 745);
                    glEnd();
                    glFlush();
            glBegin(GL_POLYGON);
                    glColor3ub(0, 0, 0);
                    glVertex2i(42.8, 745.5);
                    glVertex2i(42.8, 769);
                    glVertex2i(73.5, 769);
                    glVertex2i(73.5, 745.5);
                    glEnd();
                    glFlush();

            glBegin(GL_LINE_LOOP);
                    glColor3ub(0,0,0);
                    glVertex2i(5,775);
                    glVertex2i(5,790);
                    glVertex2i(37.5,790);
                    glVertex2i(37.5,775);
                    glEnd();

            glBegin(GL_LINE_LOOP);
                    glColor3ub(0,0,0);
                    glVertex2i(42.5,775);
                    glVertex2i(42.5,790);
                    glVertex2i(74,790);
                    glVertex2i(74,775);
                    glEnd();
            glColor3ub(0, 0, 0);
                glRasterPos3f(5,782,0);
                yazi_yaz2("  ...  ");

                   glBegin(GL_LINE_LOOP);
                   glColor3ub(0,0,0);
                   glVertex2i(52,782.5);
                   glVertex2i(70,782.5);
                   glEnd();

                   glBegin(GL_TRIANGLES);
                   glColor3ub(0,0,0);
                   glVertex2i(44,782.5);
                   glVertex2i(52,778.5);
                   glVertex2i(52,786.5);
                   glEnd();

                  glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 855);
                    glVertex2i(5, 795);
                    glVertex2i(74, 795);
                    glVertex2i(74, 855);
                glEnd();

                glColor3ub(0, 0, 255);
                glRasterPos3f(14,829.5,0);
                yazi_yaz(" Yeni ");

                glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 925);
                    glVertex2i(5, 860);
                    glVertex2i(74, 860);
                    glVertex2i(74, 925);
                glEnd();
                glColor3ub(0, 0, 255);
                glRasterPos3f(14,895,0);
                yazi_yaz("Kaydet");

                glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(5, 995);
                    glVertex2i(5, 930);
                    glVertex2i(74, 930);
                    glVertex2i(74, 995);
                glEnd();
                glColor3ub(0, 0, 255);
                glRasterPos3f(30,965,0);
                yazi_yaz("Ac");

               glBegin(GL_LINE_LOOP);
                    glColor3ub(0, 0, 0);
                    glVertex2i(79, 5);
                    glVertex2i(79, 995);
                    glVertex2i(1911, 995);
                    glVertex2i(1911, 5);
                glEnd();

                glBegin(GL_POLYGON);
                    glColor3ub(255, 255, 255);
                    glVertex2i(80, 6);
                    glVertex2i(80, 994);
                    glVertex2i(1910, 994);
                    glVertex2i(1910, 6);
                glEnd();


                ekran_depo();
                glFlush();
            }

void yazi_yaz(char *yazi) //EKRANA YAZI YAZMA FONKSIYONU
{
 char* harf;
 for(harf=yazi; *harf != '\0'; harf++)
   {
       glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*harf);
   }
}
void yazi_yaz2(char *yazi)//EKRANA YAZI YAZMA FONKSIYONU KALIN FONT
{
 char* harf;
 for(harf=yazi; *harf != '\0'; harf++)
   {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*harf);
   }
}
int main(int argc, char** argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1920,1000);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Paint");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,1920,1000,0,0,1);
    glutDisplayFunc(arayuz);
    glutMouseFunc(mouse);
    glutMotionFunc(ciz);
    ilInit();
    iluInit();
    ilutRenderer(ILUT_OPENGL);
    glutMainLoop();

    return 0;
}
