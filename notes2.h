#ifndef NOTES2_H
#define NOTES2_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QDialog>

#include "newnotedialog.h"
#include "notesbase.h"
#include "noterecord.h"

namespace Ui {
class Notes2;
}

class Notes2 : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Notes2(QWidget *parent = 0);
    ~Notes2();
    
private slots:
    void saveAndExit();
    void actAddNewNote();
    void actRenderBase();
    void actRenderNote(const int index);
    void checkRmNoteAvailable(const int index);
    
    void on_actionExit_triggered();
    void on_actionAdd_note_triggered();
    void on_pbReadBase_clicked();    
    void on_pb_clicked();
    
private:
    Ui::Notes2 *ui;
    
    NotesBase nb;
    QAction* aRmNote;
};

#endif // NOTES2_H
