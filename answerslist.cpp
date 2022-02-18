#include "answerslist.h"
#include "ui_answerslist.h"

AnswersList::AnswersList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnswersList)
{
    ui->setupUi(this);
}

AnswersList::~AnswersList()
{
    delete ui;
}
