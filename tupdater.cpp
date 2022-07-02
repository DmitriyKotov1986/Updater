#include <QDir>
#include <QCoreApplication>
#include <QProcess>
#include "tupdater.h"

TUpdater::TUpdater(const QString &ConfigFileName, QObject *parent)
    : QObject(parent)
{
    Config = new QSettings(ConfigFileName, QSettings::IniFormat);
    if (Config->status() != QSettings::NoError) {
        qCritical() << "Cannot read file of configuration.";
        exit(-1);
    }
}

TUpdater::~TUpdater()
{
    Config->deleteLater();
}

void TUpdater::UpdateIni()
{
    QDir Dir(QCoreApplication::applicationDirPath());  //объявляем объект работы с папками
    Dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    Dir.setNameFilters(QStringList("*.ini"));
    QFileInfoList List = Dir.entryInfoList();

    for  (const auto &Item : List) {
        qDebug() << "Update file: " << Item.absoluteFilePath();
        QSettings tmp(Item.absoluteFilePath(), QSettings::IniFormat);
        for (const auto & GroupName: Config->childGroups()) {
            if (tmp.childGroups().contains(GroupName)) {
                Config->beginGroup(GroupName);
                tmp.beginGroup(GroupName);
                for (const auto & KeyName:Config->childKeys()) {
                    if (tmp.childKeys().contains(KeyName)) {
                        qDebug() << "Group: " << GroupName << " Key: " << KeyName
                                 << " Old value = " << tmp.value(KeyName, "").toString()
                                 << " New value = " << Config->value(KeyName, "").toString();
                        tmp.setValue(KeyName, Config->value(KeyName, ""));
                    }
                }
               Config->endGroup();
               tmp.endGroup();
            }
        }
    }
}

void TUpdater::Update()
{
    QProcess StartProcess;
    StartProcess.start("cmd", QStringList() << "/c" << "./Update/Update.bat");
    if (!StartProcess.waitForFinished()) {
        qDebug() << "Update.bat not finished.";
    };
}

/*void TUpdater::RunBefore()
{
    QProcess StartProcess;
    StartProcess.start("cmd", QStringList() << "/c" << "BeforeUpdate.bat");
    if (!StartProcess.waitForFinished()) {
        qDebug() << "BeforeUpdate.bat not finished.";
    };
}*/

/*void TUpdater::RunAfter()
{
    QProcess::startDetached("cmd", QStringList() << "/c" << "AfterUpdate.bat");
}
*/

void TUpdater::onStart()
{
   // RunBefore();

   // Update();

    UpdateIni();

  //  RunAfter();

    emit Finished();
}
