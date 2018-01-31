#ifndef QOPENGLITEM_H
#define QOPENGLITEM_H

#include <QtCore>
#include <QQuickFramebufferObject>
#include <QQuickWindow>
#include <QOpenGLFramebufferObjectFormat>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLContext>
#include <QtQuick/QQuickItem>
#include <QOpenGLFunctions>

#include "mypoint2d.h"
#include "openglfractals.h"



class QOpenGLItem : public QQuickFramebufferObject
{

    Q_OBJECT

    Q_PROPERTY(int iterations READ iterations WRITE setIterations NOTIFY IterationsChanged)
    Q_PROPERTY(int fractalIndex READ fractalIndex WRITE setFractalIndex NOTIFY FractalIndexChanged)
    Q_PROPERTY(int windowWidth READ windowWidth WRITE setWindowWidth NOTIFY WindowChanged)
    Q_PROPERTY(int windowHeight READ windowHeight WRITE setWindowHeight NOTIFY WindowChanged)
    Q_PROPERTY(float scale READ scale WRITE setScale NOTIFY ScaleChanged)
    Q_PROPERTY(int cameraCenterX READ cameraCenterX WRITE setCameraCenterX NOTIFY CameraCenterChanged)
    Q_PROPERTY(int cameraCenterY READ cameraCenterY WRITE setCameraCenterY NOTIFY CameraCenterChanged)
    Q_PROPERTY(int snowflakeSize READ snowflakeSize WRITE setSnowflakeSize NOTIFY SnowflakeSizeChanged)
    Q_PROPERTY(QColor drawColor READ drawColor WRITE setDrawColor NOTIFY DrawColorChanged)
    Q_PROPERTY(int offSetX READ offSetX WRITE setOffSetX NOTIFY OffSetXChanged)
    Q_PROPERTY(int offSetY READ offSetY WRITE setOffSetY NOTIFY OffSetYChanged)


    class QOpenGLRenderer : public QQuickFramebufferObject::Renderer
    {
    public:
        int WINDOW_WIDTH=0, WINDOW_HEIGHT=0,ITERATIONS=0,FRACTAL_INDEX=0,SNOWFLAKE_SIZE=0,CAMERA_CENTER_X=0,CAMERA_CENTER_Y=0,OFFSET_X=0,OFFSET_Y=0;
        float SCALE=1;
        QColor DRAW_COLOR;
        QOpenGLItem *viewItem;
        OpenGLFractals *fractals;




        QOpenGLFramebufferObject *createFramebufferObject(const QSize &size)
        {
            QOpenGLFramebufferObjectFormat format;
            format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);

            format.setSamples(4);

            fractals = new OpenGLFractals();

            //qDebug() << "THIS IS CREATE";
            return new QOpenGLFramebufferObject(size, format);
        }

        void synchronize(QQuickFramebufferObject *item) {

            viewItem = static_cast<QOpenGLItem *>(item);

            ITERATIONS = viewItem->iterations();
            FRACTAL_INDEX = viewItem->fractalIndex();
            WINDOW_WIDTH = viewItem->windowWidth();
            WINDOW_HEIGHT = viewItem->windowHeight();
            SCALE = viewItem->scale();
            SNOWFLAKE_SIZE = viewItem->snowflakeSize();
            DRAW_COLOR = viewItem->drawColor();
            OFFSET_X = viewItem->offSetX();
            OFFSET_Y = viewItem->offSetY();
            update();

        }

