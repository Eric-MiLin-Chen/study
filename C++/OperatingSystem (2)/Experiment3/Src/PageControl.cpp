#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>

// 生成模拟的指令地址流
std::vector<int> generateInstructionStream(int numInstructions, int numPages)
{
    std::vector<int> stream;
    for (int i = 0; i < numInstructions; ++i)
    {
        stream.push_back(rand() % numPages);
    }
    return stream;
}

// LRU 页面淘汰算法
class LRU
{
private:
    std::list<int> pages;                                      // 存储页面的列表
    std::unordered_map<int, std::list<int>::iterator> pageMap; // 映射页面和其在列表中的位置
    int capacity;                                              // 内存中可以存储的页数

public:
    LRU(int capacity) : capacity(capacity) {}

    void accessPage(int pageId)
    {
        if (pageMap.find(pageId) == pageMap.end())
        {
            if (pages.size() == capacity)
            {
                // 移除最久未访问的页面
                pageMap.erase(pages.back());
                pages.pop_back();
            }
        }
        else
        {
            // 移除已存在的页面
            pages.erase(pageMap[pageId]);
        }
        // 将访问的页面放到前面
        pages.push_front(pageId);
        pageMap[pageId] = pages.begin();
    }

    bool isPageInMemory(int pageId) const
    {
        return pageMap.find(pageId) != pageMap.end();
    }
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

    void accessPage(int pageId)
    {
        if (pageSet.find(pageId) == pageSet.end())
        {
            if (pageQueue.size() == capacity)
            {
                int oldestPage = pageQueue.front();
                pageQueue.pop();
                pageSet.erase(oldestPage);
            }
            pageQueue.push(pageId);
            pageSet.insert(pageId);
        }
    }

    bool isPageInMemory(int pageId) const
    {
        return pageSet.find(pageId) != pageSet.end();
    }
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

    void accessPage(int pageId, int currentIndex)
    {
        if (pages.find(pageId) == pages.end())
        {
            if (pages.size() == capacity)
            {
                replacePage(currentIndex);
            }
            pages.insert(pageId);
        }
    }

    void replacePage(int currentIndex)
    {
        // 寻找最晚被访问的页面
        int farthest = currentIndex;
        int pageToReplace = -1;

        for (int page : pages)
        {
            int nextIndex = findNextIndex(page, currentIndex);
            if (nextIndex > farthest)
            {
                farthest = nextIndex;
                pageToReplace = page;
            }
        }

        if (pageToReplace != -1)
        {
            pages.erase(pageToReplace);
        }
    }

    int findNextIndex(int page, int currentIndex)
    {
        for (int i = currentIndex + 1; i < instructionStream.size(); ++i)
        {
            if (instructionStream[i] == page)
            {
                return i;
            }
        }
        return instructionStream.size(); // 返回一个大于当前流长度的值
    }

    bool isPageInMemory(int pageId) const
    {
        return pages.find(pageId) != pages.end();
    }
};

// 主函数
int main()
{
    int numPages = 4;          // 实存中的页数
    int numInstructions = 100; // 指令流长度
    int numTotalPages = 10;    // 总页数

    std::vector<int> instructionStream = generateInstructionStream(numInstructions, numTotalPages);

    LRU lru(numPages);
    FIFO fifo(numPages);
    OPT opt(numPages, instructionStream);

    int lruHits = 0;
    int fifoHits = 0;
    int optHits = 0;

    for (int i = 0; i < instructionStream.size(); ++i)
    {
        int pageId = instructionStream[i];
        // 对于LRU
        if (lru.isPageInMemory(pageId))
        {
            lruHits++;
        }
        lru.accessPage(pageId);

        // 对于FIFO
        if (fifo.isPageInMemory(pageId))
        {
            fifoHits++;
        }
        fifo.accessPage(pageId);

        // 对于OPT
        if (opt.isPageInMemory(pageId))
        {
            optHits++;
        }
        opt.accessPage(pageId, i);
    }

    std::cout << "LRU 命中率: " << static_cast<double>(lruHits) / numInstructions << std::endl;
    std::cout << "FIFO 命中率: " << static_cast<double>(fifoHits) / numInstructions << std::endl;
    std::cout << "OPT 命中率: " << static_cast<double>(optHits) / numInstructions << std::endl;

    return 0;
}
