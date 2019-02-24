#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <string>
#include <QDebug>

std::vector<std::string> arrOfFigures = {"GL_POINT","GL_LINES","GL_LINE_STRIP","GL_LINE_LOOP","GL_TRIANGLES","GL_TRIANGLE_STRIP",
                                         "GL_TRIANGLE_FAN","GL_QUADS","GL_QUAD_STRIP","GL_POLYGON","CIRCLES"};
std::vector<std::string> typesOfTests = {"Выбирай тест", "Прозрачность", "Смешивание", "Отсечение", "Все тесты"};
std::vector<std::string> opasityTests = { "GL_NEVER", "GL_LESS", "GL_EQUAL", "GL_LEQUAL", "GL_GREATER", "GL_NOTEQUAL", "GL_GEQUAL",
                                          "GL_ALWAYS"};
std::vector<std::string> blendTests = {"GL_ZERO", "GL_ONE", "GL_DST_COLOR", "GL_ONE_MINUS_DST_COLOR", "GL_SRC_COLOR", "GL_ONE_MINUS_SRC_COLOR", "GL_SRC_ALPHA",
                                       "GL_ONE_MINUS_SRC_ALPHA", "GL_DST_ALPHA","GL_ONE_MINUS_DST_ALPHA", "GL_SRC_ALPHA_SATURATE"};

std::vector<int> startPositions = {0, 0, 0 , 550, 450};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (std::string i : arrOfFigures) {
            ui->comboBox->addItem(QString::fromStdString(i));
    }
    QObject::connect(ui->comboBox, SIGNAL(activated(int)), ui->openGLWidget, SLOT(setFigure(int)));

    for (std::string i : typesOfTests) {
        ui->comboBox_2->addItem(QString::fromStdString(i));
    }
    QObject::connect(ui->comboBox_2, SIGNAL(activated(int)), this, SLOT(testAll(int)));
    for (std::string i : opasityTests) {
        ui->comboBox_3->addItem(QString::fromStdString(i));
    }
    QObject::connect(ui->comboBox_3, SIGNAL(activated(int)), ui->openGLWidget, SLOT(setAlphaIndex(int)));

    QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(dispOpacity(int)));

    for (std::string i : blendTests) {
        ui->comboBox_4->addItem(QString::fromStdString(i));
        ui->comboBox_5->addItem(QString::fromStdString(i));
    }
    QObject::connect(ui->comboBox_4, SIGNAL(activated(int)), ui->openGLWidget, SLOT(setBlendBegin(int)));
    QObject::connect(ui->comboBox_5, SIGNAL(activated(int)), ui->openGLWidget, SLOT(setBlendEnd(int)));

    QObject::connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(dispX(int)));
    QObject::connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this, SLOT(dispY(int)));
    QObject::connect(ui->horizontalSlider_4, SIGNAL(valueChanged(int)), this, SLOT(dispW(int)));
    QObject::connect(ui->horizontalSlider_5, SIGNAL(valueChanged(int)), this, SLOT(dispH(int)));
    testAll(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
     QApplication::exit();
}

void MainWindow::dispOpacity(int par) {
    double p = (double) par;
    ui->label_13->setNum(p);
    ui->openGLWidget->setAlphaValue(p);
}

void MainWindow::dispX(int par) {
    double p = (double) par;
    ui->label_14->setNum(p);
    ui->openGLWidget->setX(p);
}

void MainWindow::dispY(int par) {
    double p = (double) par;
    ui->label_15->setNum(p);
    ui->openGLWidget->setY(p);
}

void MainWindow::dispW(int par) {
    double p = (double) par;
    ui->label_16->setNum(p);
    ui->openGLWidget->setW(p);
}

void MainWindow::dispH(int par) {
    double p = (double) par;
    ui->label_17->setNum(p);
    ui->openGLWidget->setH(p);
}

void MainWindow::turnAlphaTest() {
    qDebug() << "alphatest\n";
    ui->openGLWidget->setAlphaIndex(ui->comboBox_2->currentIndex());
    dispOpacity(ui->horizontalSlider->value());
}

void MainWindow::turnBlendTest() {
    qDebug() << "blendtest\n";
    ui->openGLWidget->setBlendBegin(ui->comboBox_3->currentIndex());
    ui->openGLWidget->setBlendEnd(ui->comboBox_4->currentIndex());
}

void MainWindow::turnScissorTest() {
    qDebug() << "scissortest\n";
    dispX(ui->horizontalSlider_2->value());
    dispY(ui->horizontalSlider_3->value());
    dispW(ui->horizontalSlider_4->value());
    dispH(ui->horizontalSlider_5->value());

}

