#include "scenarioresult.h"
#include "ui_scenarioresult.h"
#include <QTextStream>


void ScenarioResult::addContainer(int containerid, QString name)
{
    QString msg;
    QTextStream s(&msg);
    s << "Start evaluating new container: " << name << " (id: " << containerid << ").";
    ui->messages->addItem(msg);

    QColor color = Qt::gray;
    if (containerid >= 0)
    {
        color = m_colors.back();
        m_colors.pop_back();
    }
    ui->graph->addLine(containerid,name,color);


    QListWidgetItem *item = new QListWidgetItem(name);
    item->setForeground(QBrush(color));
    ui->legend->addItem(item);
}


void ScenarioResult::finishContainerBenchmark(int containerid)
{
    QString msg;
    QTextStream s(&msg);
    s << "Finished evaluating container, id: " << containerid << ".";
    ui->messages->addItem(msg);
    ui->messages->scrollToBottom();
}

void ScenarioResult::addIterationResult(int containerid, int iteration, int duration)
{
//    QString msg;
//    QTextStream s(&msg);
//    s << containerid << ", iteration " << iteration << ": " << duration;
//    ui->messages->addItem(msg);
//    ui->messages->scrollToBottom();

}

void ScenarioResult::addErrorMessage(int containerid, QString msg)
{
    QString mmsg;
    QTextStream s(&mmsg);
    s << containerid << ": " << msg;
    ui->messages->addItem(mmsg);
    ui->messages->scrollToBottom();
}

ScenarioResult::ScenarioResult(Scenario *scenario, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScenarioResult)
{
    m_colors.push_back(Qt::darkRed);
    m_colors.push_back(Qt::darkGreen);
    m_colors.push_back(Qt::darkBlue);
    m_colors.push_back(Qt::cyan);
    m_colors.push_back(Qt::magenta);
    m_colors.push_back(Qt::red);
    m_colors.push_back(Qt::green);
    m_colors.push_back(Qt::blue);



    ui->setupUi(this);
    QObject::connect(scenario,SIGNAL(benchmarkStarted(int,QString)),this,SLOT(addContainer(int,QString)));
    QObject::connect(scenario,SIGNAL(benchmarkFinished(int)),this,SLOT(finishContainerBenchmark(int)));
    QObject::connect(scenario,SIGNAL(iterationFinished(int,int,int)),this,SLOT(addIterationResult(int,int,int)));
    QObject::connect(scenario,SIGNAL(evaluationFailed(int,QString)),this,SLOT(addErrorMessage(int,QString)));

//    QObject::connect(scenario,SIGNAL(benchmarkStarted(int,QString)),ui->graph,SLOT(addLine(int,QString)));
    QObject::connect(scenario,SIGNAL(iterationFinished(int,int,int)),ui->graph,SLOT(addPoint(int,int,int)));



    ui->name->setText(scenario->name());
}





ScenarioResult::~ScenarioResult()
{
    delete ui;
}
