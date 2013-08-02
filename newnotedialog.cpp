#include "newnotedialog.h"
#include "ui_newnotedialog.h"

NewNoteDialog::NewNoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewNoteDialog)
{
    this->setWindowTitle("New note");
    ui->setupUi(this);
    ui->pbNewTag->setEnabled(false);
    ui->leNewTag->setText("");
    
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    
    connect(ui->leNewTag, SIGNAL(textChanged(QString)),
            this, SLOT(checkEnablePbNewTag(QString)));
    connect(ui->leCaption, SIGNAL(textChanged(QString)),
            this, SLOT(validateNote()));
    connect(ui->teText, SIGNAL(textChanged()),
            this, SLOT(validateNote()));
    connect(ui->lwTagsAvailable, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(checkTagsButtons()));
    connect(ui->lwTags, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(checkTagsButtons()));
    
    checkTagsButtons();
}

NewNoteDialog::~NewNoteDialog()
{
    delete ui;
}

NoteRecord NewNoteDialog::rezult() const
{
    return note_;
}

void NewNoteDialog::setAvailableTags(const QMap<QString, int> &tags)
{
    actRenderAvailableTags(tags);
}

void NewNoteDialog::clearData()
{
    tags_.clear();
    note_.clear();
}

void NewNoteDialog::setNote(const NoteRecord &nr)
{
    if(nr.isValid()){
        note_ = nr;
        tags_ = note_.tags();
    }    
    
    renderNote();
}

void NewNoteDialog::on_buttonBox_accepted()
{
    note_.setCaption(ui->leCaption->text());
    note_.setText(ui->teText->toPlainText());
    note_.setDtmd(QDateTime::currentDateTime());
    note_.setTags(tags_);
}

void NewNoteDialog::renderTags()
{
    ui->lTags->setText(msiToSimpleString(tags_));
    
    ui->lwTags->clear();
    foreach (QString key, tags_.keys()) {
        if(!key.isEmpty()){
            ui->lwTags->addItem(key);
        }
    }
}

void NewNoteDialog::actRenderAvailableTags(QMap<QString, int> tags)
{
    ui->lwTagsAvailable->clear();
    foreach (QString key, tags.keys()) {
        if(!key.isEmpty() && !note_.tags().contains(key)){
            ui->lwTagsAvailable->addItem(key);
        }
    }
}

void NewNoteDialog::checkEnablePbNewTag(const QString str)
{
    ui->pbNewTag->setEnabled(!str.isEmpty());
}

void NewNoteDialog::validateNote()
{
    bool bValid = false;
    
    if(!ui->leCaption->text().isEmpty() 
            && !ui->teText->toPlainText().isEmpty()){
        bValid = true;
    }else{
        bValid = false;
    }
    
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(bValid);
}

void NewNoteDialog::checkTagsButtons()
{
    ui->pbAddTag->setEnabled(ui->lwTagsAvailable->currentRow() != -1);
    ui->pbRemoveTag->setEnabled(ui->lwTags->currentRow() != -1);
    qDebug() << ui->lwTagsAvailable->currentRow();
}

void NewNoteDialog::on_pbNewTag_clicked()
{
    tags_[ui->leNewTag->text()] = 0;
    ui->lwTags->addItem(ui->leNewTag->text());
    ui->leNewTag->setText("");
    renderTags();
}

void NewNoteDialog::on_pbAddTag_clicked()
{
    QString currTag = ui->lwTagsAvailable->currentItem()->text();
    
    if(currTag.isEmpty()){
        return;
    }
    
    tags_[currTag] = 0;
    note_.tags().insert(currTag, 0);
    ui->lwTags->addItem(currTag);
    delete ui->lwTagsAvailable->takeItem(ui->lwTagsAvailable->currentRow());

    renderTags();
}

void NewNoteDialog::on_pbRemoveTag_clicked()
{
    QString currTag = ui->lwTags->currentItem()->text();
    
    if(currTag.isEmpty()){
        return;
    }
    
    ui->lwTagsAvailable->addItem(currTag);
    delete ui->lwTags->takeItem(ui->lwTags->currentRow());
    tags_.remove(currTag);
    note_.tags().remove(currTag);
    
    renderTags();
}

void NewNoteDialog::renderNote()
{
    ui->teText->setText(note_.text());
    ui->leCaption->setText(note_.caption());
    renderTags();
}
