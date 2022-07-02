#ifndef TINIUPDATE_H
#define TINIUPDATE_H

#include <QObject>
#include <QSettings>

class TIniUpdate : public QObject
{
    Q_OBJECT
public:
    explicit TIniUpdate(const QString &ConfigFileName, const QString &Key, const QString &Value, QObject *parent = nullptr);
    ~TIniUpdate();

private:
    QSettings *Config;
    QString WriteKey;
    QString WriteValue;
    void UpdateIni();

public slots:
    void onStart();

signals:
    void Finished();
};

#endif // TINIUPDATE_H
