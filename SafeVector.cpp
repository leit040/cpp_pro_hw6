#include <stdexcept>
#include <vector>
#include <mutex>

template<typename T>
class SafeVector {
private:
    std::vector<T> vector;
    mutable std::mutex mutex;

public:
    void push_back(const T &value) {
        std::unique_lock<std::mutex> lock(mutex);
        vector.push_back(value);
    }
    T& get(size_t index) {
        std::unique_lock<std::mutex> lock(mutex);
        if (index < vector.size()) {
            return vector[index];
        }
        throw std::out_of_range("Index out of range");
    }

    T& get(size_t index) const{
        std::unique_lock<std::mutex> lock(mutex);
        if (index < vector.size()) {
            return static_cast<int &>(vector[index]);
        }
        throw std::out_of_range("Index out of range");
    }

    size_t size() {
        std::unique_lock<std::mutex> lock(mutex);
        return vector.size();
    }

    void erase(size_t index) {
        std::unique_lock<std::mutex> lock(mutex);
        if (index < vector.size()) {
            vector.erase(vector.begin() + index);
        } else {
            throw std::out_of_range("Index out of range");
        }
    }
};