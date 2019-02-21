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
  std::map< const QString, int> mapOfFigures();
  ~MainWindow();
private slots:
    void on_pushButton_clicked();
  //  void on_comboBox_activated();

    void on_pushButton_2_clicked();

public:
  Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
