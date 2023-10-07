#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;

const int BUFFER_SIZE = 5;  // 缓冲区大小
const int NUM_PRODUCE = 10; // 生产者生成的数据项数量

queue<int> buffer;                            // 缓冲区
mutex mtx;                                    // 互斥锁
condition_variable buffer_empty, buffer_full; // 信号量

// 生产者函数
void producer(int id)
{
    for (int i = 0; i < NUM_PRODUCE; ++i)
    {
        // 生产数据项
        int item = i + 1;

        unique_lock<mutex> lock(mtx);

        // 如果缓冲区已满，等待
        while (buffer.size() >= BUFFER_SIZE)
        {
            cout << "Producer " << id << " is waiting. Buffer full." << endl;
            buffer_full.wait(lock);
        }

        // 将数据项放入缓冲区
        buffer.push(item);
        cout << "Producer " << id << " produced item " << item << ". Buffer size: " << buffer.size() << endl;

        // 通知消费者可以取数据
        buffer_empty.notify_all();

        lock.unlock();

        // 模拟生产耗时
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

// 消费者函数
void consumer(int id)
{
    for (int i = 0; i < NUM_PRODUCE; ++i)
    {
        unique_lock<mutex> lock(mtx);

        // 如果缓冲区为空，等待
        while (buffer.empty())
        {
            cout << "Consumer " << id << " is waiting. Buffer empty." << endl;
            buffer_empty.wait(lock);
        }

        // 从缓冲区取出数据
        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed item " << item << ". Buffer size: " << buffer.size() << endl;

        // 通知生产者可以放数据
        buffer_full.notify_all();

        lock.unlock();

        // 模拟消费耗时
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

int main()
{
    vector<thread> producers, consumers;

    // 创建生产者线程
    for (int i = 1; i <= 2; ++i)
    {
        producers.emplace_back(producer, i);
    }

    // 创建消费者线程
    for (int i = 1; i <= 3; ++i)
    {
        consumers.emplace_back(consumer, i);
    }

    // 等待线程结束
    for (auto &producer_thread : producers)
    {
        producer_thread.join();
    }
    for (auto &consumer_thread : consumers)
    {
        consumer_thread.join();
    }

    return 0;
}
