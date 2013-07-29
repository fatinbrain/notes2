#ifndef NEWNOTEDIALOG_H
#define NEWNOTEDIALOG_H

#include <QDialog>
#include "noterecord.h"

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
    void setTags(const QString& tags);
    
private slots:
    void on_buttonBox_accepted();
    
    void actRenderTags();
    void checkEnablePbNewTag(const QString str);
    void validateNote();
    
    void on_pbNewTag_clicked();
    
private:
    Ui::NewNoteDialog *ui;
    
    NoteRecord note_;
    QString tags_;
};

#endif // NEWNOTEDIALOG_H
