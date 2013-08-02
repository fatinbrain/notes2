#include "mapTool.h"

QString msiToString(const QMap<QString, int> map, 
                    QString keyValueSeparator,
                    QString wordsSepeartor){
    QString sBuff("");
    
    QMap<QString, int>::const_iterator it;
    for(it = map.begin(); it != map.end(); it++){
        if(!it.key().isEmpty()){
            sBuff += it.key().simplified() + keyValueSeparator + 
                    QString::number(it.value()) + wordsSepeartor;
        }
    }
    
    return sBuff;
}

QMap<QString, int> msiFromString(const QString str, 
                                 QString keyValueSeparator,
                                 QString wordsSepeartor){
    if(str.isNull() || str.isEmpty()){
        return QMap<QString, int>();
    }
    
    QMap<QString, int> buff;
    
    QStringList slWords = str.split(wordsSepeartor);
    foreach (QString s, slWords) {
        QString keyBuff = s.left(s.lastIndexOf(keyValueSeparator)).simplified();
        bool rez;
        int valueBuff = s.right(s.length() - s.lastIndexOf(keyValueSeparator) - 1).toInt(&rez);
        if(!rez){
            valueBuff = -1;
        }        
        buff[keyBuff] = valueBuff;
    }    
    return buff;
}


QString msiToSimpleString(const QMap<QString, int> map, QString wordsSepeartor)
{
    QString s;
    
    foreach(QString k, map.keys()){
        if(!k.isEmpty()){
            s += k + wordsSepeartor;
        }
    }
    
    s = s.left(s.length() - 1);
    
    return s;
}
