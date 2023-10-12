#include <iostream>
#include <vector>
#include <thread>
#include <semaphore.h>
#include <mutex>
#include <chrono>

using namespace std;

// 循环队列的定义
template <typename T>
class CircularQueue
{
private:
    int _capacity; // 队列容量
    int _front;    // 队首索引
    int _rear;     // 队尾索引
    T *elements;   // 存储元素的数组

public:
    CircularQueue(int capacity)
    {
        this->_capacity = capacity;
        elements = new T[capacity];
        _front = _rear = -1;
    }

    ~CircularQueue()
    {
        delete[] elements;
    }

    bool isEmpty()
    {
        return _front == -1;
    }

    bool isFull()
    {
        return (_front == 0 && _rear == _capacity - 1) || (_rear == (_front - 1) % (_capacity - 1));
    }

    int size()
    {
        if (isEmpty())
            return 0;
        if (isFull())
            return _capacity;
        if (_front <= _rear)
            return _rear - _front + 1;
        return _capacity - _front + _rear + 1;
    }

    void push(T item)
    {
        if (isFull())
        {
            cout << "队列已满，无法添加元素" << endl;
            return;
        }

        if (isEmpty())
            _front = _rear = 0;
        else if (_rear == _capacity - 1)
            _rear = 0;
        else
            _rear++;

        elements[_rear] = item;
    }

    void pop()
    {
        if (isEmpty())
        {
            cout << "队列为空，无法出队" << endl;
            return;
        }

        if (_front == _rear)
            _front = _rear = -1;
        else if (_front == _capacity - 1)
            _front = 0;
        else
            _front++;
    }

    T front()
    {
        if (isEmpty())
        {
            cout << "队列为空，无法获取队首元素" << endl;
            throw "队列为空";
        }
        return elements[_front];
    }
};

const int bufferSize = 5; // 缓冲区大小
CircularQueue<int> buffer(bufferSize);
sem_t emptySlots, filledSlots; // 信号量用于表示空槽位和已填槽位
std::mutex mtx;                // 互斥锁用于控制输出顺序

const int numProducers = 2;
const int numConsumers = 2;

void producer(int id)
{
    for (int i = 1; i <= 10; ++i)
    {
        sem_wait(&emptySlots);

        // 生产一个项目并将其放入缓冲区
        buffer.push(i);

        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "生产者 " << id << " 生产: " << i << ", 当前缓冲容量: " << buffer.size() << std::endl;
        }

        sem_post(&filledSlots);

        // 引入延时，模拟生产过程
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer(int id)
{
    for (int i = 1; i <= 10; ++i)
    {
        sem_wait(&filledSlots);

        // 从缓冲区中取出一个项目并消费
        int item = buffer.front();
        buffer.pop();

        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "消费者 " << id << " 消费: " << item << ", 当前缓冲容量: " << buffer.size() << std::endl;
        }

        sem_post(&emptySlots);

        // 引入延时，模拟消费过程
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main()
{
    sem_init(&emptySlots, 0, bufferSize); // 初始化信号量
    sem_init(&filledSlots, 0, 0);

    std::vector<std::thread> producerThreads;
    std::vector<std::thread> consumerThreads;

    for (int i = 0; i < numProducers; ++i)
    {
        producerThreads.emplace_back(producer, i);
    }

    for (int i = 0; i < numConsumers; ++i)
    {
        consumerThreads.emplace_back(consumer, i);
    }

    for (auto &thread : producerThreads)
    {
        thread.join();
    }

    for (auto &thread : consumerThreads)
    {
        thread.join();
    }

    sem_destroy(&emptySlots);
    sem_destroy(&filledSlots);

    return 0;
}
