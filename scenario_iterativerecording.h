#ifndef SCENARIO_ITERATIVERECORDING_H
#define SCENARIO_ITERATIVERECORDING_H


#include "scenario_templated.h"
#include "container.h"
#include "valuefactory.h"
#include <memory>
#include <QElapsedTimer>

namespace scenario
{
    template<class ValueT>
    class IterativeRecording : public scenario::Templated<ValueT>
    {
    public:
        QString name() const {return "Iterative recording";}
        QString description() const { return "Performs a continous recording, then truncates the recording at some random point. Loops.";}

        virtual void prepareIteration(Container<ValueT> *container, int iteration)
        {

        }

        virtual void finishIteration(Container<ValueT> *container, int iteration)
        {
        }

        virtual void runIteration(Container<ValueT> *container, int iteration)
        {
            m_valuefactory->reset(iteration);

            srand(iteration);

            int currenttime = rand()%m_timespan;

            container->truncate(currenttime);

            for(int subiteration = 0; subiteration < m_subiterationsperiteration; subiteration++, currenttime += (rand()%5) + 1)
            {
                //Simulate some reading.
                for(int readiteration = 0, readpos = currenttime-1; readiteration < m_readspersubiteration; readiteration++, readpos -= (rand()%5) + 1)
                {
                    int readindex = container->index(readpos);
                    if (readindex >= 0)
                    {
                        ValueT v = (*container)[readindex].second;
                    }
                }

                container->set(currenttime, m_valuefactory->getNextValue());
            }
        }


        IterativeRecording(
                Container<ValueT> *refcontainer,
                ValueFactory<ValueT> *valuefactory,
                int timespan = 1000000,
              int subiterationsperiteration = 1000,
              int readspersubiteration = 30,
              QObject *parent = nullptr)
            : Templated<ValueT>(refcontainer, parent),
              m_valuefactory(valuefactory),
              m_subiterationsperiteration(subiterationsperiteration),
              m_readspersubiteration(readspersubiteration),
              m_timespan(timespan)
        {

        }

        ~IterativeRecording()
        {
            delete m_valuefactory;
        }

    private:
        ValueFactory<ValueT> *m_valuefactory;
        int m_subiterationsperiteration;
        int m_readspersubiteration;
        int m_timespan;
    };

}


#endif // SCENARIO_ITERATIVERECORDING_H
