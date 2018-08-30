#ifndef SCENARIO_READABILITY_H
#define SCENARIO_READABILITY_H



#include "scenario_templated.h"
#include "container.h"
#include "valuefactory.h"

namespace scenario
{

    template<class ValueT>
    class ReadRandomAccess : public scenario::Templated<ValueT>
    {
    public:
        QString name() const {return "Read random access";}
        QString description() const {return "Reads values at random locations on a pre-set recording sequence.";}

        virtual void prepareIteration(Container<ValueT> *container, int iteration)
        {
            if (iteration == 0)
            {
                m_valuefactory->reset(iteration);
                srand(523948);
                int currenttime = 0;
                for(int num = 0; num < m_keys; num++, currenttime += 1)
                {
                    container->set(currenttime,m_valuefactory->getNextValue());
                }
                m_timespan = currenttime+1;
            }
        }

        virtual void finishIteration(Container<ValueT> *container, int iteration)
        {
        }

        virtual void runIteration(Container<ValueT> *container, int iteration)
        {
            srand(iteration * 12378);

            for(int i = 0; i < m_readsperiteration; i++)
            {
                int index = container->index(rand()%m_timespan);
                if (index >= 0)
                {
                    ValueT v = container->operator [](index).second;
                }
            }

        }


        ReadRandomAccess(
                Container<ValueT> *refcontainer,
                ValueFactory<ValueT> *valuefactory,
              int keys = 100000,
              int readsperiteration = 1000,
              QObject *parent = nullptr)
            : Templated(refcontainer, parent),
              m_valuefactory(valuefactory),
              m_keys(keys),
              m_readsperiteration(readsperiteration)
        {

        }

        ~ReadRandomAccess()
        {
            delete m_valuefactory;
        }

    private:
        ValueFactory<ValueT> *m_valuefactory;
        int m_keys, m_timespan;
        int m_readsperiteration;
    };

}


#endif // SCENARIO_READABILITY_H
