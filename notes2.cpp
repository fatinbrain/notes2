#include "notes2.h"
#include "ui_notes2.h"

Notes2::Notes2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notes2)
{
    ui->setupUi(this);
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
    QMessageBox::information(this, "action exit", "will save base\nand exit");
    close();
}

void Notes2::actAddNewNote()
{
    qDebug() << QString("[notes2] attempt to add new note");
    NewNoteDialog* nnDialog = new NewNoteDialog();
    nnDialog->show();
} 

void Notes2::on_actionAdd_note_triggered()
{
    actAddNewNote();
}
