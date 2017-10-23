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

        virtual void prepareIteration(Container<ValueT> *container, int iteration)
        {
            m_valuefactory->reset(iteration);
            for(int i = 0; i < m_newkeysperiteration; i++)
            {
                container->set(container->keys(),m_valuefactory->getNextValue());
            }
        }

        virtual void finishIteration(Container<ValueT> *container, int iteration)
        {
        }

        virtual void runIteration(Container<ValueT> *container, int iteration)
        {
            int keys = container->keys();
            srand(iteration * 12378);

            for(int i = 0; i < m_readsperiteration; i++)
            {
                int index = container->index(rand()%keys);
                if (index >= 0)
                {
                    ValueT v = container->operator [](index).second;
                }
            }

        }


        ReadRandomAccess(
                Container<ValueT> *refcontainer,
                ValueFactory<ValueT> *valuefactory,
              int newkeysperiteration = 1000,
              int readsperiteration = 100,
              QObject *parent = nullptr)
            : Templated(refcontainer, parent),
              m_valuefactory(valuefactory),
              m_newkeysperiteration(newkeysperiteration),
              m_readsperiteration(readsperiteration)
        {

        }

        ~ReadRandomAccess()
        {
            delete m_valuefactory;
        }

    private:
        ValueFactory<ValueT> *m_valuefactory;
        int m_newkeysperiteration;
        int m_readsperiteration;
    };

}


#endif // SCENARIO_READABILITY_H
