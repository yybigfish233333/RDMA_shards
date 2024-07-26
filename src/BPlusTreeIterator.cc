#include "BPlusTreeIterator.hh"
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>

namespace HtableRDMA
{

    log4cplus::Logger logger = log4cplus::Logger::getRoot();

    template <typename Key, typename Value>
    BPlusTreeIterator<Key, Value>::BPlusTreeIterator(BPlusTreeNode<Key, Value> *root) : currentIndex(0)
    {
        log4cplus::BasicConfigurator::configure();
        logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("BPlusTreeIterator"));
        moveToFirstLeaf(root);
        LOG4CPLUS_INFO(logger, "BPlusTreeIterator initialized and moved to first leaf.");
    }

    template <typename Key, typename Value>
    BPlusTreeIterator<Key, Value>::~BPlusTreeIterator()
    {
        LOG4CPLUS_INFO(logger, "BPlusTreeIterator destroyed");
    }

    template <typename Key, typename Value>
    bool BPlusTreeIterator<Key, Value>::hasNext() const
    {
        // 1.到树的末尾，或者树本身为空 2.当前索引是否在当前叶子节点的有效范围内
        bool hasNext = currentLeaf != nullptr && currentIndex < currentLeaf->values.size();
        LOG4CPLUS_DEBUG(logger, "hasNext called:" << (hasNext ? "true" : "false"));
        return hasNext;
    }

    template <typename Key, typename Value>
    std::pair<Key, Value> BPlusTreeIterator<Key, Value>::next()
    {
        if (!hasNext())
        {
            LOG4CPLUS_ERROR(logger, "No more elements to iterate");
            throw std::out_of_range("No more elements");
        }

        auto result = std::make_pair(currentLeaf->keys[currentIndex], currentLeaf->values[currentIndex]);
        LOG4CPLUS_DEBUG(logger, "Next element :Key=" << result.first << ",Value=" << result.second);

        currentIndex++;
        if (currentIndex >= currentLeaf->keys.size() && currentLeaf->nextLeaf != nullptr)
        {
            currentLeaf = currentLeaf->nextLeaf;
            currentIndex = 0;
            LOG4CPLUS_INFO(logger, "Moved to next leaf");
        }
        return result;
    }

    template <typename Key, typename Value>
    void BPlusTreeIterator<Key, Value>::insert(const Key &key, const Value &value)
    {
        LOG4CPLUS_INFO(logger, "insert called:key=" << key << ",value=" << value);
    }

    template <typename Key, typename Value>
    void BPlusTreeIterator<Key, Value>::remove(const Key &key)
    {
        // 这里可以添加删除逻辑
        LOG4CPLUS_INFO(logger, "Remove called: Key = " << key);
    }

    template <typename Key, typename Value>
    Value *BPlusTreeIterator<Key, Value>::find(const Key &key)
    {
        // 这里可以添加查找逻辑
        LOG4CPLUS_INFO(logger, "Find called: Key = " << key);
        return nullptr;
    }

    template <typename Key, typename Value>
    void BPlusTreeIterator<Key, Value>::update(const Key &key, const Value &value)
    {
        // 这里可以添加更新逻辑
        LOG4CPLUS_INFO(logger, "Update called: Key = " << key << ", Value = " << value);
    }

    template <typename Key, typename Value>
    std::pair<Key, Value> BPlusTreeIterator<Key, Value>::getFirst() const
    {
        if (currentLeaf != nullptr && !currentLeaf->values.empty())
        {
            auto first = std::make_pair(currentLeaf->keys[0], currentLeaf->values[0]);
            LOG4CPLUS_DEBUG(logger, "First element: Key = " << first.first << ", Value = " << first.second);
            return first;
        }
        LOG4CPLUS_ERROR(logger, "No elements in the tree.");
        throw std::out_of_range("No elements in the tree");
    }

    template <typename Key, typename Value>
    void BPlusTreeIterator<Key, Value>::moveToFirstLeaf(BPlusTreeNode<Key, Value> *root)
    {
        BPlusTreeNode<Key, Value> *node = root;
        while (node != nullptr && !node->isLeaf)
        {
            node = node->children.front();
        }
        currentLeaf = node;
        LOG4CPLUS_INFO(logger, "Moved to first leaf.");
    }

}