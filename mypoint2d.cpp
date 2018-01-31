#include "MyPoint2D.h"

MyPoint2D::MyPoint2D()
{

}
MyPoint2D::MyPoint2D(float nx, float ny)
{
    x = nx;
    y = ny;
}


MyPoint2D::~MyPoint2D()
{
}

float MyPoint2D::getX()
{
    return x;
}

float MyPoint2D::getY()
{
    return y;
}

void MyPoint2D::setX(float nx)
{
    x = nx;
}
void MyPoint2D::setY(float nx)
{
    y = nx;
}

void MyPoint2D::set(float nx, float ny)
{
    x = nx;
    y = ny;
}
