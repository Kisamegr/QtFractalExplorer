#ifndef OPENGLFRACTALS_H
#define OPENGLFRACTALS_H

#include "mypoint2d.h"
#include <QtCore>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLContext>
#include <math.h>


class OpenGLFractals
{
public:

    GLbyte **colors;
    GLbyte *pixels;

    int pixelCount;


    OpenGLFractals() {
        pixels = NULL;
        colors = new GLbyte*[1000];

        qDebug() << "INITI";

        int c=0, cStart = 10, cEnd = 110, cStep = 10;
        double r,g,b;

        for (r=cStart; r<cEnd; r+=cStep) {
            for (g=cStart; g<cEnd; g+=cStep) {
                for (b=cStart; b<cEnd; b+=cStep) {
                    colors[c] = new GLbyte[3];
                    colors[c][0] = r;
                    colors[c][1] = g;
                    colors[c][2] = b;
                    c++;

                }
            }
        }

        qDebug() << c;
    }

    ~OpenGLFractals() {
        for(int c=0;c<1000;c++)
            delete colors[c];
        delete colors;
    }

    void DrawBarnsleyFern(int WINDOW_WIDTH,int iterations) {



        glClear(GL_COLOR_BUFFER_BIT);

        glDisable(GL_DEPTH_TEST);

        glBegin(GL_POINTS);

        double r;
        MyPoint2D q(0,0),p;
        float n1=100000;
        float n2=500000;

        glVertex2d(q.getX(), q.getY());


        for (int i = 0; i < iterations; i++)
        {
            r = ((double)rand() / (RAND_MAX));

            if (r < 0.01) {
                p.set(0, 0.16*q.getY());
            }
            else if (r < 0.86) {
                p.set(0.85*q.getX() + 0.04*q.getY(), -0.04 *q.getX() + 0.85*q.getY() + 1.6);

            }
            else if (r < 0.93) {
                p.set(0.2*q.getX() - 0.26*q.getY(), 0.23*q.getX() + 0.22*q.getY() + 1.6);

            }
            else {
                p.set(-0.15*q.getX() + 0.28*q.getY(), 0.26*q.getX() + 0.24*q.getY() + 0.44);

            }
            float x = p.getX() * 50+ WINDOW_WIDTH/2;
            float y = p.getY()* 50;

            /*float c = WINDOW_WIDTH*x + y;

            qDebug() << c;

            if (c < n1)
                glColor3f(0.3,0.1,0.2);
            else if (c < n2)
                glColor3f(0.3,1,0.3);
            else
                glColor3f(0.2,0.5,0.2);*/

            glVertex2d(x, y);

            //cout << p.getX() << " - " << p.getY() << "    " << r << endl;

            q.set(p.getX(), p.getY());


        }

        glEnd();
    }

