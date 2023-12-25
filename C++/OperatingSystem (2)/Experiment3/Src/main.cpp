#include <iostream>
#include "../Include/PageControl.hpp"

// 主函数
int main()
{
    int numPages = 50;          // 实存中的页数
    int numInstructions = 1000; // 指令流长度
    int numTotalPages = 100;    // 总页数

    // 生成指令流
    srand(static_cast<unsigned int>(time(nullptr)));
    std::vector<int> instructionStream = generateInstructionStream(numInstructions, numTotalPages);

    // 初始化算法
    LRU lru(numPages);
    FIFO fifo(numPages);
    OPT opt(numPages, instructionStream);

    // 初始化命中次数
    int lruHits = 0, fifoHits = 0, optHits = 0;

    // 初始化日志表格
    std::vector<std::string> lruLog, fifoLog, optLog;

    // 对每个页面应用三种算法
    for (int i = 0; i < instructionStream.size(); ++i)
    {
        int pageId = instructionStream[i];

        // LRU 算法
        bool lruHit = lru.isPageInMemory(pageId);
        lru.accessPage(pageId);
        lruLog.push_back("页面 " + std::to_string(pageId) + (lruHit ? " 命中" : " 缺页"));
        if (lruHit)
            lruHits++;

        // FIFO 算法
        bool fifoHit = fifo.isPageInMemory(pageId);
        fifo.accessPage(pageId);
        fifoLog.push_back("页面 " + std::to_string(pageId) + (fifoHit ? " 命中" : " 缺页"));
        if (fifoHit)
            fifoHits++;

        // OPT 算法
        bool optHit = opt.isPageInMemory(pageId);
        opt.accessPage(pageId, i);
        optLog.push_back("页面 " + std::to_string(pageId) + (optHit ? " 命中" : " 缺页"));
        if (optHit)
            optHits++;
    }

    // 输出日志表格
    std::cout << std::left << std::setw(20) << "LRU" << std::setw(20) << "FIFO" << std::setw(20) << "OPT" << std::endl;
    for (int i = 0; i < instructionStream.size(); ++i)
    {
        std::cout << std::left << std::setw(20) << lruLog[i] << std::setw(20) << fifoLog[i] << std::setw(20) << optLog[i] << std::endl;
    }

    // 输出命中率
    std::cout << "\nLRU 命中率: " << static_cast<double>(lruHits) / numInstructions << std::endl;
    std::cout << "FIFO 命中率: " << static_cast<double>(fifoHits) / numInstructions << std::endl;
    std::cout << "OPT 命中率: " << static_cast<double>(optHits) / numInstructions << std::endl;

    return 0;
}