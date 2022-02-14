#include "threadpost.h"
#include "ui_threadpost.h"

#include <QLabel>
#include <QFileInfo>
#include <QDebug>
#include "requests.h"
#include "utils.h"

ThreadPost::ThreadPost(QWidget *parent, ThreadInfo *threadInfo) :
    QWidget(parent),
    ui(new Ui::ThreadPost)
{
    ui->setupUi(this);

    ui->threadName->setText(threadInfo->title);
    ui->threadText->setText(threadInfo->text);

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
}

void ThreadPost::resized(){
    qDebug() << width();
    if (height() < width()){
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
