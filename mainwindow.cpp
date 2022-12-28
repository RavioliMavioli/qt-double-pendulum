#include <QMouseEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer.setInterval(17);

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

    timer.start();
    time.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this); //this current window
    painter.fillRect(0, 0, width(), height(), Qt::white);
    pendulums.draw(painter);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    timer.stop();
    //TODO Pendulum move
    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    timer.start();
    time.start();
}

void MainWindow::resizeEvent(QResizeEvent *window)
{
    QMainWindow::resizeEvent(window);

    int centerWidth = window->size().width()/2;
    int centerHeight = window->size().height()/2;

    pendulums.setCenter(centerWidth,centerHeight);
}

void MainWindow::update()
{
    pendulums.run();
    repaint();
    time.start();
}


