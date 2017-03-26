#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLayout>
#include <QBoxLayout>
#include <QFileDialog>
#include <QSettings>

#include "sketcher.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionGenerate_QPoint_Array_triggered();
    void on_actionLoad_Image_triggered();
    void on_sliderZoom_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    Sketcher *_sketcher;
    QGraphicsScene *_scene;
    QGraphicsView *_view;
    QSettings *_settings;
};

#endif // MAINWINDOW_H
