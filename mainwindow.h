#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "requests.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

signals:
    void resizeWindow(int w, int h);

public slots:
    void openThread(int threadNum, QString board);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Requests requests;
    void resizeEvent(QResizeEvent *event);
};
#endif // MAINWINDOW_H
