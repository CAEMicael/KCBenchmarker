#ifndef SCENARIO_ACCUMULATIVEWRITE_H
#define SCENARIO_ACCUMULATIVEWRITE_H

#include "scenario_templated.h"
#include "container.h"
#include "valuefactory.h"
#include <memory>
#include <QElapsedTimer>

namespace scenario
{
    template<class ValueT>
    class ContinousRecording : public scenario::Templated<ValueT>
    {
    public:
        QString name() const {return "Continous recording";}

        virtual void prepareIteration(Container<ValueT> *container, int iteration)
        {

        }

        virtual void finishIteration(Container<ValueT> *container, int iteration)
        {
        }

        virtual void runIteration(Container<ValueT> *container, int iteration)
        {
            m_valuefactory->reset(iteration);
            for(int subiteration = 0; subiteration < m_subiterationsperiteration; subiteration++)
            {
                int writeindex = subiteration + iteration*m_subiterationsperiteration;

                container->set(writeindex,m_valuefactory->getNextValue());
                for(int readiteration = 0; readiteration < m_readspersubiteration; readiteration++)
                {
                    int readindex = container->index(writeindex-readiteration);
                    if (readindex >= 0)
                    {
                        ValueT v = (*container)[readindex].second;
                    }
                }
            }
        }


        ContinousRecording(
                Container<ValueT> *refcontainer,
                ValueFactory<ValueT> *valuefactory,
              int subiterationsperiteration = 1000,
              int readspersubiteration = 30,
              QObject *parent = nullptr)
            : Templated(refcontainer, parent),
              m_valuefactory(valuefactory),
              m_subiterationsperiteration(subiterationsperiteration),
              m_readspersubiteration(readspersubiteration)
        {

        }

        ~ContinousRecording()
        {
            delete m_valuefactory;
        }

    private:
        ValueFactory<ValueT> *m_valuefactory;
        int m_subiterationsperiteration;
        int m_readspersubiteration;
    };

}


#endif // SCENARIO_ACCUMULATIVEWRITE_H
