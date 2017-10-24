#ifndef SIMPLECONTAINER_H
#define SIMPLECONTAINER_H

#include <container.h>
#include <vector>
#include <utility>

template<class ValueT>
class ReferenceContainer : public Container<ValueT>
{
public:
    virtual QString name() const {return "ReferenceContainer";}

    std::pair<TimeT,ValueT> operator[] (int index) const
    {
        return m_data[index];
    }

    int keys() const {return (int)m_data.size();}

    int index(TimeT time) const
    {
        for(int num = keys()-1; num >= 0; num--)
        {
            if (m_data[num].first <= time) return num;
        }
        return -1;
    }

    void truncate(TimeT afterAndAt)
    {
        for(int num = 0; num < keys(); num++)
        {
            if (m_data[num].first >= afterAndAt)
            {
                m_data.resize(num);
                return;
            }
        }
    }

    void set(TimeT timestamp, const ValueT &value)
    {
        for(int i = (int)m_data.size()-1; i >= 0; i--)
        {
            if (timestamp == m_data[i].first)
            {
                m_data[i].second = value;
                return;
            }
            if (timestamp > m_data[i].first)
            {
                m_data.insert(m_data.begin() + i + 1,std::pair<TimeT,ValueT>(timestamp,value));
                return;
            }
        }
        m_data.insert(m_data.begin(),std::pair<TimeT,ValueT>(timestamp,value));
    }



    ReferenceContainer()
    {

    }

    virtual ~ReferenceContainer()
    {

    }
private:
    std::vector<std::pair<TimeT,ValueT>> m_data;
};

#endif // SIMPLECONTAINER_H
