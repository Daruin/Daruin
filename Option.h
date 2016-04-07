#ifndef OPTION_H
#define OPTION_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>

class Option
{
public:
    Option();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    void save(QUrl url);

private:
    QUrl *arduinoDirectoryURL;
    bool loadSetting();
    bool saveSetting();
};

#endif // OPTION_H
