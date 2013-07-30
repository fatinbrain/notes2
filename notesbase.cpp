#include "notesbase.h"

NotesBase::NotesBase():
    crdt_(QDateTime::currentDateTime()),
    mddt_(QDateTime::currentDateTime()),
    tags_(msiFromString(""))
{
}

void NotesBase::clear()
{
    records_.clear();
}

void NotesBase::add(const NoteRecord &rec)
{
    records_.append(rec);
    adsorbTagsFromRecord(rec);
}


void NotesBase::rm(const int index)
{
    records_.removeAt(index);
}

bool NotesBase::writeToXML(const QString fname)
{
    qDebug() << QString("[notesbase]attempt to write xml to file [%1]").arg(fname);
    
    QDomDocument doc;
        
    QDomElement deNotesBase = doc.createElement("NotesBase");
    deNotesBase.setAttribute("cr", crdt_.toTime_t());
    deNotesBase.setAttribute("md", mddt_.toTime_t());
    
    QDomElement deTags = doc.createElement("Tags");
    QDomText deTagsText = doc.createTextNode(msiToString(tags()));
    deTags.appendChild(deTagsText);
    
    QDomElement deNotes = doc.createElement("Notes");
    for(int i = 0; i < records_.size(); i++){
        QDomElement deNote = doc.createElement("Note");
        deNote.setAttribute("cr", records_.at(i).dtcr().toTime_t());
        deNote.setAttribute("md", records_.at(i).dtmd().toTime_t());
        
        QDomElement deNoteCaption = doc.createElement("Caption");
        QDomText deNoteCaptionText = doc.createTextNode(records_.at(i).caption());
        deNoteCaption.appendChild(deNoteCaptionText);
        
        QDomElement deNoteText = doc.createElement("Text");
        QDomText deNoteTextText = doc.createTextNode(records_.at(i).text());
        deNoteText.appendChild(deNoteTextText);
        
        QDomElement deNoteTags = doc.createElement("Tags");
        QString sTagline = msiToString(records_.at(i).tags());        
        if(!sTagline.isEmpty()){
            QDomText deNoteTagsText = doc.createTextNode(sTagline);            
            deNoteTags.appendChild(deNoteTagsText);
        }
        
        deNotes.appendChild(deNote);
        deNote.appendChild(deNoteCaption);
        deNote.appendChild(deNoteText);
        deNote.appendChild(deNoteTags);
    }
    
    doc.appendChild(deNotesBase);
    deNotesBase.appendChild(deTags);
    deNotesBase.appendChild(deNotes);
    
    QFile f(fname);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << QString("[ERRR]cannot open file [%1] to write base").arg(fname);
        return false;
    }
    
    QTextStream ts(&f);
    ts << doc.toString(4);
    
    f.close();
    
    return true;
}


