#ifndef SCENARIORESULT_H
#define SCENARIORESULT_H

#include <QWidget>
#include "scenario.h"
#include <QColor>

namespace Ui {
class ScenarioResult;
}

class ScenarioResult : public QWidget
{
    Q_OBJECT

public:
    explicit ScenarioResult(Scenario *scenario, QWidget *parent = 0);
    ~ScenarioResult();


public slots:
    void addErrorMessage(int containerid, QString msg);
    void addIterationResult(int containerid, int iteration, int duration);
    void addContainer(int containerid, QString name);
    void finishContainerBenchmark(int containerid);
private:
    Ui::ScenarioResult *ui;
    std::vector<QColor> m_colors;
};

#endif // SCENARIORESULT_H
