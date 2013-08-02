#include "noterecord.h"

NoteRecord::NoteRecord(QString caption, QString text, QString tags):
    caption_(caption), text_(text), tags_(msiFromString(tags)),
    dtcr_(QDateTime::fromMSecsSinceEpoch(0)),
    dtmd_(QDateTime::fromMSecsSinceEpoch(0)),
    isValid_(false),
    isInit_(true)
{
    validate();
}

//NoteRecord::NoteRecord(const NoteRecord &other)
//{
//    caption_ = other.caption();
//    text_ = other.text();
//}

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

bool NoteRecord::isValid() const
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

        if(!isInit_){
            if(dtmd_ == QDateTime::fromMSecsSinceEpoch(0)){
                dtmd_ = QDateTime::currentDateTime();
            }
        }
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

QMap<QString, int> NoteRecord::tags() const
{
	return tags_;
}

void NoteRecord::setTags(const QMap<QString, int> &tags)
{
    tags_ = tags;
}

void NoteRecord::setTags(const QString str)
{
    tags_ = msiFromString(str);
}

void NoteRecord::addTag(const QString tag)
{
    if(!tag.isEmpty() && !tag.isNull()){
        tags_[tag] = 0;
    }
}

void NoteRecord::initBegin()
{
    isInit_ = true;
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


void NoteRecord::initEnd()
{
    isInit_ = false;
}

void NoteRecord::clear()
{
    caption_ = "";
    text_ = "";
    tags_.clear();
    dtcr_ = QDateTime::fromMSecsSinceEpoch(0);
    dtmd_ = QDateTime::fromMSecsSinceEpoch(0);
    isValid_ = false;
    isInit_ = true;
}
