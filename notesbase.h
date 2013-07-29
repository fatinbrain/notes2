#ifndef NOTESBASE_H
#define NOTESBASE_H

#include <QString>
#include <QList>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <qdom.h>

#include "noterecord.h"

class NotesBase
{
public:
    NotesBase();
    
    QString tags() const;
    void setTags(const QString &tags);
    
public slots:
    void clear();    
    void add(const NoteRecord& rec);
    int size() const;
    void rm(const int index);
    bool writeToXML(const QString fname);
    bool readFromXML(const QString fname);
    NoteRecord item(const int index);    
    
private:
    QDateTime crdt_;
    QDateTime mddt_;
    QString tags_;
    QList<NoteRecord> records_;
    
    QDateTime dtFromString(const QString s);
};

#endif // NOTESBASE_H
