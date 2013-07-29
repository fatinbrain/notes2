#include "noterecord.h"

NoteRecord::NoteRecord(QString caption, QString text, QString tags):
    caption_(caption), text_(text), tags_(tags),    
    dtcr_(QDateTime::fromMSecsSinceEpoch(0)),
    dtmd_(QDateTime::fromMSecsSinceEpoch(0)),
    isValid_(true)
{
}

QDateTime NoteRecord::dtmd() const
{
    return dtmd_;
}

void NoteRecord::setDtmd(const QDateTime &dtmd)
{
    if(dtmd.isValid()){
        dtmd_ = dtmd;
    }
}

bool NoteRecord::isNull() const
{
    return isValid_;
}

void NoteRecord::validate()
{
    isValid_ = !caption_.isEmpty() && !text_.isEmpty();
    if(isValid_){
        if(dtcr_ == QDateTime::fromMSecsSinceEpoch(0)){
            dtcr_ = QDateTime::currentDateTime();
        }
        dtmd_ = QDateTime::currentDateTime();
    }
}

QDateTime NoteRecord::dtcr() const
{
    return dtcr_;
}

void NoteRecord::setDtcr(const QDateTime &dtcr)
{
    if(dtcr.isValid()){
        dtcr_ = dtcr;
    }
}

QString NoteRecord::tags() const
{
    return tags_;
}

void NoteRecord::setTags(const QString &tags)
{
    tags_ = tags;
}

QString NoteRecord::text() const
{
    return text_;
}

void NoteRecord::setText(const QString &text)
{
    text_ = text;
    validate();
}

QString NoteRecord::caption() const
{
    return caption_;
}

void NoteRecord::setCaption(const QString &caption)
{
    caption_ = caption;
    validate();
}
