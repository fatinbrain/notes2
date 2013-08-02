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
#include <QTextBlock>

#include "newnotedialog.h"
#include "datastruct/notesbase.h"
#include "datastruct/noterecord.h"
#include "markdown/markdowncxx.h"

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
    void renderBase();
    void renderNote(const int index);    
    void checkRmNoteAvailable(const int currentIndex = -1);
    void readBase(const QString fname);
    void updateNoteTime();
    QString getNewBaseFileName();    
    void editCurrentNote();
    
    void on_actionExit_triggered();
    void on_actionAdd_note_triggered();
    void on_pbReadBase_clicked();
    void on_pb_clicked();
    void on_actionAbout_Qt_triggered();
    void on_actionAbout_program_triggered();
    void on_pbRemoveNote_clicked();
    void on_actionRemove_note_triggered();
    
    void on_actionOpen_base_triggered();
    
    void on_actionEdit_note_triggered();
    
private:
    Ui::Notes2 *ui;
    
    NotesBase nb;
    QString fname;
    QString sCss;
    
    QAction* aRmNote;
    QTimer* tmr;    
    
    QString ago(const double value);
    void readCss();
    void readSettings();
    void writeSettings();
    int reversedIndex();
};

#endif // NOTES2_H
