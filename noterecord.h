#ifndef NOTERECORD_H
#define NOTERECORD_H

#include <QString>
#include <QDateTime>
#include <QMap>
#include "tools/mapTool.h"

class NoteRecord
{
public:
    NoteRecord(QString caption = "", QString text = "", QString tags = "");    
    
    QString caption() const;
    void setCaption(const QString &caption);
    
    QString text() const;
    void setText(const QString &text);
    
    QDateTime dtcr() const;
    void setDtcr(const QDateTime &dtcr);
    
    QDateTime dtmd() const;
    void setDtmd(const QDateTime &dtmd);
    
    bool isNull()const;
    
    QMap<QString, int> tags() const;
    void setTags(const QMap<QString, int> &tags);
    void setTags(const QString str);
    void addTag(const QString tag);
    void initBegin();
    void initEnd();
    
private slots:
    void validate();
    
private:
    QString caption_;
    QString text_;
//    QString tags_;
    QMap<QString, int> tags_;
    QDateTime dtcr_;
    QDateTime dtmd_;
    bool isValid_;
    bool isInit_;
};

#endif // NOTERECORD_H
