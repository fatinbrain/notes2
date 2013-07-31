#ifndef NOTES2_H
#define NOTES2_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QDialog>
#include <QTimer>
#include <QSettings>
#include <QDir>
#include <QFileDialog>

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
    void addNewNote();
    void removeNote(const int index);
    void actRenderBase();
    void actRenderNote(const int index);
    void checkRmNoteAvailable(const int index);
    void readBase(const QString fname);
    void updateNoteTime();
    void readSettings();
    void writeSettings();
    
    void on_actionExit_triggered();
    void on_actionAdd_note_triggered();
    void on_pbReadBase_clicked();
    void on_pb_clicked();
    void on_actionAbout_Qt_triggered();
    void on_actionAbout_program_triggered();
    void on_pbRemoveNote_clicked();
    void on_actionRemove_note_triggered();
    
private:
    Ui::Notes2 *ui;
    
    NotesBase nb;    
    
    QAction* aRmNote;
    QTimer* tmr;    
    
    QString ago(const double value);
    QString fname;
};

#endif // NOTES2_H
