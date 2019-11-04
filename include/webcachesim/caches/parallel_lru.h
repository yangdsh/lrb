//
// Created by zhenyus on 11/2/19.
//

#ifndef WEBCACHESIM_PARALLEL_LRU_H
#define WEBCACHESIM_PARALLEL_LRU_H

#include "parallel_cache.h"
#include <list>
/*
    ParallelLRU: allowing get/put concurrently. Internally it is still sequential
*/
using namespace webcachesim;
using namespace std;


typedef std::list<uint64_t>::iterator ListIteratorType;
typedef std::unordered_map<uint64_t, ListIteratorType> lruCacheMapType;

class ParallelLRUCache : public ParallelCache {
private:
    // list for recency order
    list<uint64_t> cache_list;
    // map to find objects in list
    lruCacheMapType cache_map;

    ~ParallelLRUCache() override {
        keep_running.clear();
        lookup_get_thread.join();
    }

    void hit(lruCacheMapType::const_iterator it);

public:
    bool lookup(SimpleRequest &req) override;

    void admit(SimpleRequest &req) override;

    void async_lookup(const uint64_t &key) override;

    void async_admit(const uint64_t &key, const int64_t &size) override;

    void evict();
};

static Factory<ParallelLRUCache> factoryLRU("ParallelLRU");
#endif //WEBCACHESIM_PARALLEL_LRU_H
