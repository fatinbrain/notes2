#include "noterecord.h"

NoteRecord::NoteRecord(QString caption, QString text, QString tags):
    caption_(caption), text_(text), tags_(tags),
    dtcr_(QDateTime::currentDateTime()),
    dtmd_(QDateTime::currentDateTime())    
{
}
