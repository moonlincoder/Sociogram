#include <QIntValidator>
#include <QSlider>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int GridSize = ui->gridSizeSlider->value();
    // Connect slider with func
    connect(ui->gridSizeSlider, &QSlider::valueChanged, this, &MainWindow::gridSizeChangedSlot);

    mp_graphWidget = new GraphWidget(this, GridSize);
//    ui->gridSizeSlider->setValue(GridSize);

    ui->graphWidgetGridLayout->addWidget(mp_graphWidget);

}

void MainWindow::gridSizeChangedSlot(int size)
{
    ui->gridSizeLabel->setText(QString::number(size));
    mp_graphWidget->setGridSize(size);
    mp_graphWidget->getScene()->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{

    int count = mp_graphWidget->addNode({1});
    ui->CountLabel->setText(QString::number(count));
    mp_graphWidget->getScene()->update();
}

