#ifndef TUPDATER_H
#define TUPDATER_H

#include <QObject>
#include <QSettings>

class TUpdater : public QObject
{
    Q_OBJECT
public:
    explicit TUpdater(const QString &ConfigFileName, QObject *parent = nullptr);
    ~TUpdater();

private:
    QSettings *Config;

    void UpdateIni();
    void Update();
  //  void RunBefore();
  //  void RunAfter();

public slots:
    void onStart();

signals:
    void Finished();
};

#endif // TUPDATER_H