void MainWindow::testAll(int val) {
    qDebug() << val ;
    switch(val) {
    case 1:
        ui->openGLWidget->setFilter(1);
        turnAlphaTest();

        ui->label_2->setEnabled(true);
        ui->label_13->setEnabled(true);
        ui->comboBox_3->setEnabled(true);
        ui->horizontalSlider->setEnabled(true);

        ui->label_5->setEnabled(false);
        ui->label_6->setEnabled(false);
        ui->label_7->setEnabled(false);
        ui->comboBox_4->setEnabled(false);
        ui->comboBox_5->setEnabled(false);

        ui->label_8->setEnabled(false);
        ui->label_9->setEnabled(false);
        ui->label_10->setEnabled(false);
        ui->label_11->setEnabled(false);
        ui->label_12->setEnabled(false);
        ui->label_14->setEnabled(false);
        ui->label_15->setEnabled(false);
        ui->label_16->setEnabled(false);
        ui->label_17->setEnabled(false);
        ui->horizontalSlider_2->setEnabled(false);
        ui->horizontalSlider_3->setEnabled(false);
        ui->horizontalSlider_4->setEnabled(false);
        ui->horizontalSlider_5->setEnabled(false);
        break;
    case 2:
        ui->openGLWidget->setFilter(2);
        turnBlendTest();

        ui->label_2->setEnabled(false);
        ui->label_13->setEnabled(false);
        ui->comboBox_3->setEnabled(false);
        ui->horizontalSlider->setEnabled(false);

        ui->label_5->setEnabled(true);
        ui->label_6->setEnabled(true);
        ui->label_7->setEnabled(true);
        ui->comboBox_4->setEnabled(true);
        ui->comboBox_5->setEnabled(true);

        ui->label_8->setEnabled(false);
        ui->label_9->setEnabled(false);
        ui->label_10->setEnabled(false);
        ui->label_11->setEnabled(false);
        ui->label_12->setEnabled(false);
        ui->label_14->setEnabled(false);
        ui->label_15->setEnabled(false);
        ui->label_16->setEnabled(false);
        ui->label_17->setEnabled(false);
        ui->horizontalSlider_2->setEnabled(false);
        ui->horizontalSlider_3->setEnabled(false);
        ui->horizontalSlider_4->setEnabled(false);
        ui->horizontalSlider_5->setEnabled(false);
        break;
    case 3:
        ui->openGLWidget->setFilter(3);
        turnScissorTest();

        ui->label_2->setEnabled(false);
        ui->label_13->setEnabled(false);
        ui->comboBox_3->setEnabled(false);
        ui->horizontalSlider->setEnabled(false);

        ui->label_5->setEnabled(false);
        ui->label_6->setEnabled(false);
        ui->label_7->setEnabled(false);
        ui->comboBox_4->setEnabled(false);
        ui->comboBox_5->setEnabled(false);

        ui->label_8->setEnabled(true);
        ui->label_9->setEnabled(true);
        ui->label_10->setEnabled(true);
        ui->label_11->setEnabled(true);
        ui->label_12->setEnabled(true);
        ui->label_14->setEnabled(true);
        ui->label_15->setEnabled(true);
        ui->label_16->setEnabled(true);
        ui->label_17->setEnabled(true);
        ui->horizontalSlider_2->setEnabled(true);
        ui->horizontalSlider_3->setEnabled(true);
        ui->horizontalSlider_4->setEnabled(true);
        ui->horizontalSlider_5->setEnabled(true);
        break;
    case 4:
        ui->openGLWidget->setFilter(4);
        turnAlphaTest();
        turnBlendTest();
        turnScissorTest();

        ui->label_2->setEnabled(true);
        ui->label_13->setEnabled(true);
        ui->comboBox_3->setEnabled(true);
        ui->horizontalSlider->setEnabled(true);

        ui->label_5->setEnabled(true);
        ui->label_6->setEnabled(true);
        ui->label_7->setEnabled(true);
        ui->comboBox_4->setEnabled(true);
        ui->comboBox_5->setEnabled(true);

        ui->label_8->setEnabled(true);
        ui->label_9->setEnabled(true);
        ui->label_10->setEnabled(true);
        ui->label_11->setEnabled(true);
        ui->label_12->setEnabled(true);
        ui->label_14->setEnabled(true);
        ui->label_15->setEnabled(true);
        ui->label_16->setEnabled(true);
        ui->label_17->setEnabled(true);
        ui->horizontalSlider_2->setEnabled(true);
        ui->horizontalSlider_3->setEnabled(true);
        ui->horizontalSlider_4->setEnabled(true);
        ui->horizontalSlider_5->setEnabled(true);
        break;

    default:
        ui->openGLWidget->setFilter(0);

        ui->label_2->setEnabled(false);
        ui->label_13->setEnabled(false);
        ui->comboBox_3->setEnabled(false);
        ui->horizontalSlider->setEnabled(false);

        ui->label_5->setEnabled(false);
        ui->label_6->setEnabled(false);
        ui->label_7->setEnabled(false);
        ui->comboBox_4->setEnabled(false);
        ui->comboBox_5->setEnabled(false);

        ui->label_8->setEnabled(false);
        ui->label_9->setEnabled(false);
        ui->label_10->setEnabled(false);
        ui->label_11->setEnabled(false);
        ui->label_12->setEnabled(false);
        ui->label_14->setEnabled(false);
        ui->label_15->setEnabled(false);
        ui->label_16->setEnabled(false);
        ui->label_17->setEnabled(false);
        ui->horizontalSlider_2->setEnabled(false);
        ui->horizontalSlider_3->setEnabled(false);
        ui->horizontalSlider_4->setEnabled(false);
        ui->horizontalSlider_5->setEnabled(false);
        break;
    }
}
