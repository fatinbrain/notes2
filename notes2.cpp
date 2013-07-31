#include "notes2.h"
#include "ui_notes2.h"

Notes2::Notes2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notes2)
{
    ui->setupUi(this);
    
    ui->mainToolBar->actions().at(1)->setEnabled(false);
    
    tmr = new QTimer(this);
    tmr->start(1000);
    
    connect(ui->lwNotes, SIGNAL(currentRowChanged(int)),
            this, SLOT(actRenderNote(int)));
    connect(ui->lwNotes, SIGNAL(currentRowChanged(int)),
            this, SLOT(checkRmNoteAvailable(int)));
    connect(tmr, SIGNAL(timeout()),
            this, SLOT(updateNoteTime()));
    
    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, qApp->applicationDirPath());
    
    fname = "";
    readSettings();
    
    if(QFile::exists(fname)){
        readBase(fname);
    }else{
        QString f = QFileDialog::getOpenFileName(this, "Open base", qApp->applicationDirPath());
        if(QFile::exists(f)){
            fname = f;            
        }else{
            fname = "base.xml";
        }
        readBase(fname);
    }
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
    nb.writeToXML("base.xml");
    writeSettings();
    close();
}

void Notes2::addNewNote()
{
    qDebug() << QString("[notes2] attempt to add new note");
    
    NewNoteDialog* nnDialog = new NewNoteDialog(this);
    qDebug() << "set available tags to record:" << msiToString(nb.tags());
    nnDialog->setAvailableTags(nb.tags());
    
    if(nnDialog->exec() == QDialog::Accepted){        
        NoteRecord n = nnDialog->rezult();
        nb.add(n);
        nb.updateModifyTime();
        actRenderBase();
    }else{
        qDebug() << "[dia rez]rejected";
    }    
}

void Notes2::removeNote(const int index)
{
    nb.remove(nb.size() - index - 1);
    actRenderBase();
}

void Notes2::actRenderBase()
{
    ui->lwNotes->clear();
    
    for(int i = nb.size() - 1; i >= 0; i--){
        ui->lwNotes->addItem(nb.item(i).caption());
    }
    
    ui->teNoteText->clear();
    
    if(nb.size() > 0){
        ui->lwNotes->setCurrentRow(0);
    }
}

void Notes2::actRenderNote(const int index)
{
    if(!(index >= 0 && index < nb.size())){
        return;
    }
    
    int reversedIndex = nb.size() - index - 1;
    
    if(index >=0 && index < nb.size()){
        ui->teNoteText->clear();
        ui->teNoteText->append(nb.item(reversedIndex).text());
        ui->lCr->setText(nb.item(reversedIndex).dtcr().toString());
        ui->lCrAgo->setText(ago(-QDateTime::currentDateTime().secsTo(nb.item(reversedIndex).dtcr())));
        ui->lMd->setText(nb.item(reversedIndex).dtmd().toString());
        ui->lMdAgo->setText(ago(-QDateTime::currentDateTime().secsTo(nb.item(reversedIndex).dtmd())));
    }
}

void Notes2::checkRmNoteAvailable(const int index)
{
    bool isVaildIndex = (index >= 0);
    ui->pbRemoveNote->setEnabled(isVaildIndex);
    ui->mainToolBar->actions().at(1)->setEnabled(isVaildIndex);
}

void Notes2::readBase(const QString fname)
{
    nb.clear();
    nb.readFromXML(fname);
    ui->statusBar->showMessage(QString("Loaded from [%1], records[%2]").arg(fname).arg(nb.size()), 3000);
    actRenderBase();
}

void Notes2::updateNoteTime()
{
    if(ui->lwNotes->currentRow() != -1){
        actRenderNote(ui->lwNotes->currentRow());
    }
}

void Notes2::readSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    fname = settings.value("fname", "").toString();    
}

void Notes2::on_actionAdd_note_triggered()
{
    addNewNote();
}

void Notes2::on_pbReadBase_clicked()
{
    readBase("base.xml");
}

void Notes2::on_pb_clicked()
{
    qDebug() << "attempt to write base to xml";
    if(nb.writeToXML("base.xml")){
        qDebug() << "write norm";
        ui->statusBar->showMessage("write norm", 5000);
    }else{
        qDebug() << "write FAULT";
        ui->statusBar->showMessage("write FAULT", 5000);
    }
}

void Notes2::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void Notes2::on_actionAbout_program_triggered()
{
    QMessageBox::about(this, "About Notes2", "<h1>Notes 2</h1><p>Simple note management application</p>");
}

void Notes2::on_pbRemoveNote_clicked()
{
    removeNote(ui->lwNotes->currentRow());
}

void Notes2::on_actionRemove_note_triggered()
{
    removeNote(ui->lwNotes->currentRow());
}

QString Notes2::ago(const double value)
{
    QString rez = "";
    QString postfix = "secs";
    double val = value;
    
    if(val > 60){
        val /= 60;
        postfix = "mins";
        if(val > 60){
            val /= 60;
            postfix = "hours";
            if(val > 24){
                val /= 24;
                postfix = "days";
                if(val > 30){
                    val /= 30;
                    postfix = "months";
                    if(val > 12){
                        val /= 12;
                        postfix = "years";
                    }
                }
            }
        }
    }
    
    rez = QString::number(val, 'g', 2) + " " + postfix + " ago";
    
    return rez;
}


void Notes2::writeSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.setValue("fname", fname);
}
