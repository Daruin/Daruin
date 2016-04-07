#include "Option.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QFile>
#include <QByteArray>

Option::Option()
{
    if(!loadSetting()){
        arduinoDirectoryURL = new QUrl("");
    }
}

void Option::read(const QJsonObject &json)
{
    arduinoDirectoryURL = new QUrl(json["arduinoDirectory"].toString());
}

void Option::write(QJsonObject &json) const
{
    json["arduinoDirectory"] = arduinoDirectoryURL->toString();
}

void Option::save(QUrl url)
{
    arduinoDirectoryURL = url;
    saveSetting();
}

bool Option::loadSetting(void)
{
    QFile saveFile("save.json");
    if(!saveFile.open(QIODevice::ReadOnly)){
        return false;
    }
    QByteArray saveData = saveFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc);
    return true;
}

bool Option::saveSetting(void)
{
    QFile saveFile("save.json");
    if(!saveFile.open(QIODevice::WriteOnly)){
        return false;
    }

    QJsonObject optionObejct;
    write(optionObject);
    QJsonDocument saveDoc(optionObejct);
    saveFile.write(saveDoc.toJson());
    return true;
}
