#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>
#include <QColor>

class DataObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    explicit DataObject(QObject * parent);
    explicit DataObject(const QColor & color);
    ~DataObject();

    QColor color();
    void setColor(const QColor & color);

signals:
    void colorChanged();

private:
    QColor mColor;
};

#endif // DATAOBJECT_H
