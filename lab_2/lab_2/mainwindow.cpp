#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <string>

std::vector<std::string> arrOfFigures = {"GL_POINT","GL_LINES","GL_LINE_STRIP","GL_LINE_LOOP","GL_TRIANGLES","GL_TRIANGLE_STRIP",
                                         "GL_TRIANGLE_FAN","GL_QUADS","GL_QUAD_STRIP","GL_POLYGON"};
std::vector<std::string> typesOfTests = {"Выбирай тест", "Прозрачность", "Смешивание", "Отсечение", "Все тесты"};
std::vector<std::string> opasityTests = { "GL_NEVER", "GL_LESS", "GL_EQUAL", "GL_LEQUAL", "GL_GREATER", "GL_NOTEQUAL", "GL_GEQUAL",
                                          "GL_ALWAYS"};
std::vector<std::string> blendTests = {"GL_ZERO", "GL_ONE", "GL_SRC_COLOR", "GL_ONE_MINUS_SRC_COLOR", "GL_SRC_ALPHA",
                                       "GL_ONE_MINUS_SRC_ALPHA", "GL_DST_ALPHA","GL_ONE_MINUS_DST_ALPHA", "GL_SRC_ALPHA_SATURATE"};

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
    QObject::connect(ui->comboBox_2, SIGNAL(activated(int)), ui->openGLWidget, SLOT(setAlphaIndex(int)));
    QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setAlphaValue(int)));

    for (std::string i : blendTests) {
        ui->comboBox_3->addItem(QString::fromStdString(i));
        ui->comboBox_4->addItem(QString::fromStdString(i));
    }
    QObject::connect(ui->comboBox_3, SIGNAL(activated(int)), ui->openGLWidget, SLOT(setBlendBegin(int)));
    QObject::connect(ui->comboBox_4, SIGNAL(activated(int)), ui->openGLWidget, SLOT(setBlendEnd(int)));

    QObject::connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(setX(int)));
    QObject::connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this, SLOT(setY(int)));
    QObject::connect(ui->horizontalSlider_4, SIGNAL(valueChanged(int)), this, SLOT(setW(int)));
    QObject::connect(ui->horizontalSlider_5, SIGNAL(valueChanged(int)), this, SLOT(setH(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
     QApplication::exit();
}

int num = 0;

void MainWindow::on_pushButton_2_clicked()
{
    ui->openGLWidget->update();
    ++num;
    if (num == 10) num = 0;
}
