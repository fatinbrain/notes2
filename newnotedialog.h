#ifndef NEWNOTEDIALOG_H
#define NEWNOTEDIALOG_H

#include <QDialog>

namespace Ui {
class NewNoteDialog;
}

class NewNoteDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewNoteDialog(QWidget *parent = 0);
    ~NewNoteDialog();
    
private:
    Ui::NewNoteDialog *ui;
};

#endif // NEWNOTEDIALOG_H
