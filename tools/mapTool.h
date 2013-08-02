#ifndef MAPTOOL_H
#define MAPTOOL_H

#include <QMap>
#include <QStringList>


QString msiToString(const QMap<QString, int> map, 
                    QString keyValueSeparator = ":",
                    QString wordsSepeartor = ",");

QString msiToSimpleString(const QMap<QString, int> map, QString wordsSepeartor = ",");

QMap<QString, int> msiFromString(const QString str, 
                                 QString keyValueSeparator = ":",
                                 QString wordsSepeartor = ",");

#endif // MAPTOOL_H
