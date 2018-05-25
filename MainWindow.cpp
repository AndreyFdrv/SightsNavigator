#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Sight.h"
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(this, SIGNAL(FindOptimalWay()),
            ui->mapWidget, SLOT(GetFirstChoosenSight()));
    QObject::connect(this, SIGNAL(SetMaxCost(QString)),
            ui->mapWidget, SLOT(SetMaxCost(QString)));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnFindOptimalWay_clicked()
{
    emit FindOptimalWay();
    emit SetMaxCost(ui->txtCost->text());
}
