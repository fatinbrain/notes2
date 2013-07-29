#ifndef NOTERECORD_H
#define NOTERECORD_H

#include <QString>
#include <QDateTime>

class NoteRecord
{
public:
    NoteRecord(QString caption = "", QString text = "", QString tags = "");    
    
private:
    QString caption_;
    QString text_;
    QString tags_;
    QDateTime dtcr_;
    QDateTime dtmd_;
};

#endif // NOTERECORD_H
