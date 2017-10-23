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
            for(int i = 0; i < m_newkeysperiteration; i++)
            {
                container->set(rand(),m_valuefactory->getNextValue());
            }

        }


        WriteRandomAccess(
                Container<ValueT> *refcontainer,
                ValueFactory<ValueT> *valuefactory,
              int newkeysperiteration = 1000,
              QObject *parent = nullptr)
            : Templated(refcontainer, parent),
              m_valuefactory(valuefactory),
              m_newkeysperiteration(newkeysperiteration)
        {

        }

        ~WriteRandomAccess()
        {
            delete m_valuefactory;
        }

    private:
        ValueFactory<ValueT> *m_valuefactory;
        int m_newkeysperiteration;
    };

}




#endif // SCENARIO_WRITERANDOMACCESS_H
