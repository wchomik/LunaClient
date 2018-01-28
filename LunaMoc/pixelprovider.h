#ifndef PIXELPROVIDER_H
#define PIXELPROVIDER_H

#include <QObject>
#include <QList>
#include <QTimer>
#include <QColor>
#include <vector>

#include <random>

class PixelProvider : public QObject
{
    Q_OBJECT

public:
    explicit PixelProvider(QObject *parent = nullptr);
    explicit PixelProvider(int count);
    Q_PROPERTY(QList<QObject *> data READ data NOTIFY dataChanged)

    QList<QObject *> data() const;

    void setPixel(int index, const QColor & color);
signals:
    void dataChanged();
private:

    QList<QObject *> m_data;
};

#endif // PIXELPROVIDER_H
