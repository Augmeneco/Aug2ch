#include "threadpost.h"
#include "ui_threadpost.h"

#include <QLabel>
#include <QFileInfo>
#include <QDebug>
#include "requests.h"
#include "utils.h"
#include "mainwindow.h"

ThreadPost::ThreadPost(QWidget *parent, ThreadInfo *threadInfo) :
    QWidget(parent),
    ui(new Ui::ThreadPost)
{
    ui->setupUi(this);

    ui->threadName->setText(threadInfo->title);
    ui->threadText->setText(threadInfo->text);
    this->threadInfo_ = threadInfo->clone();

    for(QString imageUrl : threadInfo->imageUrls){
        QPixmap pm;
        pm.loadFromData(Requests().get("https://2ch.hk"+imageUrl).data);

        QLabel *imageObject = new QLabel();
        imageObject->setScaledContents(true);
        imageObject->setPixmap(pm);
        imageObject->setMaximumWidth(pm.width());
        imageObject->setMaximumHeight(pm.height());
        imageObject->setWordWrap(true);

        ui->threadImages->addWidget(imageObject);
    }

    connect(this, &ThreadPost::openThread,
            ((MainWindow*)parent), &MainWindow::openThread);
}

void ThreadPost::resized(int w, int h){
    qDebug() << w;
    if (h < w){
        ui->threadImages->setDirection(ui->threadImages->LeftToRight);
    }else{
        ui->threadImages->setDirection(ui->threadImages->TopToBottom);
    }
}

/*void ThreadPost::resizeEvent(QResizeEvent *event)
{
    qDebug() << width();
    if (height() < width()){
        ui->threadImages->setDirection(ui->threadImages->LeftToRight);
    }else{
        ui->threadImages->setDirection(ui->threadImages->TopToBottom);
    }
}*/

ThreadPost::~ThreadPost()
{
    delete ui;
}

void ThreadPost::on_threadOpen_clicked()
{
    qDebug() << threadInfo_.threadNum << threadInfo_.board;
    emit openThread(threadInfo_.threadNum, threadInfo_.board);
}

ThreadInfo ThreadInfo::clone(){
    ThreadInfo threadInfo;
    threadInfo.board = this->board;
    threadInfo.imageUrls = this->imageUrls;
    threadInfo.images = this->images;
    threadInfo.text = this->text;
    threadInfo.threadNum = this->threadNum;
    threadInfo.title = this->title;

    return threadInfo;
}

