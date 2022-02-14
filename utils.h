#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QStandardPaths>
#include <QDir>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QObject>


class utils : public QObject
{
    Q_OBJECT
public:

};

class Config{
public:
    Config();

    QString maFilesPath = "";
    QString nickname = "";

    void save();
    void load();

private:
    QString defaultConfigPath = "";
};

QString readFile(QString path);
void writeFile(QString path, QString value);

#endif // UTILS_H
