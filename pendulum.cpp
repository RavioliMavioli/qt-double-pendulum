#include "pendulum.h"
#include <QtMath>
#include <QPainterPath>
#include <iostream>

Pendulum::Pendulum():
    GRAVITY(0.3),
    r1(100),
    r2(100),
    angle1(M_PI/4),
    angle2(M_PI/1),
    velocity1(0),
    velocity2(0),
    acceleration1(0),
    acceleration2(0),
    damp(0.999),
    m1(10),
    m2(10),
    center(400, 400)

{
    pendulum1.setX((r1 * qSin(angle1) + center.x()));
    pendulum1.setY((r1 * qCos(angle1) + center.y()));

    pendulum2.setX((r2 * qSin(angle2) + pendulum1.x()));
    pendulum2.setY((r2 * qCos(angle2) + pendulum1.y()));

}

void Pendulum::move(const QPoint &point)
{
}

void Pendulum::equation1()
{
    qreal num1 = -GRAVITY * ( 2 * (m1 + m2) ) * qSin(angle1);
    qreal num2 = -m2 * GRAVITY * qSin(acceleration1 - (2*acceleration2));
    qreal num3 = -2 * qSin(angle1-angle2) * m2;
    qreal num4 = (qPow(velocity2,2)) * (r2 + qPow(velocity1,2) * r1 * qCos(angle1-angle2));
    qreal den = r1 * (2*m1 + m2 - (m2*qCos((2*angle1)-(2*angle2))));

    acceleration1 = (num1 + num2 + (num3 * num4)) / den;
}

void Pendulum::equation2(){
    qreal num1 = 2 * qSin(angle1-angle2);
    qreal num2 = qPow(velocity1,2) * r1 * (m1+m2);
    qreal num3 = GRAVITY * (m1+m2) * qCos(angle1);
    qreal num4 = qPow(velocity2,2) * r2 * m2 * qCos(angle1-angle2);
    qreal den = r2 * (2*m1 + m2 - (m2*qCos((2*angle1)-(2*angle2))));

    acceleration2 = (num1*(num2 + num3 + num4)) / den;
}

void Pendulum::equation3(){
    equation1();
    equation2();

    velocity1 += acceleration1;
    velocity2 += acceleration2;
    angle1 += velocity1;
    angle2 += velocity2;

    velocity1 *= damp;
    velocity2 *= damp;
}
void Pendulum::run()
{
    equation3();

    pendulum1.setX((r1 * qSin(angle1) + center.x()));
    pendulum1.setY((r1 * qCos(angle1) + center.y()));

    pendulum2.setX((r2 * qSin(angle2) + pendulum1.x()));
    pendulum2.setY((r2 * qCos(angle2) + pendulum1.y()));

    trace.append(pendulum2);

}

void Pendulum::setCenter(const int &width, const int &height)
{
    center.setX(width);
    center.setY(height);
    /*for (int i = 0; i < trace.size(); i++){
        trace[i].setX(trace[i].x() + width);
        trace[i].setY(trace[i].y() + height);
    }*/
    trace.clear();
    move(QPoint(width, height));

}

void Pendulum::draw(QPainter &painter)
{
    //Trace 1

    painter.setPen(Qt::magenta);
    painter.setBrush(Qt::magenta);
    painter.drawLines(trace);


    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    //Pendulum 1
    painter.drawEllipse(pendulum1, m1, m1);
    painter.drawLine(center, pendulum1);
    //Pendulum 2
    painter.drawEllipse(pendulum2, m2, m2);
    painter.drawLine(pendulum1, pendulum2);
    //Middle Line
    painter.drawLine(center+QPoint(10,0), center-QPoint(10,0));

    std::cout<<velocity1<<std::endl;

}


