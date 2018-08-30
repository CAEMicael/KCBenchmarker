#ifndef SCENARIO_H
#define SCENARIO_H

#include <QObject>
#include <QString>

class Scenario : public QObject
{
    Q_OBJECT
public:
    virtual QString name() const = 0;
    virtual QString description() const = 0;

    explicit Scenario(QObject *parent = nullptr);
signals:
    void benchmarkStarted(int containerindex, QString name);
    void iterationFinished(int containerindex, int iteration, int duration);
    void benchmarkFinished(int containerIndex);
    void evaluationFailed(int containerIndex, QString message);
    void finished();


public slots:
    virtual void run(int iterations, bool evaluateintegrity) = 0;
};


#endif // SCENARIO_H
