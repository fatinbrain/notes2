#include "newnotedialog.h"
#include "ui_newnotedialog.h"

NewNoteDialog::NewNoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewNoteDialog)
{
    ui->setupUi(this);
    ui->pbNewTag->setEnabled(false);
    ui->leNewTag->setText("");
    
    connect(ui->leNewTag, SIGNAL(textChanged(QString)),
            this, SLOT(checkEnablePbNewTag(QString)));
}

NewNoteDialog::~NewNoteDialog()
{
    delete ui;
}

NoteRecord NewNoteDialog::rezult() const
{
    return note_;
}

void NewNoteDialog::setTags(const QString &tags)
{
    tags_ = tags;
    actRenderTags();
}

void NewNoteDialog::on_buttonBox_accepted()
{
    note_.setCaption(ui->leCaption->text());
    note_.setText(ui->teText->toPlainText());
    note_.setDtmd(QDateTime::currentDateTime());
}

void NewNoteDialog::actRenderTags()
{
    ui->lwTagsAvailable->clear();
    ui->lwTagsAvailable->addItems(tags_.split(','));    
}

void NewNoteDialog::checkEnablePbNewTag(const QString str)
{
    ui->pbNewTag->setEnabled(!str.isEmpty());
}

void NewNoteDialog::validateNote()
{
    if(!ui->leCaption->text().isNull() 
            && !ui->teText->toPlainText().isEmpty()){
        
    }
}

void NewNoteDialog::on_pbNewTag_clicked()
{
    tags_ += "," + ui->leNewTag->text();
    actRenderTags();
}
