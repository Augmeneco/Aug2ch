#ifndef THREADPOST_H
#define THREADPOST_H

#include <QWidget>
#include <QList>

class ThreadInfo{
public:
    ThreadInfo clone();

    QString text;
    QString title;
    QString board;
    QList<QImage> images;
    int threadNum;
    QList<QString> imageUrls;
};

namespace Ui {
class ThreadPost;
}

class ThreadPost : public QWidget
{
    Q_OBJECT

public slots:
    void resized(int w, int h);
    void on_threadOpen_clicked();

signals:
    void openThread(int threadNum, QString board);

public:
    explicit ThreadPost(QWidget *parent = nullptr, ThreadInfo *threadInfo = nullptr);
    ThreadInfo threadInfo_;
    ~ThreadPost();

private:
    Ui::ThreadPost *ui;
};

#endif // THREADPOST_H
