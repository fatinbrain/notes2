#include "notesbase.h"

NotesBase::NotesBase():
    crdt_(QDateTime::currentDateTime()),
    mddt_(QDateTime::currentDateTime()),
    tags_("")
{
}

void NotesBase::clear()
{
    records_.clear();
}

void NotesBase::add(const NoteRecord &rec)
{
    records_.append(rec);
}


void NotesBase::rm(const int index)
{
    records_.removeAt(index);
}

void NotesBase::writeToXML(const QString fname)
{
    qDebug() << QString("[notesbase]attempt to write xml to file [%1]").arg(fname);
}

void NotesBase::readFromXML(const QString fname)
{
    qDebug() << QString("[notesbase]attempt to read xml to file [%1]").arg(fname);
}

NoteRecord NotesBase::item(const int index)
{
    if(index < records_.size() && index >= 0){
        return records_.at(index);
    }else{
        return NoteRecord();
    }
}

int NotesBase::size() const
{
    return records_.size();
}
            
            
QString NotesBase::tags() const
{
    return tags_;
}

void NotesBase::setTags(const QString &tags)
{
    tags_ = tags;
}
