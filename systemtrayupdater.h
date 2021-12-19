#ifndef SYSTEMTRAYUPDATER_H
#define SYSTEMTRAYUPDATER_H

#include <QList>
#include <QObject>
#include <QPixmap>
#include <QSystemTrayIcon>

class SystemTrayUpdater : public QObject
{
    Q_OBJECT
public:
    explicit SystemTrayUpdater(QString toolTip, QObject *parent = nullptr);

    void timerEvent(QTimerEvent * /*unused*/);
    void start();
    void stop();

private:
    QIcon* createIcon(QPixmap &pixmap, int rotationDegrees);
    QPixmap createBasePixmap();

    int timerId;
    int currentImageIndex;
    QSystemTrayIcon systemTrayIcon;
    QList<QIcon> images;
signals:

};

#endif // SYSTEMTRAYUPDATER_H
