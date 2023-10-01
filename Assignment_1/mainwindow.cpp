#include "mainwindow.h"
#include "./ui_mainwindow.h"

QImage img(700, 700, QImage::Format_RGB888);
QRgb background(qRgb(0, 0, 0));

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// algorithm to draw dda line.
void MainWindow :: dda_line(float x1, float y1, float x2, float y2){
    float dx, dy, xinc, yinc, steps;
    int i=0;
    QRgb color=qRgb(230, 230, 0);
    dx=x2-x1;
    dy=y2-y1;
    if(abs(dx)>=abs(dy)){
        steps=abs(dx);
    }
    else{
        steps=abs(dy);
    }
    xinc=(float)dx/(float)steps;
    yinc=(float)dy/(float)steps;
    for(i=0; i<steps; i++){
        img.setPixel(x1, y1, color);
        x1+=xinc;
        y1+=yinc;
    }
}

// algorithm to draw bresenham's circle.
void MainWindow :: bresenham_circle(float xc, float yc, float radius){
    int x=0;
    int y=radius;
    // setting the decision parameter.
    int d=3-2*radius;
    QRgb color=qRgb(230, 230, 0);
    while(x<=y){
        // setting the color of pixels at spectific locations.
        img.setPixel(y+xc, x+yc, color);
        img.setPixel(x+xc, y+yc, color);
        img.setPixel(-x+xc, y+yc, color);
        img.setPixel(-y+xc, x+yc, color);
        img.setPixel(-y+xc, -x+yc, color);
        img.setPixel(-x+xc, -y+yc, color);
        img.setPixel(x+xc, -y+yc, color);
        img.setPixel(y+xc, -x+yc, color);

        // checking the decision parameter.
        if(d<0){
            d+=4*x+6;
        }
        else{
            d+=4*(x-y)+10;
            y--;
        }
        x++;
    }
}

// button to draw dda line.
void MainWindow::on_draw_line_clicked()
{
    float x1=ui->x_1->toPlainText().toInt();
    float y1=ui->x_1->toPlainText().toInt();
    float x2=ui->x_2->toPlainText().toInt();
    float y2=ui->y_2->toPlainText().toInt();
    dda_line(x1, y1, x2, y2);
    ui->result->setPixmap(QPixmap :: fromImage(img));
    ui->result->show();
}

// button to draw bresenham's circle.
void MainWindow::on_draw_circle_clicked()
{
    float xc=ui->x_c->toPlainText().toInt();
    float yc=ui->y_c->toPlainText().toInt();
    // radius of outer circle.
    int R=ui->radius->toPlainText().toInt();

    float r=(0.5)*R;      // calculating the radius of the inner cirlce.

    // drawing the sides of triangle using dda algorithm.
    dda_line(xc, yc-R, xc+(R/1.154), yc+r);
    dda_line(xc, yc-R, xc-(R/1.154), yc+r);
    dda_line(xc-(R/1.154), yc+r, xc+(R/1.154), yc+r);
    // drawing the circles.
    bresenham_circle(xc, yc, R);    // outer circle.
    bresenham_circle(xc, yc, r);    // inner circle.
    ui->result->setPixmap(QPixmap :: fromImage(img));
}

// button to clear the screen.
void MainWindow::on_clear_clicked()
{
    img.fill(background);
    ui->result->setPixmap(QPixmap :: fromImage(img));
}

