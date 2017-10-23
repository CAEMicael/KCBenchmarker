#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "scenario_simulatedrecording.h"
#include "scenario_readrandomaccess.h"
#include "scenario_writerandomaccess.h"
#include "referencecontainer.h"
#include "scenarioresult.h"
#include <QTimer>

void MainWindow::run()
{
    ui->resultList->clear();
    std::vector<Scenario*> scenarios = createScenarios();
    for(int si = 0; si < (int)scenarios.size(); si++)
    {
        Scenario *s = scenarios[si];
        s->moveToThread(m_workthread);
        QObject::connect(s,SIGNAL(finished()),s,SLOT(deleteLater()));


        ScenarioResult *widget = new ScenarioResult(s, ui->resultList);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(widget->sizeHint());
        ui->resultList->addItem(item);
        ui->resultList->setItemWidget(item,widget);

        QMetaObject::invokeMethod(s,"run",Q_ARG(int,ui->iterations->value()),Q_ARG(bool,ui->evaluate->isChecked()));


//        s->run(ui->iterations->value(),ui->evaluate->isChecked());

    }
}



std::vector<Scenario*> MainWindow::createScenarios() const
{
    std::vector<Scenario*> ret;

    scenario::SimulatedRecording<double> *s1 = new scenario::SimulatedRecording<double>(
                new ReferenceContainer<double>(),
                new valuefactory::ConstantValue<double>(0.0),
                100,
                30,
                nullptr
                );
    s1->addContainer(new ReferenceContainer<double>());
    ret.push_back(s1);


    scenario::ReadRandomAccess<double> *s2 = new scenario::ReadRandomAccess<double>(
                new ReferenceContainer<double>(),
                new valuefactory::ConstantValue<double>(0.0),
                100,
                1000,
                nullptr
                );
    s2->addContainer(new ReferenceContainer<double>());
    ret.push_back(s2);

    scenario::WriteRandomAccess<double> *s3 = new scenario::WriteRandomAccess<double>(
                new ReferenceContainer<double>(),
                new valuefactory::ConstantValue<double>(0.0),
                1000,
                nullptr
                );
    s3->addContainer(new ReferenceContainer<double>());
    ret.push_back(s3);


    return ret;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_workthread = new QThread();
    m_workthread->start();
    QObject::connect(m_workthread,SIGNAL(finished()),m_workthread,SLOT(deleteLater()));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    m_workthread->exit();
    delete ui;
}
