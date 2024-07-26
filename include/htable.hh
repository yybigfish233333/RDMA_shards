#ifndef HTABLE_HH
#define HTABLE_HH

#include <iostream>
#include <mutex>
#include <atomic>
#include <vector>
#include <unordered_map>
#include <shared_mutex>

namespace HtableRDMA
{
    template <typename Key, typename Value>
    // 提供对索引哈希的表，全局只有一个，用单例模式
    class Htable
    {
    private:
        std::vector<std::mutex> locks;
        static const int num_shards = 3; // 分片的数量，暂时定为3
        std::vector<std::unordered_map<Key, Value>> shards;

    public:
        // Htable() = default; // Add default constructor
        Htable(const Htable &) = delete;
        Htable &operator=(const Htable &) = delete;

        // 这里获得全局访问点
        static Htable &getInstance()
        {
            // static std::mutex mtx;
            // std::lock_guard<std::mutex> lck(mtx);
            static Htable instance;
            return instance;
        }

        void insert(const Key &key, const Value &value)
        {
            auto shard_index = hash_key(key) % num_shards;
            std::lock_guard<std::mutex> lock(locks[shard_index]);
            shards[shard_index][key]=value;
        }

        typename std::ordered_map<Key,Value>::iterator getIterator(size_t shard_index){
            
        }

        bool find(const Key &key, Value &value)
        {
            auto shard_index = hash_key(key) % num_shards;
            std::lock_guard<std::mutex> lock(locks[shard_index]);
            auto &shard=shards[shard_index];
            auto it=shard.find(key);
            if(it!=shard.end()){
                value=it->second;
                return true;
            }
            return false;
        }

        void erase(const Key &key){
            auto shard_index=hash_key(key)%num_shards;
            std::lock_guard<std::mutex> lock(locks[shard_index]);
            shards[shard_index].erase(key);
        }


        void showTable()
        {
            std::cout << "showTable" << std::endl;
        }

    private:
        Htable()
        {
            std::cout << "Htable created!" << std::endl;
        }
        ~Htable()
        {
            std::cout << "Htable destroyed!" << std::endl;
        }

        size_t hash_key(const Key &key) const
        {
            return std::hash<Key>{}(key);
        }
    };

} // namespace HtableRDMA

#endif