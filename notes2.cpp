#include "notes2.h"
#include "ui_notes2.h"

Notes2::Notes2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notes2)
{
    ui->setupUi(this);
    connect(ui->lwNotes, SIGNAL(currentRowChanged(int)),
            this, SLOT(actRenderNote(int)));
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
    qDebug() << "[action exit]will save base\nand exit";
    close();
}

void Notes2::actAddNewNote()
{
    qDebug() << QString("[notes2] attempt to add new note");
    
    NewNoteDialog* nnDialog = new NewNoteDialog();
    nnDialog->setTags(nb.tags());
    
    if(nnDialog->exec() == QDialog::Accepted){        
        NoteRecord n = nnDialog->rezult();
        nb.add(n);
        actRenderBase();
    }else{
        qDebug() << "[dia rez]rejected";
    }    
}

void Notes2::actRenderBase()
{
    ui->lwNotes->clear();
    for(int i = nb.size() - 1; i >= 0; i--){
        ui->lwNotes->addItem(nb.item(i).caption());
    }
}

void Notes2::actRenderNote(const int index)
{
    if(index >=0 && index < nb.size()){
        ui->teNoteText->clear();
        ui->teNoteText->append(nb.item(nb.size() - index - 1).text());
    }
} 

void Notes2::on_actionAdd_note_triggered()
{
    actAddNewNote();
}

void Notes2::on_pbReadBase_clicked()
{
    NoteRecord nr;
    nr.setCaption("first cap");
    nr.setText("first text\nin two lines");    
    nb.add(nr);
    nr.setCaption("second cap");
    nr.setText("second text\nin three\n\tlines");    
    nb.add(nr);
    nb.setTags("a,b,c,d");
    
    actRenderBase();
}
