#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void dda_line(float x1, float y1, float x2, float y2);
    void bresenham_circle(float xc, float yc, float radius);
    void on_draw_line_clicked();

    void on_draw_circle_clicked();

    void on_clear_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
