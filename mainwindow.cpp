#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QHBoxLayout>

#include "threadpost.h"
#include "threadslist.h"

ThreadsList *threadsList;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    threadsList = new ThreadsList(this);
    ui->stackedWidget->insertWidget(0, threadsList);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    ui->scrollAreaWidgetContents->setMaximumWidth(width()-20);

    //emit resizeWindow(width(),height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openThread(int threadNum, QString board){
    QString url = QString("https://2ch.hk/makaba/mobile.fcgi?task=get_thread&board=%1&thread=%2&post=1").arg(
        board, threadNum
    );
    qDebug() << url;
}


void MainWindow::on_pushButton_clicked()
{
    threadsList->drawThreads(ui->lineEdit->text(),1);
}

