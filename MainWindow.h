#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnFindOptimalWay_clicked();

    void on_btnSave_clicked();

    void on_btnLoad_clicked();

signals:
    void FindOptimalWay();
    void SetMaxCost(QString maxCostStr);
    void SaveSightsMultigraph(QString filename);
    void LoadSightsMultigraph(QString filename);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
