#include "systemtrayupdater.h"
#include <QIcon>
#include <QPainter>
#include <QSystemTrayIcon>
#include <QTransform>

SystemTrayUpdater::SystemTrayUpdater(QString toolTip, QObject *parent)
    : QObject{parent}, currentImageIndex(0)
{
    const int imageCount = 12;
    const int degreesPerImage = 360 / imageCount;
    systemTrayIcon.setToolTip(toolTip);

    QPixmap pixmap = createBasePixmap();
    for (int i = 0; i < imageCount; i++) {
        int rotationDegrees = degreesPerImage * i;
        QIcon *icon = createIcon(pixmap, rotationDegrees);
        images.append(*icon);
    }
}

QPixmap SystemTrayUpdater::createBasePixmap() {
    const int iconSize = 32;
    QPixmap pixmap(iconSize, iconSize);
    pixmap.fill(QColorConstants::Transparent);
    QPainter painter(&pixmap);
    QFont font = QFont(painter.font());
    font.setPixelSize(pixmap.rect().height());
    painter.setFont(font);
    painter.drawText(pixmap.rect(),Qt::AlignCenter,"🤔");
    return pixmap;
}

void SystemTrayUpdater::start() {
    timerId = startTimer(128);
    currentImageIndex = 0;
    systemTrayIcon.setIcon(images.first());
    systemTrayIcon.setVisible(true);
}

void SystemTrayUpdater::stop() {
    killTimer(timerId);
    systemTrayIcon.setVisible(false);
}

QIcon* SystemTrayUpdater::createIcon(QPixmap &pixmap, int rotationDegrees) {
    return new QIcon(pixmap.transformed(QTransform().rotate(rotationDegrees)));
}

void SystemTrayUpdater::timerEvent(QTimerEvent *) {
    currentImageIndex = (++currentImageIndex) % images.size();
    systemTrayIcon.setIcon(images.value(currentImageIndex));
}
