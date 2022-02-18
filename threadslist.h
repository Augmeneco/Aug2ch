#ifndef THREADSLIST_H
#define THREADSLIST_H

#include <QWidget>

namespace Ui {
class ThreadsList;
}

class ThreadsList : public QWidget
{
    Q_OBJECT

public:
    explicit ThreadsList(QWidget *parent = nullptr);
    void drawThreads(QString board,int page);

    ~ThreadsList();

private:
    Ui::ThreadsList *ui;
};

#endif // THREADSLIST_H
