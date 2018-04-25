#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Sight.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Вектор sights должен возвращаться мультиграфом, который ещё не реализован
    QVector<Sight> sights = new QVector();
    sights.append(new Sight(59.934410, 30.324564, "Казанский собор"));
    sights.append(new Sight(59.937657, 30.308562, "Адмиралтейство"));
    sights.append(new Sight(59.938279, 30.315546, "Дворцовая площадь"));
    sights.append(new Sight(59.936442, 30.302236, "Медный всадник"));
    sights.appned(new Sight(59.934179, 30.306102, "Исакиевский собор"));
    sights.appned(new Sight(59.940213, 30.328921, "Спас на Крови"));
    sights.append(new Sight(59.950137, 30.316697, "Петропавловская крепость"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
