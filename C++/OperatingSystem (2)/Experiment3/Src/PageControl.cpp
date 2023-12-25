#include <vector>
#include <list>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <ctime>
#include <iomanip> // 用于格式化输出
#include "../Include/PageControl.hpp"

// 生成模拟的指令地址流
std::vector<int> generateInstructionStream(int numInstructions, int numPages)
{
    std::vector<int> stream;
    int halfNumPages = numPages / 2;

    // 50% 顺序执行
    for (int i = 0; i < numInstructions / 2; ++i)
    {
        stream.push_back(i % numPages);
    }

    // 25% 均匀分布在前半部分
    for (int i = 0; i < numInstructions / 4; ++i)
    {
        stream.push_back(rand() % halfNumPages);
    }

    // 25% 均匀分布在后半部分
    for (int i = 0; i < numInstructions / 4; ++i)
    {
        stream.push_back(rand() % halfNumPages + halfNumPages);
    }

    return stream;
}

// LRU
void LRU::accessPage(int pageId)
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

bool LRU::isPageInMemory(int pageId) const
{
    return pageMap.find(pageId) != pageMap.end();
}

// FIFO
void FIFO::accessPage(int pageId)
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

bool FIFO::isPageInMemory(int pageId) const
{
    return pageSet.find(pageId) != pageSet.end();
}

// OPT
void OPT::accessPage(int pageId, int currentIndex)
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

void OPT::replacePage(int currentIndex)
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

int OPT::findNextIndex(int page, int currentIndex)
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

bool OPT::isPageInMemory(int pageId) const
{
    return pages.find(pageId) != pages.end();
}