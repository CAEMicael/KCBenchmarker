#ifndef SCENARIO_WRITERANDOMACCESS_H
#define SCENARIO_WRITERANDOMACCESS_H


#include "scenario_templated.h"
#include "container.h"
#include "valuefactory.h"

namespace scenario
{

    template<class ValueT>
    class WriteRandomAccess : public scenario::Templated<ValueT>
    {
    public:
        QString name() const {return "Write random access";}
        QString description() const { return "Writes keys all over the place in a completely random manner.";}

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
            m_valuefactory->reset(iteration);
            srand(iteration);
            for(int i = 0; i < m_writesperiteration; i++)
            {
                container->set(rand()%m_timespan,m_valuefactory->getNextValue());
            }

        }


        WriteRandomAccess(
                Container<ValueT> *refcontainer,
                ValueFactory<ValueT> *valuefactory,
                int keys = 100000,
                int writesperiteration = 1000,
              QObject *parent = nullptr)
            : Templated<ValueT>(refcontainer, parent),
              m_valuefactory(valuefactory),
              m_keys(keys),
              m_writesperiteration(writesperiteration)
        {

        }

        ~WriteRandomAccess()
        {
            delete m_valuefactory;
        }

    private:
        ValueFactory<ValueT> *m_valuefactory;
        int m_keys, m_timespan;
        int m_writesperiteration;
    };

}




#endif // SCENARIO_WRITERANDOMACCESS_H
