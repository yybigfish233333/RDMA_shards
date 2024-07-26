#ifndef BPLUSTREEITERATOR_HH
#define BPLUSTREEITERATOR_HH
#include "indexiterator.hh"
#include <vector>

namespace HtableRDMA{
    template <typename Key,typename Value>
    class BPlusTreeNode{
        public:
            bool isLeaf;
            std::vector<Key> keys;
            std::vector<Value> values;//只给叶节点用
            std::vector<BPlusTreeNode<Key,Value>*> children;

            BPlusTreeNode(bool leaf = false): isLeaf(leaf){}
    };

    template <typename Key,typename Value>
    class BPlusTreeIterator: public IndexIterator<Key,Value>{
        public:
            BPlusTreeIterator(BPlusTreeNode<Key,Value>* root);
            ~BPlusTreeIterator();

            bool hasNext() const override;
            std::pair<Key, Value> next() override;
            void insert(const Key& key, const Value& value) override;
            void remove(const Key& key) override;
            Value* find(const Key& key) override;
            void update(const Key& key, const Value& value) override;
            std::pair<Key, Value> getFirst() const override;

            void moveToFirstLeaf(BPlusTreeNode<Key,Value>* root);
        private:
            BPlusTreeNode<Key,Value>* root;
            BPlusTreeNode<Key,Value>* current;
            size_t currentIndex;
    };
}

#endif