#include "dataobject.h"


DataObject::DataObject(QObject *parent)
    : QObject(parent),
      mColor("magenta")
{

}

DataObject::DataObject(const QColor &color)
    : QObject(nullptr),
      mColor(color)
{

}

DataObject::~DataObject(){

}

QColor DataObject::color() {
    return mColor;
}

void DataObject::setColor(const QColor &color) {
    mColor = color;
    colorChanged();
}
