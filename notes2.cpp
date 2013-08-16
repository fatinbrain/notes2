#include "notes2.h"
#include "ui_notes2.h"

Notes2::Notes2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notes2)
{
    ui->setupUi(this);

    ui->menuNotes->actions().at(1)->setEnabled(false);  //edit note
    ui->menuNotes->actions().at(2)->setEnabled(false);  //remove note
    
    tmr = new QTimer(this);
    tmr->start(1000);
    
    connect(ui->lwNotes, SIGNAL(currentRowChanged(int)),
            this, SLOT(renderNote(int)));
    connect(ui->lwNotes, SIGNAL(currentRowChanged(int)),
            this, SLOT(checkRmNoteAvailable(int)));    
    connect(tmr, SIGNAL(timeout()),
            this, SLOT(updateNoteTime()));
    connect(ui->leSearch, SIGNAL(textChanged(QString)),
            this, SLOT(searchBase()));
    
    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, qApp->applicationDirPath());
    
    fname = "";
    readSettings();
    
    readCss();
    
    if(QFile::exists(fname)){
        readBase(fname);
    }else{
        QMessageBox::warning(this, "Base file error", 
            QString("Cannot open base file\n[%1].\nSelect existing base in next dialog...\n\tor press 'cancel' to create new base").arg(fname));
        fname = getNewBaseFileName();
        if(fname.isEmpty()){
            fname = "note2.xml";
        }
        readBase(fname);
    }
    
    ui->gbSearch->setVisible(false);
}

Notes2::~Notes2()
{
    delete ui;
}

void Notes2::on_actionExit_triggered()
{
    saveAndExit();
}

void Notes2::saveAndExit()
{
    qDebug() << "[action exit]will save base and exit";    
    nbOrig.writeToXML(fname);
    writeSettings();
    close();
}

void Notes2::addNewNote()
{
    qDebug() << QString("[notes2] attempt to add new note");
    
    NewNoteDialog* nnDialog = new NewNoteDialog(this);
    nnDialog->setAvailableTags(nbOrig.tags());
    nnDialog->clearData();
    
    if(nnDialog->exec() == QDialog::Accepted){        
        NoteRecord n = nnDialog->rezult();
        nbOrig.add(n);
        nbOrig.updateModifyTime();
        nb = nbOrig;
        renderBase();
    }else{
        qDebug() << "[dia rez]rejected";
    }
}

void Notes2::removeNote()
{
    if(QMessageBox::question(this, "Really?", "Are you shure to delete current note?", 
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::No) == QMessageBox::Yes){
        nbOrig.remove(nbOrig.indexByHash(currentItemHash()));
        nb = nbOrig;
        renderBase();
    }
}

void Notes2::renderBase()
{
    ui->lwNotes->clear();
    
    for(int i = nb.size() - 1; i >= 0; i--){
        ui->lwNotes->addItem(nb.item(i).caption());
    }
    
    ui->tbNoteText->clear();
    
    if(nb.size() > 0){
        ui->lwNotes->setCurrentRow(0);
    }
}

void Notes2::renderNote(const int index)
{
    if(index >=0 && index < nb.size()){
        std::string stdHtml;
        markdown2html(nb.item(reversedIndex()).text().toStdString(), stdHtml);
        QString sHtml = QString::fromStdString(stdHtml);
        sHtml = "<body>" + sHtml + "</body>";

        QTextDocument *td = new QTextDocument(this);
        td->setDefaultStyleSheet(sCss);
        td->setHtml(sHtml);        
//        qDebug() << sHtml;
        
        ui->tbNoteText->clear();
        ui->tbNoteText->setDocument(td);
        
        QString tagline = msiToSimpleString(nb.item(reversedIndex()).tags());
        if(tagline.isEmpty()){
            tagline = "na";
        }
        ui->lTags->setText(tagline);
        
        updateNoteTime();
    }
}

void Notes2::checkRmNoteAvailable(const int currentIndex)
{
    int index = currentIndex;
    if(index == -1){
        index = ui->lwNotes->currentRow();
    }
    
    bool isVaildIndex = (index >= 0);
    ui->pbRemoveNote->setEnabled(isVaildIndex);
    ui->pbXAction->setEnabled(isVaildIndex);
    ui->menuNotes->actions().at(1)->setEnabled(isVaildIndex/* && canEdit*/);
    ui->menuNotes->actions().at(2)->setEnabled(isVaildIndex);
}

void Notes2::readBase(const QString fname)
{   
    nbOrig.clear();
    nbOrig.readFromXML(fname);
    ui->statusBar->showMessage(QString("Loaded from [%1], records[%2]").arg(fname).arg(nbOrig.size()), 3000);
 
    if(boBackupOn && QFile::exists(fname)){
        QFile::copy(fname, "backup.xml");
    }
    
    nb = nbOrig;
    
    renderBase();
}

int Notes2::reversedIndex()
{
    int reversedIndex = nb.size() - ui->lwNotes->currentRow() - 1;
    
    return reversedIndex;
}

uint Notes2::currentItemHash()
{
    if(ui->lwNotes->currentRow() < 0){
        return 0;
    }else{
        return nb.itemHash(reversedIndex());
    }
}

