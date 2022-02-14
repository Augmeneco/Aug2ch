#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "threadpost.h"

void writeFile(QString path, QByteArray value){
    QFile file(path);
    file.open(QIODevice::ReadWrite);
    file.write(value);
    file.close();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QJsonArray threads = requests.get("https://2ch.hk/vg/index.json").json().object()["threads"].toArray();
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
        ui->threadsList->addWidget(thread);
        connect(this, &MainWindow::resizeWindow,
                thread, &ThreadPost::resized);
    }

}

void MainWindow::resizeEvent(QResizeEvent *event){
    emit resizeWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

