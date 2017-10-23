#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scenario.h"
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    std::vector<Scenario*> createScenarios() const;

public slots:
    void run();

private:
    Ui::MainWindow *ui;
    QThread *m_workthread;
};

#endif // MAINWINDOW_H
