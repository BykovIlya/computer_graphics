#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <string>

/*
std::map< const QString, GLenum > MainWindow::mapOfFigures() {
    std::map< const QString, GLenum > map = {{"GL_POINT", GL_POINT},
                {"GL_LINES", GL_LINES},
                {"GL_LINE_STRIP", GL_LINE_STRIP},
                {"GL_LINE_LOOP", GL_LINE_LOOP},
                {"GL_TRIANGLES", GL_TRIANGLES},
                {"GL_TRIANGLE_STRIP", GL_TRIANGLE_STRIP},
                {"GL_TRIANGLE_FAN", GL_TRIANGLE_FAN},
                {"GL_QUADS", GL_QUADS},
                {"GL_QUAD_STRIP", GL_QUAD_STRIP},
                {"GL_POLYGON", GL_POLYGON}};
    return map;
}
*/
std::map< const QString, int > MainWindow::mapOfFigures() {
    std::map< const QString, int > map = {{"GL_POINT", 0},
                {"GL_LINES", 1},
                {"GL_LINE_STRIP", 2},
                {"GL_LINE_LOOP", 3},
                {"GL_TRIANGLES", 4},
                {"GL_TRIANGLE_STRIP", 5},
                {"GL_TRIANGLE_FAN", 6},
                {"GL_QUADS", 7},
                {"GL_QUAD_STRIP", 8},
                {"GL_POLYGON", 9}};
    return map;
}

std::vector<std::string> arrOfFigures = {"GL_POINT","GL_LINES","GL_LINE_STRIP","GL_LINE_LOOP","GL_TRIANGLES","GL_TRIANGLE_STRIP","GL_TRIANGLE_FAN","GL_QUADS","GL_QUAD_STRIP","GL_POLYGON"};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::map< const QString, int > map = mapOfFigures();
    /*for (auto it = map.begin(); it != map.end(); ++it) {
        ui->comboBox->addItem(it->first);
    }*/
    /*for (std::string i : arrOfFigures) {
        ui->comboBox->addItem(QString::fromStdString(i));
    }*/
    ui->label_3->setText(QString::fromStdString(arrOfFigures[0]));
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
    bool ok;
    //ui->openGLWidget->paintFigure(mapOfFigures().find(ui->comboBox->currentText())->second);
    ++num;
    ui->openGLWidget->update();
    ui->label_3->setText(QString::fromStdString(arrOfFigures[num]));
    if (num == 10) num = 0;
}