bool NotesBase::readFromXML(const QString fname)
{
    qDebug() << QString("[notesbase]attempt to read xml to file [%1]").arg(fname);
    
    QFile f(fname);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << QString("[ERRR]cannot open file [%1] to read base").arg(fname);
        return false;
    }
    
    QDomDocument doc;
    if(!doc.setContent(&f)){
        f.close();
        qDebug() << QString("[ERRR]cannot read xml from [%1]").arg(fname);
        return false;
    }
    f.close();
    
    qDebug() << doc.toString(4);
    
    QDomElement deMain = doc.documentElement();
    
    QDomNode dnMainChild = doc.firstChild();    //NoteBase
    QString sBuff = deMain.attribute("cr");
    crdt_ = dtFromString(sBuff);
    sBuff = deMain.attribute("md");
    mddt_ = dtFromString(sBuff);
    
    qDebug() << "crdt\t" << crdt_.toString();
    qDebug() << "mddt\t" << mddt_.toString();
    
    QDomNode dnChild = dnMainChild.firstChild();    //First child of NoteBase
    
    while(!dnChild.isNull()){
        if(dnChild.isElement()){
            QDomElement de = dnChild.toElement();
            qDebug() << de.tagName();
            
            if(de.tagName() == "Tags"){
                QDomText dt = de.firstChild().toText();                
                qDebug() << "tags:\t" + dt.data();
                tags_ = msiFromString(dt.data());
            }
            
            if(de.tagName() == "Notes"){
                qDebug() << "Notes found";

                NoteRecord n;
                
                QDomNode dnNotesChild = de.firstChild();    //Note
                qDebug() << dnNotesChild.toElement().tagName();
                                
                while(!dnNotesChild.isNull()){  //jo Notes
                    
                    QString sBuff = dnNotesChild.toElement().attribute("cr");
                    n.setDtcr(dtFromString(sBuff));
                    sBuff = dnNotesChild.toElement().attribute("md");
                    n.setDtmd(dtFromString(sBuff));
                    qDebug() << "crdt\t" << n.dtcr().toString();
                    qDebug() << "mddt\t" << n.dtmd().toString();                      
                    
                    QDomNode dnNote = dnNotesChild.firstChild();                    
                    
                    while(!dnNote.isNull()){    //jo Notes elements
                        
                        if(dnNote.isElement()){
                            
                            QDomElement deNotesEl = dnNote.toElement();
                          
                            if(deNotesEl.tagName() == "Caption"){
                                QDomText dtCaptionText = deNotesEl.firstChild().toText();
                                qDebug() << "Caption\t" + dtCaptionText.data();
                                n.setCaption(dtCaptionText.data());
                            }else if(deNotesEl.tagName() == "Text"){
                                QDomText dtTextText = deNotesEl.firstChild().toText();
                                qDebug() << "Text\t" + dtTextText.data();
                                n.setText(dtTextText.data());
                            }else if(deNotesEl.tagName() == "Tags"){
                                QDomText dtTagsText = deNotesEl.firstChild().toText();
                                qDebug() << "Tags\t" + dtTagsText.data();
                                n.setTags(msiFromString(dtTagsText.data()));
                            }
                        }
                        
                        dnNote = dnNote.nextSibling();
                    }
                    
                    n.initEnd();
                    records_.append(n);
                    
                    dnNotesChild = dnNotesChild.nextSibling();
                }
            }
        }
        
        dnChild = dnChild.nextSibling();
    }
    
    return true;
}

NoteRecord NotesBase::item(const int index) const
{
    if(index < records_.size() && index >= 0){
        return records_.at(index);
    }else{
        return NoteRecord();
    }
}

void NotesBase::updateModifyTime()
{
    mddt_ = QDateTime::currentDateTime();
}

QDateTime NotesBase::dtFromString(const QString s)
{
    QDateTime dtRez;
    
    bool bRez;    
    uint uiBuff = s.toInt(&bRez);
    if(bRez){
        dtRez = QDateTime::fromTime_t(uiBuff);
    }else{
        dtRez = QDateTime::fromTime_t(0);
    }
    
    return dtRez;
}

void NotesBase::adsorbTagsFromRecord(const NoteRecord &rec)
{
    foreach (QString key, rec.tags().keys()) {
        if(key.isEmpty()){
            continue;
        }
        if(tags_.contains(key)){
            tags_[key]++;
            qDebug() << "[notebase]inc tag[" << key << "]" << QString::number(tags_.value(key));
        }else{
            tags_[key] = 1;
            qDebug() << "[notebase]new tag:" << key;
        }
    }
}

int NotesBase::size() const
{
    return records_.size();
}
          

QMap<QString, int> NotesBase::tags() const
{
	return tags_;
}

void NotesBase::setTags(const QMap<QString, int> &tags)
{
	if(tags_ != tags){
		tags_ = tags;
    }
}

void NotesBase::setTags(const QString str)
{
    tags_ = msiFromString(str);
}
