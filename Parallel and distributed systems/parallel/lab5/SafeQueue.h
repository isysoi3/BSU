//
// Created by isysoi on 04.12.18.
//

#ifndef LAB5_SAFE_QUEUE_H
#define LAB5_SAFE_QUEUE_H

#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>

template<typename T>
class SafeQueue {
private:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable condition;
public:

    SafeQueue();
    void push(T element);
    bool empty();
    std::shared_ptr<T> wait_and_pop();
    std::shared_ptr<T> try_pop();
};

#endif //LAB5_SAFE_QUEUE_H
