#include "utils.h"

QString readFile(QString path){
    QString output = "";

    QFile file(path);
    file.open(QIODevice::ReadWrite);
    QTextStream in(&file);

    output.append(in.readAll());

    file.close();

    return output;
}

void writeFile(QString path, QString value){
    QFile file(path);
    file.open(QIODevice::ReadWrite);
    file.write(value.toUtf8());
    file.close();
}

Config::Config(){
    defaultConfigPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.config/AugSteam";
}

void Config::load(){
    if (!QDir().exists(defaultConfigPath)){
        QDir().mkpath(defaultConfigPath);
    }
    if (!QDir().exists(defaultConfigPath+"/config.json")){
        this->save();
    }

    QString configValue = readFile(defaultConfigPath+"/config.json");
    QJsonObject configObj = QJsonDocument::fromJson(configValue.toUtf8()).object();
    this->maFilesPath = configObj["maFilesPath"].toString();
    this->nickname = configObj["nickname"].toString();
}

void Config::save(){
    QJsonObject configObj;
    configObj["maFilesPath"] = this->maFilesPath;
    configObj["nickname"] = this->nickname;

    writeFile(defaultConfigPath+"/config.json", QString(QJsonDocument(configObj).toJson()));
}
