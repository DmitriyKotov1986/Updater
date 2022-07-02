#include "tiniupdate.h"

TIniUpdate::TIniUpdate(const QString &ConfigFileName, const QString &Key, const QString &Value, QObject *parent)
    : QObject(parent)
{
    Config = new QSettings(ConfigFileName, QSettings::IniFormat);
    if (Config->status() != QSettings::NoError) {
        qCritical() << "Cannot read file of configuration.";
        exit(-1);
    }
    WriteKey = Key;
    WriteValue = Value;
}

TIniUpdate::~TIniUpdate()
{
    Config->deleteLater();
}

void TIniUpdate::onStart()
{
    Config->setValue(WriteKey, WriteValue);
    Config->sync();
    qDebug() << "Write key:" << WriteKey << " = " << WriteValue;
    emit Finished();
}
