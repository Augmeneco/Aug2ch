#include "threadslist.h"
#include "ui_threadslist.h"
#include "requests.h"
#include "threadpost.h"
#include "mainwindow.h"

ThreadsList::ThreadsList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThreadsList)
{
    ui->setupUi(this);
}

void ThreadsList::drawThreads(QString board,int page){

    QString pageIndex;
    if (page == 1) pageIndex = "index";
    else pageIndex = QString::number(page);

    QJsonArray threads = Requests().get(QString("https://2ch.hk/%1/%2.json").arg(board,pageIndex)).json().object()["threads"].toArray();
    for(auto jsonEnum : threads){
        QJsonObject mainPost = jsonEnum.toObject()["posts"].toArray()[0].toObject();

        ThreadInfo threadInfo;
        threadInfo.text = mainPost["comment"].toString();
        threadInfo.title = QString("<b><font color=\"#004A99\">%1</font></b> <font color=\"#5d5d5d\">%2 №%3</font>").arg(
            mainPost["subject"].toString(),
            mainPost["name"].toString(),
            mainPost["num"].toString()
        );
        threadInfo.threadNum = mainPost["num"].toString().toInt();
        threadInfo.board = board;

        QJsonArray images = mainPost["files"].toArray();

        for (auto image : images){
            QString imageUrl = image.toObject()["thumbnail"].toString();
            threadInfo.imageUrls.append(imageUrl);
            //break; //затычка чтобы было одно превью в списке тредов
        }

        ThreadPost *thread = new ThreadPost(this, &threadInfo);
        ui->threadsList->addWidget(thread);

        //connect((MainWindow*)parent(), &MainWindow::resizeWindow,
        //        thread, &ThreadPost::resized);
    }
}

ThreadsList::~ThreadsList()
{
    delete ui;
}
