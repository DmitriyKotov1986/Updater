#include <QCoreApplication>
#include <QTimer>
#include <QCommandLineParser>
#include <windows.h>
#include "tupdater.h"
#include "tiniupdate.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //устаналиваем основные настройки
    QCoreApplication::setApplicationName("Updater INI files");
    QCoreApplication::setOrganizationName("OOO 'SA'");
    QCoreApplication::setApplicationVersion("0.1a");

     setlocale(LC_CTYPE, ""); //настраиваем локаль

    //Создаем парсер параметров командной строки
    QCommandLineParser parser;
    parser.setApplicationDescription("Programm for update ini files.");
    parser.addHelpOption();
    parser.addVersionOption();

    //добавляем опцию Config
    QCommandLineOption Config(QStringList() << "Config", "Config file name", "ConfigFileNameValue", "Updater.ini");
    parser.addOption(Config);

    //добавляем опцию Key
    QCommandLineOption KeyName(QStringList() << "Key", "Key name by [GROUP]/[KEY]", "KeyName", "GROUP/Key");
    parser.addOption(KeyName);

    //добавляем опцию Value
    QCommandLineOption Value(QStringList() << "Value", "Key value", "KeyValue", "Value");
    parser.addOption(Value);

    //Парсим опции командной строки
    parser.process(a);

    //читаем конфигурацию из файла
    QString ConfigFileName = parser.value(Config);
    if (!parser.isSet(Config))
        ConfigFileName = a.applicationDirPath() +"/" + parser.value(Config);

    qDebug() << "Configuration file is: " +  ConfigFileName;

    //настраиваем таймер
    QTimer Timer;
    Timer.setInterval(0);       //таймер сработает так быстро как только это возможно
    Timer.setSingleShot(true);  //таймер сработает 1 раз

    if (parser.isSet(KeyName) && parser.isSet(Value)) {
        //создаем основной класс программы
        TIniUpdate Updater(ConfigFileName, parser.value(KeyName), parser.value(Value), &a);
        //При запуске выполняем слот Start
        QObject::connect(&Timer, SIGNAL(timeout()), &Updater, SLOT(onStart()));
        //Для завершения работы необходимоподать сигнал Finished
        QObject::connect(&Updater, SIGNAL(Finished()), &a, SLOT(quit()));
        //запускаем таймер
        Timer.start();
        //запускаем цикл обработчика событий
        return a.exec();
    }
    else {
        //создаем основной класс программы
        TUpdater Updater(ConfigFileName, &a);
        //При запуске выполняем слот Start
        QObject::connect(&Timer, SIGNAL(timeout()), &Updater, SLOT(onStart()));
        //Для завершения работы необходимоподать сигнал Finished
        QObject::connect(&Updater, SIGNAL(Finished()), &a, SLOT(quit()));
        //запускаем таймер
        Timer.start();
        //запускаем цикл обработчика событий
        return a.exec();
    }

}
