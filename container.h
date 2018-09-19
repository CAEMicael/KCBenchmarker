#ifndef CONTAINER_H
#define CONTAINER_H
#include <utility>
#include <QString>

typedef long long TimeT;

/**
 * The ValueT is expected to have a valid copy constructor and assignment operator.
 *
 */
template<class ValueT>
class Container
{
public:
    virtual QString name() const = 0;

    /**
     * @brief Returns the timestamp and value for the key with the specified index.
     * @param index
     * @return
     */
    virtual std::pair<TimeT,ValueT> operator[](int index) const = 0;
    /**
     * @brief Returns the index of the key whose timestamp is closest and less than given timestamp.
     * @param time
     * @return
     */
    virtual int index(TimeT time) const = 0;
    /**
     * @brief Removes all keys at and beyond the given timestamp.
     * @param afterAndAt
     */
    virtual void truncate(TimeT afterAndAt) = 0;

    /**
     * @brief Sets and possibly overwrites the value at the specified timestamp.
     * @param timestamp
     * @param value
     */
    virtual void set(TimeT timestamp, const ValueT &value) = 0;

    virtual int keys() const = 0;

    Container()
    {

    }

    virtual ~Container()
    {

    }
};



#endif // CONTAINER_H
