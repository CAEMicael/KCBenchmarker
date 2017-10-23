#ifndef VALUEFACTORY_H
#define VALUEFACTORY_H

#include <QObject>

template<class ValueT>
class ValueFactory
{
public:
    ValueFactory() {};
    virtual void reset(int seed) = 0;
    virtual ValueT getNextValue() = 0;
signals:

public slots:
};


namespace valuefactory
{

template<class ValueT>
class DefaultConstructor : ValueFactory<ValueT>
{
public:
    virtual void reset(int seed) {};
    virtual ValueT getNextValue() {return ValueT();}

};

template<class ValueT>
class ConstantValue : public ValueFactory<ValueT>
{
public:
    ConstantValue(ValueT v) : m_value(v) {};
    virtual void reset(int seed) {};
    virtual ValueT getNextValue() {return m_value;}
private:
    ValueT m_value;
};




}
#endif // VALUEFACTORY_H