    void DrawSnowflake(int WINDOW_WIDTH, int WINDOW_HEIGHT, int iterations, int N) {
        glClear(GL_COLOR_BUFFER_BIT);

        int k, R=200;
        MyPoint2D q, p, v, sv;
        MyPoint2D *vertices = new MyPoint2D[N];
        MyPoint2D center(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

        float theta = 360.0 / N;

        //cout << "THETA " << theta << endl;

        for (int i = 0; i < N; i++)
        {
            vertices[i].set(R * cos(theta * i *M_PI / 180) + center.getX(), R * sin(theta*i*M_PI / 180) + center.getY());
        }


        q.setX(rand() % (R * 2) + center.getX() - R);
        q.setY(rand() % (R * 2) + center.getY() - R);

        glDisable(GL_DEPTH_TEST);

        glBegin(GL_POINTS);
        for (int i = 0; i < N; i++)
        {
            glVertex2d(vertices[i].getX(), vertices[i].getY());
            //cout << vertices[i].getX() << " - " << vertices[i].getY() << endl;
        }

        for (int i = 0; i < iterations; i++)
        {

            k = rand() % N;

            v.set(vertices[k].getX() - q.getX(), vertices[k].getY() - q.getY());

            sv.set(v.getX() * 2.0 / 3.0, v.getY() * 2.0 / 3.0);

            p.set(q.getX() + sv.getX(), q.getY() + sv.getY());

            glVertex2d(p.getX(), p.getY());

            q.set(p.getX(), p.getY());


        }

        glEnd();
    }

    void DrawMandelbrot(int WINDOW_WIDTH, int WINDOW_HEIGHT, int iterations, float scale, float offsetX, float offsetY) {



        //qDebug() << iterations;
        glClear(GL_COLOR_BUFFER_BIT);

        qDebug() << "Drawing Mandel";

        if(pixels!=NULL) {
            delete pixels;
        }
        pixelCount = WINDOW_WIDTH*WINDOW_HEIGHT;
        pixels = new GLbyte[pixelCount*3];

        //qDebug() << pixelCount;

        float x0, y0, x, y, xtemp;
        float yStart=-1*scale, yEnd=1.1*scale, xStart=-2.5*scale, xEnd=1.1*scale;
        float x0step = (xEnd - xStart)/WINDOW_WIDTH;
        float y0step = (yEnd - yStart)/WINDOW_HEIGHT;
        float xOff = x0step*offsetX/ (sqrt(scale)), yOff = y0step*offsetY/ (sqrt(scale));
        int i, pixelIndex=0;

        qDebug() << scale ;
        qDebug() << xOff << yOff;

        for(y0 = yStart+yOff; y0 < yEnd+yOff - y0step/2; y0 += y0step) {

            //qDebug() << y0;
            for(x0 = xStart+xOff; x0 < xEnd+xOff - x0step/2; x0 += x0step){
                x = 0;
                y = 0;
                i = 0;



                /*
                * (x*x) + (y*y) < (2*2) is the 2nd bailout condition ie
                * the mandelbrot set is always within a radius of 2.
                */
                while(((x*x) + (y*y) < (2*2)) && i < iterations){
                   xtemp = (x*x) - (y*y) + x0;
                   y = (2*x*y) + y0;

                   x = xtemp;
                   i++;
                }

                //qDebug() << i;

                if(i >= iterations-1){
                /*
                * setting color pixel to Mandelbrot set coordinate
                *to black.
                */
                    pixels[pixelIndex] = 0;
                    pixels[pixelIndex+1] = 0;
                    pixels[pixelIndex+2] = 0;

                }else{
                /*
                * setting color pixel to the reset of the coordinate by the
                * pattern of no of iteration before bailout.
                */
                    pixels[pixelIndex] = colors[i][0];
                    pixels[pixelIndex+1] = colors[i][1];
                    pixels[pixelIndex+2] = colors[i][2];

                }

                pixelIndex+=3;

            }
        }

        qDebug() << "Finished";


        //glPointSize(0.7/scale);
        glDisable(GL_DEPTH_TEST);



        glBegin(GL_POINTS);
        for (int i = 0; i < pixelCount*3; i+=3)
        {
            glColor3b(pixels[i],pixels[i+1],pixels[i+2]);
            glVertex2d((i/3)%WINDOW_WIDTH,(i/3)/WINDOW_WIDTH);
        }

        glEnd();



        //glBindTexture(GL_TEXTURE_2D, 13);
        //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        //glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);




        /*glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glGenTextures(1, &textureName);   // generate a texture handler (mandatory in openGL 3.0)
        glBindTexture(GL_TEXTURE_2D, textureName); // tell openGL that we are using the texture

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, WINDOW_WIDTH, WINDOW_HEIGHT, 0,GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)pixels); // send the texture data



        glEnable(GL_TEXTURE_2D); // you should use shader, but for an example fixed pipeline is ok ;)

        glBindTexture(GL_TEXTURE_2D, textureName);



        glBegin (GL_QUADS);
        glTexCoord2f (0.0, 0.0);
        glVertex3f (0.0, 0.0, 0.0);
        glTexCoord2f (1.0, 0.0);
        glVertex3f (WINDOW_WIDTH, 0.0, 0.0);
        glTexCoord2f (1.0, 1.0);
        glVertex3f (WINDOW_WIDTH, WINDOW_HEIGHT, 0.0);
        glTexCoord2f (0.0, 1.0);
        glVertex3f (0.0, WINDOW_HEIGHT, 0.0);
        glEnd ();*/
    }


};

#endif // OPENGLFRACTALS_H
