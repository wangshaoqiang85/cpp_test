#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    int capacity_ = 0;
    list<pair<int, int>> order_;
    unordered_map<int, list<pair<int, int>>::iterator> cache_;
public:
    explicit LRUCache(int capacity): capacity_(capacity) {}

    int get(int key) {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            order_.splice(order_.begin(), order_, it->second);
            cache_[key] = order_.begin();
            return it->second->second;
        }
        return -1;
    }

    void put(int key, int value) {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            // 已经访问，更新value
            it->second->second = value;
            order_.splice(order_.begin(), order_, it->second);
            cache_[key] = order_.begin();
            return;
        }
        // 没有访问过
        if (order_.size() >= capacity_) {
            auto lastKey = order_.back().first;
            order_.pop_back();
            cache_.erase(lastKey);
        }
        order_.emplace_front(key, value);
        cache_[key] = order_.begin();
    }
};





class LRUCacheDemo {
public:
    explicit LRUCacheDemo(int capacity) : capacity_(capacity) {}

    int get(int key) {
        auto it = cache_.find(key);
        if (it == cache_.end()) {
            return -1;
        }
        order_.splice(order_.begin(), order_, it->second);
        cache_[key] = order_.begin();
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            it->second->second = value;
            order_.splice(order_.begin(), order_, it->second);
            cache_[key] = order_.begin();
            return;
        }
        if (static_cast<int>(cache_.size()) >= capacity_) {
            int lruKey = order_.back().first;
            order_.pop_back();
            cache_.erase(lruKey);
        }
        order_.emplace_front(key, value);
        cache_[key] = order_.begin();
    }

private:
    int capacity_;
    list<pair<int, int>> order_;
    unordered_map<int, list<pair<int, int>>::iterator> cache_;
};
