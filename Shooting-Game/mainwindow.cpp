#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QColor>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QColor>
#include <QVector>
#include <QThread>
#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QKeyEvent>
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

// Define colors
QColor red(255, 0, 0);
QColor blue(0, 0, 255);
QColor skin(255, 224, 189);
QColor brown(92, 51, 23);
QColor yellow(255, 255, 0);
QColor empty(0, 0, 0); // Optional, for clarity
using namespace std;
// Mario's pixel coordinates and colors
std::vector<std::tuple<QPoint, QColor>> marioPixels = {
    {{3, 0}, red}, {{4, 0}, red}, {{5, 0}, red}, {{6, 0}, red},
    {{2, 1}, red}, {{3, 1}, red}, {{4, 1}, red}, {{5, 1}, red}, {{6, 1}, red}, {{7, 1}, red},
    {{8, 1}, red}, {{9, 1}, red}, {{10, 1}, red},

    {{2, 2}, brown}, {{3, 2}, brown}, {{4, 2}, brown}, {{5, 2}, skin}, {{6, 2}, skin}, {{7, 2}, brown}, {{8, 2}, skin},

    {{1, 3}, brown}, {{2, 3}, skin}, {{3, 3}, brown}, {{4, 3}, skin}, {{5, 3}, skin}, {{6, 3}, skin}, {{7, 3}, brown}, {{8, 3}, skin}, {{9, 3}, skin}, {{10, 3}, skin},

    {{1, 4}, brown}, {{2, 4}, skin}, {{3, 4}, brown}, {{4, 4}, brown}, {{5, 4}, skin}, {{6, 4}, skin}, {{7, 4}, skin}, {{8, 4}, brown}, {{9, 4}, skin}, {{10, 4}, skin}, {{11, 4}, skin},

    {{1, 5}, brown}, {{2, 5}, brown}, {{3, 5}, skin}, {{4, 5}, skin}, {{5, 5}, skin}, {{6, 5}, skin}, {{7, 5}, brown}, {{8, 5}, brown}, {{9, 5}, brown}, {{10, 5}, brown},

    {{3, 6}, skin}, {{4, 6}, skin}, {{5, 6}, skin}, {{6, 6}, skin}, {{7, 6}, skin}, {{8, 6}, skin}, {{9, 6}, skin},

    {{2, 7}, blue}, {{3, 7}, blue}, {{4, 7}, red}, {{5, 7}, blue}, {{6, 7}, blue}, {{7, 7}, red},

    {{1, 8}, blue}, {{2, 8}, blue}, {{3, 8}, blue}, {{4, 8}, red}, {{5, 8}, blue}, {{6, 8}, blue}, {{7, 8}, red}, {{8, 8}, blue}, {{9, 8}, blue}, {{10, 8}, blue},

    {{0, 9}, blue}, {{1, 9}, blue}, {{2, 9}, blue}, {{3, 9}, blue}, {{4, 9}, red}, {{5, 9}, blue}, {{6, 9}, blue}, {{7, 9}, red}, {{8, 9}, blue}, {{9, 9}, blue}, {{10, 9}, blue}, {{11, 9}, blue},

    {{0, 10}, skin}, {{1, 10}, skin}, {{2, 10}, blue}, {{3, 10}, blue}, {{4, 10}, red}, {{5, 10}, red}, {{6, 10}, red}, {{7, 10}, red}, {{8, 10}, blue}, {{9, 10}, blue}, {{10, 10}, skin}, {{11, 10}, skin},

    {{0, 11}, skin}, {{1, 11}, skin}, {{2, 11}, skin}, {{3, 11}, skin}, {{4, 11}, red}, {{5, 11}, red}, {{6, 11}, red}, {{7, 11}, red}, {{8, 11}, blue}, {{9, 11}, blue}, {{10, 11}, skin}, {{11, 11}, skin},

    {{0, 12}, skin}, {{1, 12}, skin}, {{2, 12}, skin}, {{3, 12}, red}, {{4, 12}, red}, {{5, 12}, red}, {{6, 12}, red}, {{7, 12}, red}, {{8, 12}, red}, {{9, 12}, red}, {{10, 12}, skin}, {{11, 12}, skin},

    {{2, 13}, red}, {{3, 13}, red}, {{4, 13}, red}, {{7, 13}, red}, {{8, 13}, red}, {{9, 13}, red},

    {{1, 14}, brown}, {{2, 14}, brown}, {{3, 14}, brown}, {{8, 14}, brown}, {{9, 14}, brown}, {{10, 14}, brown},

    {{0, 15}, brown}, {{1, 15}, brown}, {{2, 15}, brown}, {{3, 15}, brown}, {{8, 15}, brown}, {{9, 15}, brown}, {{10, 15}, brown}, {{11, 15}, brown},
    };
vector< pair<int,int>> v;
int go=8,offset=0;
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
    QPen pen= QPen(c,go);
    painter.setPen(pen);
    painter.drawRect(x, y + go/2, go,0);
    ui->display->setPixmap(canvas);
}
void MainWindow::colorPointm(int x, int y,QColor c ,QPixmap& canvas) {

    //QPixmap canvas = ui->display->pixmap();
    QPainter painter(&canvas);
    QPen pen= QPen(c,go);
    painter.setPen(pen);
    painter.drawRect(x, y + go/2, go,0);
    //ui->display->setPixmap(canvas);
}
void MainWindow::drawGrids(){
    int gridOffset = go;
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
    // for(auto c : v ){
    //     colorPoint(c.first*go,c.second*go,5);
    // }
    int pixelSize = go; // Size of each pixel

    // Draw each pixel
    QPixmap canvas = ui->display->pixmap();
    for (const auto &pixel : marioPixels) {
        const QPoint &point = std::get<0>(pixel);
        const QColor &color = std::get<1>(pixel);
        colorPointm(point.x() * pixelSize, point.y() * pixelSize,color,canvas);
    }
    ui->display->setPixmap(canvas);
}
void MainWindow::keyPressEvent(QKeyEvent *event)  {
    qDebug() << "Pressed key:" << event->key(); // Debug output
    QPixmap canvas = ui->display->pixmap();
    if (event->key() == 70) {

        for (const auto &pixel : marioPixels) {
            const QPoint &point = std::get<0>(pixel);
            const QColor &color = std::get<1>(pixel);
            colorPointm((point.x() + offset)* go, point.y() * go,QColor(20,20,20),canvas);
        }
        offset -=1;
        for ( const auto &pixel : marioPixels) {
            const QPoint &point = std::get<0>(pixel);
            const QColor &color = std::get<1>(pixel);
            colorPointm((point.x() + offset) * go, point.y() * go,color,canvas);
        }
    }
    if (event->key() == 74) {

        for (const auto &pixel : marioPixels) {
            const QPoint &point = std::get<0>(pixel);
            const QColor &color = std::get<1>(pixel);
            colorPointm((point.x() + offset)* go, point.y() * go,QColor(20,20,20),canvas);
        }
        offset+=1;
        for (const auto &pixel : marioPixels) {
            const QPoint &point = std::get<0>(pixel);
            const QColor &color = std::get<1>(pixel);
            colorPointm((point.x() + offset) * go, point.y() * go,color,canvas);
        }
    }
    ui->display->setPixmap(canvas);
}
void MainWindow::shoot(){
    int x = v[1].first,y= v[1].second;
    for(int i = y - 1;i>0;i--){
        colorPoint(x*go,i*go,-1,true);
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

