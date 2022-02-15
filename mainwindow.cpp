#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QHBoxLayout>

#include "threadpost.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::drawIndex(int page){
    QString board = ui->lineEdit->text();

    QString pageIndex;
    if (page == 1) pageIndex = "index";
    else pageIndex = QString::number(page);

    QWidget *threadsLayout = new QWidget();
    threadsLayout->setLayout(new QHBoxLayout());

    QJsonArray threads = requests.get(QString("https://2ch.hk/%1/%2.json").arg(board,pageIndex)).json().object()["threads"].toArray();
    for(auto jsonEnum : threads){
        QJsonObject mainPost = jsonEnum.toObject()["posts"].toArray()[0].toObject();

        ThreadInfo threadInfo;
        threadInfo.text = mainPost["comment"].toString();
        threadInfo.title = QString("<b><font color=\"#004A99\">%1</font></b> <font color=\"#5d5d5d\">%2 №%3</font>").arg(
            mainPost["subject"].toString(),
            mainPost["name"].toString(),
            mainPost["num"].toString()
        );

        QJsonArray images = mainPost["files"].toArray();

        for (auto image : images){
            QString imageUrl = image.toObject()["thumbnail"].toString();
            threadInfo.imageUrls.append(imageUrl);
            //break; //затычка чтобы было одно превью в списке тредов
        }

        ThreadPost *thread = new ThreadPost(this, &threadInfo);

        threadsLayout->addWidget(thread);
        connect(this, &MainWindow::resizeWindow,
                thread, &ThreadPost::resized);
    }
    ui->stackedWidget->setLayout(threadsLayout);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    emit resizeWindow(width(),height());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    drawIndex();
}