        void render()
        {

            //qDebug() << "THIS IS RENDER";
            float CAMERA_WIDTH = WINDOW_WIDTH*SCALE;
            float CAMERA_HEIGHT = WINDOW_HEIGHT*SCALE;



            QOpenGLFunctions glFuncs(QOpenGLContext::currentContext());
            glFuncs.glUseProgram(0);




            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(CAMERA_CENTER_X, CAMERA_CENTER_X + CAMERA_WIDTH, CAMERA_CENTER_Y, CAMERA_CENTER_Y + CAMERA_HEIGHT,-10,100);
            glMatrixMode(GL_MODELVIEW);
            glClearColor(0, 0, 0, 1);
            glColor3f(DRAW_COLOR.redF(),DRAW_COLOR.greenF(),DRAW_COLOR.blueF());

            //qDebug() << DRAW_COLOR.redF() << DRAW_COLOR.greenF() << DRAW_COLOR.blueF();

            if (FRACTAL_INDEX == 0)
                fractals->DrawBarnsleyFern(WINDOW_WIDTH*SCALE, ITERATIONS);
            else if (FRACTAL_INDEX == 1)
                fractals->DrawSnowflake(WINDOW_WIDTH*SCALE, WINDOW_HEIGHT*SCALE, ITERATIONS, SNOWFLAKE_SIZE);
            else if (FRACTAL_INDEX == 2)
                fractals->DrawMandelbrot(WINDOW_WIDTH, WINDOW_HEIGHT,ITERATIONS, SCALE, OFFSET_X, OFFSET_Y);


            viewItem->window()->resetOpenGLState();

        }

    };

public:


    QOpenGLItem() {
    }



    int iterations() const {return m_iterations;}
    int fractalIndex() const {return m_fractalIndex;}
    int windowWidth() const {return m_windowWidth;}
    int windowHeight() const {return m_windowHeight;}
    float scale() const {return m_scale;}
    int cameraCenterX() const {return m_cameraCenterX;}
    int cameraCenterY() const {return m_cameraCenterY;}
    int snowflakeSize() const {return m_snowflakeSize;}
    QColor drawColor() const {return m_drawColor;}

    void setIterations(int i) {
        if(m_iterations != i) {
            m_iterations = i;
            emit IterationsChanged();
            update();
        }
    }

    void setFractalIndex(int f) {
        if(m_fractalIndex != f) {
            m_fractalIndex = f;
            emit FractalIndexChanged();
            update();
        }
    }

    void setWindowWidth(int w) {
        if(m_windowWidth != w) {
            m_windowWidth = w;

            emit WindowChanged();
            update();
        }

    }
    void setWindowHeight(int h) {
        if(m_windowHeight !=h) {
            m_windowHeight = h;

            emit WindowChanged();
            update();
        }

    }

    void setScale(float s) {
        if(m_scale != s) {
            m_scale = s;
            emit ScaleChanged();
            update();
        }
    }

    void setCameraCenterX(float x) {
        if(m_cameraCenterX != x) {
            m_cameraCenterX = x;
            emit CameraCenterChanged();
            update();
        }
    }

    void setCameraCenterY(float y) {
        if(m_cameraCenterY != y) {
            m_cameraCenterY = y;
            emit CameraCenterChanged();
            update();
        }
    }

    void setSnowflakeSize(int s) {
        if(m_snowflakeSize != s) {
            m_snowflakeSize = s;
            emit SnowflakeSizeChanged();
            update();
        }
    }

    void setDrawColor(QColor col) {
        if(m_drawColor.value() != col.value()) {
            m_drawColor = col;
            emit DrawColorChanged();
            update();
        }
    }

    QQuickFramebufferObject::Renderer *createRenderer() const
    {
        return new QOpenGLRenderer;
    }



    int offSetY() const
    {
        return m_offSetY;
    }

    int offSetX() const
    {
        return m_offSetX;
    }

public slots:
    void setOffSetY(int offSetY)
    {
        if (m_offSetY == offSetY)
            return;

        m_offSetY = offSetY;
        emit OffSetYChanged(offSetY);
    }

    void setOffSetX(int offSetX)
    {
        if (m_offSetX == offSetX)
            return;

        m_offSetX = offSetX;
        emit OffSetXChanged(offSetX);
    }

signals:
    void WindowChanged();
    void IterationsChanged();
    void FractalIndexChanged();
    void ScaleChanged();
    void CameraCenterChanged();
    void SnowflakeSizeChanged();
    void DrawColorChanged();



    void OffSetYChanged(int offSetY);

    void OffSetXChanged(int offSetX);

private:
    int m_windowWidth;
    int m_windowHeight;
    int m_iterations;
    int m_fractalIndex;
    float m_scale;
    int m_cameraCenterX;
    int m_cameraCenterY;
    int m_snowflakeSize;
    QColor m_drawColor;
    QOpenGLRenderer *renderer;
    int m_offSetY;
    int m_offSetX;
};

#endif // QOPENGLITEM_H
