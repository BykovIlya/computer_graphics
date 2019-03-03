#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     QObject::connect(ui->verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(dispDeg(int)));
     ui->lcdNumber->display(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QApplication::exit();
}

void MainWindow::dispDeg(int par) {
    double p = (double) par;
    ui->lcdNumber->display(p);
    ui->openGLWidget->setDeg(par);
}
