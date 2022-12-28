#ifndef PENDULUM_H
#define PENDULUM_H

#include <QPoint>
#include <QPainter>
#include <QVector2D>

class Pendulum{

public:
    Pendulum();

private:
    qreal GRAVITY;
    qreal r1;
    qreal r2;
    qreal angle1;
    qreal angle2;
    qreal velocity1;
    qreal velocity2;
    qreal acceleration1;
    qreal acceleration2;
    qreal damp=0;

    qint32 m1;
    qint32 m2;

    QPoint pendulum1;
    QPoint pendulum2;

    QPoint center;
    QVector<QPoint> trace;

public:
    void move(const QPoint &point);
    void equation1();
    void equation2();
    void equation3();
    void run();
    void setCenter(const int &width, const int &height);
    void draw(QPainter &painter);
};

#endif // PENDULUM_H
