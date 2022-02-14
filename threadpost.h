#ifndef THREADPOST_H
#define THREADPOST_H

#include <QWidget>
#include <QList>

class ThreadInfo{
public:
    QString text;
    QString title;
    QList<QImage> images;
    int id;
    QList<QString> imageUrls;
};

namespace Ui {
class ThreadPost;
}

class ThreadPost : public QWidget
{
    Q_OBJECT

public:
    explicit ThreadPost(QWidget *parent = nullptr, ThreadInfo *threadInfo = nullptr);
    ~ThreadPost();

private:
    Ui::ThreadPost *ui;
    void resizeEvent(QResizeEvent *event);
};

#endif // THREADPOST_H
