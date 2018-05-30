#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Sight.h"
#include <QVector>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(this, SIGNAL(FindOptimalWay()),
            ui->mapWidget, SLOT(GetFirstChoosenSight()));
    QObject::connect(this, SIGNAL(SetMaxCost(QString)),
            ui->mapWidget, SLOT(SetMaxCost(QString)));
    QObject::connect(this, SIGNAL(SaveSightsMultigraph(QString)),
            ui->mapWidget, SLOT(SaveSightsMultigraph(QString)));
    QObject::connect(this, SIGNAL(LoadSightsMultigraph(QString)),
            ui->mapWidget, SLOT(LoadSightsMultigraph(QString)));
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
void MainWindow::on_btnSave_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Сохранить"),
                                                    "",
                                                    tr("Multigraph (*.mg)"));
    emit SaveSightsMultigraph(filename);
}
void MainWindow::on_btnLoad_clicked()
{
    QString filename = QFileDialog::getOpenFileName(0, "Загрузить", "", "*.mg");
    emit LoadSightsMultigraph(filename);
}
