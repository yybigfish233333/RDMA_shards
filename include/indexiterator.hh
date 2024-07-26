#ifndef INDEXITERATOR_HH
#define INDEXITERATOR_HH
#include <utility>

namespace HtableRDMA{

template <typename Key,typename Value>
class IndexIterator{
    public:
        virtual ~Iterator(){}
        virtual bool hasNext() const=0;
        virtual std::pair<Key, Value> next() = 0;
        virtual void insert(const Key& key, const Value& value) = 0;
        virtual void remove(const Key& key) = 0;
        virtual Value* find(const Key& key) = 0;
        virtual void update(const Key& key, const Value& value) = 0;
        virtual std::pair<Key, Value> getFirst() const = 0;
};

}
#endif