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
#include "tools/mapTool.h"

class NotesBase
{
public:
    NotesBase();    

    QMap<QString, int> tags() const;
    void setTags(const QMap<QString, int> &tags);
    void setTags(const QString str);
    
public slots:
    void clear();    
    void add(const NoteRecord& rec);
    void remove(const int index);
    int size() const;
    void rm(const int index);
    bool writeToXML(const QString fname);
    bool readFromXML(const QString fname);
    NoteRecord item(const int index) const;
    void setItem(const int index, const NoteRecord record);
    void updateModifyTime();
    
private:
    QDateTime dtcr_;
    QDateTime dtmd_;
    QMap<QString, int> tags_;
    QList<NoteRecord> records_;
    
    QDateTime dtFromString(const QString s);
    void adsorbTagsFromRecord(const NoteRecord& rec);
};

#endif // NOTESBASE_H
