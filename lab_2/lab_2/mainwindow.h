#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

protected slots:
  void testAll(int);
  void turnAlphaTest();
  void turnBlendTest();
  void turnScissorTest();

  void dispOpacity(int);
  void dispX(int);
  void dispY(int);
  void dispW(int);
  void dispH(int);

private slots:
    void on_pushButton_clicked();

public:
  Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