void Notes2::updateNoteTime()
{
    if(ui->lwNotes->currentRow() == -1){
        return;        
    }
    
    int index = reversedIndex();
    
    if(index >=0 && index < nb.size()){
        ui->lCr->setText(nb.item(index).dtcr().toString());
        ui->lCrAgo->setText(ago(-QDateTime::currentDateTime().secsTo(nb.item(index).dtcr())));
        ui->lMd->setText(nb.item(index).dtmd().toString());
        ui->lMdAgo->setText(ago(-QDateTime::currentDateTime().secsTo(nb.item(index).dtmd())));
    }
}

QString Notes2::getNewBaseFileName()
{
    QString f = QFileDialog::getOpenFileName(
                this, "Open base", qApp->applicationDirPath(), 
                "xml base(*.xml);;all files(*.*)");
    if(f.isEmpty()){
        return "";
    }

    return f;
}


void Notes2::writeSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.setValue("fname", fname);
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());
    settings.setValue("doBackup", boBackupOn);
}

void Notes2::readSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    fname = settings.value("fname", "").toString();
    boBackupOn = settings.value("doBackup", true).toBool();
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());
}

void Notes2::on_actionAdd_note_triggered()
{
    addNewNote();
}

void Notes2::editCurrentNote()
{
    if(ui->lwNotes->currentRow() >= 0){
        qDebug() << QString("[notes2] attempt to edit note");
        
        NewNoteDialog* nnDialog = new NewNoteDialog(this);
        nnDialog->clearData();
        uint currItemHash = nb.itemHash(reversedIndex());
        nnDialog->setNote(nbOrig.itemByHash(currItemHash));
        nnDialog->setAvailableTags(nbOrig.tags());
        
        if(nnDialog->exec() == QDialog::Accepted){        
            NoteRecord n = nnDialog->rezult();
            nbOrig.setItem(nbOrig.indexByHash(currItemHash), n);
            nbOrig.updateModifyTime();
            nb = nbOrig;
            searchBase();
            renderBase();
        }else{
            qDebug() << "[dia rez]rejected";
        } 
    }    
}

void Notes2::searchBase()
{
    if(ui->leSearch->text().isEmpty()){
        nb = nbOrig;        
        ui->gbSearch->setTitle("Search");
    }else{
        nb.clear();
        
        for(int i = 0; i < nbOrig.size(); i++){
            if(nbOrig.item(i).text().contains(ui->leSearch->text(), Qt::CaseInsensitive)){
                nb.add(nbOrig.item(i));
            }
        }
        
        ui->gbSearch->setTitle(QString("Search [%1/%2]").arg(nb.size()).arg(nbOrig.size()));
    }
        
    renderBase();

}

void Notes2::on_pb_clicked()
{
    ui->gbSearch->setVisible(!ui->gbSearch->isVisible());
}

void Notes2::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void Notes2::on_actionAbout_program_triggered()
{
    QString aboutText = QString("<h1>Notes 2</h1><h3>version [%1]</h3><p>Simple note management application<br/>with <strong>markdown</strong> support.</p>")
            .arg(APP_VER);
    QMessageBox::about(this, "About Notes2", aboutText);
}

void Notes2::on_pbRemoveNote_clicked()
{
    removeNote();
}

void Notes2::on_actionRemove_note_triggered()
{
    removeNote();
}

QString Notes2::ago(const double value)
{
    QString rez = "";
    QString postfix = "s";
    double val = value;
    
    if(val > 60){
        val /= 60;
        postfix = "m";
        if(val > 60){
            val /= 60;
            postfix = "h";
            if(val > 24){
                val /= 24;
                postfix = "d";
                if(val > 30){
                    val /= 30;
                    postfix = "mo";
                    if(val > 12){
                        val /= 12;
                        postfix = "ye";
                    }
                }
            }
        }
    }
    
    rez = QString::number(val, 'g', 2) + "" + postfix + " ago";
    
    return rez;
}

void Notes2::readCss()
{   
    QFile f("default.css");
    if(f.open(QIODevice::ReadOnly | QIODevice::Text)){
        sCss = f.readAll();
        f.close();
        qDebug() << "read css from [default.css]";
    }else{
        sCss = "body{background-color:silver;font-family:georgia,serif}em{color:black;}h1,h2,h3,h4,h5,h6{font-family:sans-serif;}p{text-indent:20px;}";
        qDebug() << "cannot read [default.css], use default css";
    }
}

void Notes2::on_actionOpen_base_triggered()
{
    QString newFName = getNewBaseFileName();
    if(!newFName.isEmpty()){
        fname = newFName;
        readBase(fname);
    }
}

void Notes2::on_actionEdit_note_triggered()
{
    editCurrentNote();
}

void Notes2::on_pbXAction_clicked()
{
    editCurrentNote();
}

void Notes2::on_lwNotes_doubleClicked(const QModelIndex &index)
{
    editCurrentNote();
}

void Notes2::on_pbSearchClear_clicked()
{
    ui->leSearch->setText("");
}

void Notes2::on_actionSearch_triggered()
{
    ui->gbSearch->setVisible(!ui->gbSearch->isVisible());
}
