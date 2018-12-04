//
// Created by isysoi on 04.12.18.
//

#pragma once

#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <iostream>

template<typename T>
class SafeQueue {
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable condition;
public:

    SafeQueue();
    void push(T);
    bool empty();
    std::shared_ptr<T> wait_and_pop();
    std::shared_ptr<T> try_pop();

};

