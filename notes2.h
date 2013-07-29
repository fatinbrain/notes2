#ifndef NOTES2_H
#define NOTES2_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>

#include "newnotedialog.h"

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
    
    void on_actionExit_triggered();
    void on_actionAdd_note_triggered();
    
private:
    Ui::Notes2 *ui;
};

#endif // NOTES2_H
