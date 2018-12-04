//
// Created by isysoi on 04.12.18.
//

#include "SafeQueue.h"

template<typename T>
bool SafeQueue<T>::empty() {
    std::lock_guard<std::mutex> lock_guard(mutex);
    return queue.empty();
}

template<typename T>
std::shared_ptr<T> SafeQueue<T>::wait_and_pop() {
    std::unique_lock<std::mutex> unique_lock(mutex);
    queue.wait(unique_lock, !queue.empty());
    std::shared_ptr<T> result(std::make_shared<T>(move(queue.front())));
    queue.pop();
    return result;
}

template<typename T>
std::shared_ptr<T> SafeQueue<T>::try_pop() {
    std::lock_guard<std::mutex> lock_guard(mutex);
    if (queue.empty())
        return std::shared_ptr<T>();
    std::shared_ptr<T> result(std::make_shared<T>(move(queue.front())));
    queue.pop();
    return result;
}

template<typename T>
SafeQueue<T>::SafeQueue() {

}

template<typename T>
void SafeQueue<T>::push(T element) {
    std::lock_guard<std::mutex> lock_guard(mutex);
    queue.push(element);
    condition.notify_one();
}


