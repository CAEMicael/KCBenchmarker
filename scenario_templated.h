#ifndef SCENATIO_TEMPLATED_H
#define SCENATIO_TEMPLATED_H

#include "scenario.h"
#include "container.h"
#include <qtextstream>

namespace scenario
{

    template<class ValueT>
    class Templated : public Scenario
    {
    public:
        Templated(Container<ValueT>* refcontainer, QObject *parent = nullptr)
            :Scenario(parent)
            ,m_refcontainer(refcontainer)
        {

        }

        void addContainer(Container<ValueT> *c)
        {
            m_testcontainers.push_back(c);
        }

        virtual ~Templated()
        {
            delete m_refcontainer;
            for(std::vector<Container<ValueT>*>::reverse_iterator iter = m_testcontainers.rbegin(); iter != m_testcontainers.rend(); iter++)
            {
                delete *iter;
            }
            m_testcontainers.clear();
        }

        int testContainers() const {return (int)m_testcontainers.size();}
        Container<ValueT> *testContainer(int index) const {return m_testcontainers[index];}




        virtual void run(int iterations, bool evaluateintegrity)
        {
            for(int cindex = 0; cindex < testContainers(); cindex++)
            {
                evalContainer(testContainer(cindex),cindex,iterations);
            }
            emit finished();

            if (evaluateintegrity)
            {
                evalContainer(m_refcontainer,-1,iterations);

                for(int cindex = 0; cindex < testContainers(); cindex++)
                {
                    Container<ValueT> *c = testContainer(cindex);

                    if (c->keys() != m_refcontainer->keys())
                    {
                        QString msg;
                        QTextStream stream(&msg);
                        stream << "Container size mismatch. Expected " << m_refcontainer->keys() << " keys, got " << c->keys() << ".";
                        emit evaluationFailed(cindex,msg);
                    }
                    else
                    {
                        int keys = m_refcontainer->keys();
                        std::vector<int> mismatchingkeys;
                        for(int kindex = 0; kindex < keys && mismatchingkeys.size() < 10; kindex++)
                        {
                            if (m_refcontainer->operator [](kindex) != c->operator [](kindex))
                                mismatchingkeys.push_back(kindex);
                        }

                        if (!mismatchingkeys.empty())
                        {
                            QString msg;
                            QTextStream stream(&msg);
                            stream << "Mismatching keys in container. First 10 mismatching indexes are: [";
                            for(int num = 0; num < (int)mismatchingkeys.size(); num++)
                            {
                                if (num != 0) stream << ",";
                                stream << mismatchingkeys[num];
                            }
                            stream << "].";
                            emit evaluationFailed(cindex,msg);
                        }

                    }

                }

            }

        }

       protected:
            virtual void prepareIteration(Container<ValueT> *container, int iteration) = 0;
            virtual void runIteration(Container<ValueT> *container, int iteration) = 0;
            virtual void finishIteration(Container<ValueT> *container, int iteration) = 0;

    private:
        Container<ValueT> *m_refcontainer;
        std::vector<Container<ValueT>*> m_testcontainers;

        void evalContainer(Container<ValueT> *container, int cindex, int iterations)
        {
            emit benchmarkStarted(cindex,container->name());
            for(int iteration = 0; iteration < iterations; iteration++)
            {
                QElapsedTimer timer;
                prepareIteration(container,iteration);
                timer.start();
                runIteration(container,iteration);
                emit iterationFinished(cindex, iteration,timer.elapsed());
                finishIteration(container,iteration);
            }
            emit benchmarkFinished(cindex);
        }


    };

}


#endif // SCENATIO_TEMPLATED_H
