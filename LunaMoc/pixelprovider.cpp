#include "pixelprovider.h"

#include "dataobject.h"

#include <QDebug>

PixelProvider::PixelProvider(QObject *parent) :
    QObject(parent)
{
}

PixelProvider::PixelProvider(int count) :
    PixelProvider(nullptr)
{
    for(int i = 0; i < count; ++i) {
        m_data.append(new DataObject(QColor("white")));
    }
}

QList<QObject *> PixelProvider::data() const
{
    return m_data;
}

void PixelProvider::setPixel(int index, const QColor &color)
{
    static_cast<DataObject *>(m_data[index])->setColor(color);
}
