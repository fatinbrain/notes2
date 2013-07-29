#include "newnotedialog.h"
#include "ui_newnotedialog.h"

NewNoteDialog::NewNoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewNoteDialog)
{
    ui->setupUi(this);
}

NewNoteDialog::~NewNoteDialog()
{
    delete ui;
}
