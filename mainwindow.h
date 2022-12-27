#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graphwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void gridSizeChangedSlot(int size);

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    GraphWidget* mp_graphWidget;
};

#endif // MAINWINDOW_H
