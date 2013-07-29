#ifndef NOTES2_H
#define NOTES2_H

#include <QMainWindow>
#include <QMessageBox>

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
    void on_actionExit_triggered();
    void saveAndExit();
    
private:
    Ui::Notes2 *ui;
};

#endif // NOTES2_H
