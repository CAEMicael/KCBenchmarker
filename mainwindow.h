#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scenario.h"
#include "container.h"
#include "referencecontainer.h"
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


    template<class T>
    std::vector<Container<T>*> createEvalContainers() const;


    std::vector<Scenario*> createScenarios() const;

public slots:
    void run();

private:
    Ui::MainWindow *ui;
    QThread *m_workthread;
};


template<class T>
std::vector<Container<T>*> MainWindow::createEvalContainers() const
{
    std::vector<Container<T>*> ret;
    ret.push_back(new ReferenceContainer<double>());
    return ret;
}


#endif // MAINWINDOW_H
