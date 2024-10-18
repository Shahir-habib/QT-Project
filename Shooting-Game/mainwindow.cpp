#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QColor>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QColor>
#include <QVector>
#include <QThread>
#include <QEventLoop>
#define DELAY delay(10)
QVector<QColor> colorVector {
    QColor(255, 0, 0),    // Red
    QColor(0, 255, 0),    // Green
    QColor(0, 0, 255),    // Blue
    QColor(255, 255, 0),  // Yellow
    QColor(255, 0, 255),  // Magenta
    QColor(0, 255, 255),  // Cyan
    QColor(192, 192, 192),// Silver
    QColor(128, 0, 0),    // Maroon
    QColor(128, 128, 0),  // Olive
    QColor(0, 128, 128)   // Teal
};

using namespace std;
vector< pair<int,int>> v;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->display->setMouseTracking(true);
    ui->display->installEventFilter(this);

    QPixmap canvas = ui->display->pixmap(Qt::ReturnByValue);
    if (canvas.isNull()) {
        canvas = QPixmap(ui->display->size());
        canvas.fill(QColor(20, 20, 20));
        ui->display->setPixmap(canvas);
    }
    drawGrids();
}
void MainWindow::delay(){
    QEventLoop loop;
    QTimer::singleShot(5,&loop,&QEventLoop::quit);
    loop.exec();
}
void MainWindow::colorPoint(int x, int y,int ri = -1,bool f =false) {

    QPixmap canvas = ui->display->pixmap();
    QPainter painter(&canvas);
    if(ri==-1)
         ri = rand()%9;
    QColor c = colorVector[ri];
    QPen pen= QPen(c,20);
    painter.setPen(pen);
    painter.drawRect(x, y + 10, 20,0);
    ui->display->setPixmap(canvas);
}
void MainWindow::drawGrids(){
    int gridOffset = 20;
    int width = ui->display->width();
    int height = ui->display->height();

    QImage gridImage(width, height, QImage::Format_ARGB32);
    gridImage.fill(Qt::black);
    QPainter painter(&gridImage);
    painter.setPen(QPen(Qt::gray, 1));

    for (int x = 0; x < width; x += gridOffset) {
        painter.drawLine(x, 0, x, height);
    }

    for (int y = 0; y < height; y += gridOffset) {
        painter.drawLine(0, y, width, y);
    }
    ui->display->setPixmap(QPixmap::fromImage(gridImage));

    v.push_back({29,18});
    v.push_back({31,18});
    v.push_back({33,18});
    v.push_back({30,19});
    v.push_back({31,19});
    v.push_back({32,19});
    v.push_back({30,20});
    v.push_back({31,20});
    v.push_back({32,20});
    v.push_back({30,21});
    v.push_back({32,21});
    for(auto c : v ){
        colorPoint(c.first*20,c.second*20,5);
    }
}
void MainWindow::shoot(){
    int x = v[1].first,y= v[1].second;
    for(int i = y - 1;i>0;i--){
        colorPoint(x*20,i*20,-1,true);
    }
    delay();
    shoot();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fire_clicked()
{
    // for(int i=50;i>0;i--){
    //     shoot();
    //     delay();
    // }
    shoot();
    qDebug()<<"HEllo";
}

