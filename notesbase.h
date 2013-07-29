#ifndef NOTESBASE_H
#define NOTESBASE_H

#include <QString>
#include <QList>
#include <QDateTime>
#include <QDebug>
#include "noterecord.h"

class NotesBase
{
public:
    NotesBase();
    
public slots:
    void clear();    
    void add(const NoteRecord& rec);
    int size() const;
    void rm(const int index);
    void writeToXML(const QString fname);
    void readFromXML(const QString fname);
    
private:
    QDateTime crdt_;
    QDateTime mddt_;
    QString tags_;
    QList<NoteRecord> records_;
};

#endif // NOTESBASE_H
