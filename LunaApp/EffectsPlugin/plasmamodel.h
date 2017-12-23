#ifndef PLASMAMODEL_H
#define PLASMAMODEL_H

#include <QObject>

class PlasmaModel : public QObject
{
    Q_OBJECT
public:
    explicit PlasmaModel(QObject *parent = nullptr);

};

#endif // PLASMAMODEL_H
