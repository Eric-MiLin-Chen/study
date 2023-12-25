#ifndef __PROCESS_CONTROL_BLOCK_H
#define __PROCESS_CONTROL_BLOCK_H

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <ctime>
#include <iomanip> // 用于格式化输出

// 生成模拟的指令地址流
std::vector<int> generateInstructionStream(int numInstructions, int numPages);

// LRU 页面淘汰算法
class LRU
{
private:
    std::list<int> pages;                                      // 存储页面的列表
    std::unordered_map<int, std::list<int>::iterator> pageMap; // 映射页面和其在列表中的位置
    int capacity;                                              // 内存中可以存储的页数

public:
    LRU(int capacity) : capacity(capacity) {}
    void accessPage(int pageId);
    bool isPageInMemory(int pageId) const;
};

// FIFO 页面淘汰算法
class FIFO
{
private:
    std::queue<int> pageQueue;
    std::unordered_set<int> pageSet;
    int capacity;

public:
    FIFO(int capacity) : capacity(capacity) {}
    void accessPage(int pageId);
    bool isPageInMemory(int pageId) const;
};

// OPT 页面淘汰算法
class OPT
{
private:
    std::unordered_set<int> pages;
    std::vector<int> instructionStream;
    int capacity;

public:
    OPT(int capacity, const std::vector<int> &stream) : capacity(capacity), instructionStream(stream) {}
    void accessPage(int pageId, int currentIndex);
    void replacePage(int currentIndex);
    int findNextIndex(int page, int currentIndex);
    bool isPageInMemory(int pageId) const;
};

#endif