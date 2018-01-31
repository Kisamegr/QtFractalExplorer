#ifndef POINT2D_H
#define POINT2D_H

class MyPoint2D
{

private:
    float x;
    float y;
public:

    MyPoint2D();
    MyPoint2D(float nx, float ny);

    ~MyPoint2D();

    float getX();
    float getY();
    void setX(float nx);
    void setY(float ny);
    void set(float nx, float ny);

};

#endif // POINT2D_H
