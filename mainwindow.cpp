#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->centralWidget()->hide();

    _settings = new QSettings("dankrusi","VectorTracer",this);

    setGeometry(this->x(),
                this->y(),
                _settings->value("appWidth","800").toInt(),
                _settings->value("appHeight","600").toInt());


    _scene = new QGraphicsScene(this);


    _view =  new QGraphicsView(_scene,this);
    _view->setStatusTip("test");

    ui->groupBoxDrawpad->setLayout(new QBoxLayout(QBoxLayout::TopToBottom));
    ui->groupBoxDrawpad->layout()->addWidget(_view);

    _sketcher = new Sketcher(_scene);
    _scene->addItem(_sketcher);


    QString lastLoadingImage = _settings->value("lastLoadingImage","").toString();
    if(lastLoadingImage != "") _sketcher->loadImage(lastLoadingImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionGenerate_QPoint_Array_triggered()
{

}

void MainWindow::on_actionLoad_Image_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this);
    _sketcher->loadImage(filename);
    _settings->setValue("lastLoadingImage",filename);
}

void MainWindow::on_sliderZoom_valueChanged(int value)
{
    double scale = value/100.0;
    QTransform trans;
    trans.scale(scale,scale);
    _view->setTransform(trans,false);
    _sketcher->setZoom(scale);
    ui->labelZoom->setText(QString("%1%").arg(value));
}
