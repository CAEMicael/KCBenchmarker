#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "scenario_continousrecording.h"
#include "scenario_readrandomaccess.h"
#include "scenario_writerandomaccess.h"
#include "scenario_iterativerecording.h"
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

    scenario::Templated<double> *scenario_double;
    std::vector<Container<double>*> containers_double;


    scenario_double = new scenario::ContinousRecording<double>(
                new ReferenceContainer<double>(),
                new valuefactory::ConstantValue<double>(0.0),
                10000,
                30,
                nullptr
                );

    containers_double = createEvalContainers<double>();
    for(size_t i = 0; i < containers_double.size(); i++)
        scenario_double->addContainer(containers_double[i]);
    ret.push_back(scenario_double);



    scenario_double = new scenario::IterativeRecording<double>(
                new ReferenceContainer<double>(),
                new valuefactory::ConstantValue<double>(0.0),
                1000000,
                10000,
                30,
                nullptr
                );
    containers_double = createEvalContainers<double>();
    for(size_t i = 0; i < containers_double.size(); i++)
        scenario_double->addContainer(containers_double[i]);
    ret.push_back(scenario_double);



    scenario_double = new scenario::ReadRandomAccess<double>(
                new ReferenceContainer<double>(),
                new valuefactory::ConstantValue<double>(0.0),
                10000,
                1000,
                nullptr
                );
    containers_double = createEvalContainers<double>();
    for(size_t i = 0; i < containers_double.size(); i++)
        scenario_double->addContainer(containers_double[i]);
    ret.push_back(scenario_double);



    scenario_double = new scenario::WriteRandomAccess<double>(
                new ReferenceContainer<double>(),
                new valuefactory::ConstantValue<double>(0.0),
                10000,
                1000,
                nullptr
                );
    containers_double = createEvalContainers<double>();
    for(size_t i = 0; i < containers_double.size(); i++)
        scenario_double->addContainer(containers_double[i]);
    ret.push_back(scenario_double);




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
