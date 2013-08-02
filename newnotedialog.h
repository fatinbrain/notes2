#ifndef NEWNOTEDIALOG_H
#define NEWNOTEDIALOG_H

#include <QDialog>
#include <QDebug>
#include "datastruct/noterecord.h"

namespace Ui {
class NewNoteDialog;
}

class NewNoteDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewNoteDialog(QWidget *parent = 0);
    ~NewNoteDialog();
    
    NoteRecord rezult()const;
    void setAvailableTags(const QMap<QString, int> &tags);
    void clearData();
    void setNote(const NoteRecord& nr);
    
    
private slots:
    void renderTags();
    void actRenderAvailableTags(QMap<QString, int> tags);
    void checkEnablePbNewTag(const QString str);
    void validateNote();
    void checkTagsButtons();
    
    void on_buttonBox_accepted();
    void on_pbNewTag_clicked();    
    void on_pbAddTag_clicked();    
    void on_pbRemoveTag_clicked();
    
private:
    Ui::NewNoteDialog *ui;
    
    NoteRecord note_;
    QMap<QString, int> tags_;
    
    void renderNote();
};

#endif // NEWNOTEDIALOG_H
