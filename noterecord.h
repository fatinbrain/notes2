#ifndef NOTERECORD_H
#define NOTERECORD_H

#include <QString>
#include <QDateTime>

class NoteRecord
{
public:
    NoteRecord(QString caption = "", QString text = "", QString tags = "");    
    
    QString caption() const;
    void setCaption(const QString &caption);
    
    QString text() const;
    void setText(const QString &text);
    
    QString tags() const;
    void setTags(const QString &tags);
    
    QDateTime dtcr() const;
    void setDtcr(const QDateTime &dtcr);
    
    QDateTime dtmd() const;
    void setDtmd(const QDateTime &dtmd);
    
    bool isNull()const;
    
private slots:
    void validate();
    
private:
    QString caption_;
    QString text_;
    QString tags_;
    QDateTime dtcr_;
    QDateTime dtmd_;
    bool isValid_;
};

#endif // NOTERECORD_H
