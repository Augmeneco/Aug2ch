#ifndef ANSWERSLIST_H
#define ANSWERSLIST_H

#include <QWidget>

namespace Ui {
class AnswersList;
}

class AnswersList : public QWidget
{
    Q_OBJECT

public:
    explicit AnswersList(QWidget *parent = nullptr);
    ~AnswersList();

private:
    Ui::AnswersList *ui;
};

#endif // ANSWERSLIST_H
