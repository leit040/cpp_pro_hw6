#include <iostream>
#include <thread>
#include "SafeVector.cpp"

void thread_push(SafeVector<int>& vec) {
    for (int i = 0; i < 1000; ++i) {
        vec.push_back(i);
    }
}

void thread_get(SafeVector<int>& vec) {
    for (int i = 0; i < 1000; ++i) {
        try {
            if (i < vec.size()) {
                std::cout << "Value: " << vec.get(i) << std::endl;
            }
        } catch (const std::out_of_range& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

int main() {
    SafeVector<int> intVector;
    std::thread writer1(thread_push, std::ref(intVector));
    std::thread writer2(thread_push, std::ref(intVector));
    std::thread reader1(thread_get, std::ref(intVector));
    std::thread reader2(thread_get, std::ref(intVector));

    writer1.join();
    writer2.join();
    reader1.join();
    reader2.join();

    std::cout << "Final size of intVector: " << intVector.size() << std::endl;

    return 0;
}