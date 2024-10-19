#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void colorPoint(int x, int y,int ri,bool f);
    void colorPointm(int x, int y,QColor c,QPixmap& camvas);
    void drawGrids();
    void shoot();
    void delay();
    //bool eventFilter(QObject *watched, QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void on_fire_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
