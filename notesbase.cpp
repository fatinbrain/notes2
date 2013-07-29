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


int NotesBase::size() const
{
    return records_.size();
}
