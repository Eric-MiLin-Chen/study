#include <SDL.h>
#include <iostream>
#include <random>

const int screen_width = 800;
const int screen_height = 600;
const int particle_count = 10000;
const float particle_radius = 2; // 修改粒子的半径
const float collision_losses = 0.1;

// 创建一个随机数生成器引擎
std::random_device rd;
std::mt19937 mt(rd()); // 使用 Mersenne Twister 生成器引擎

// 创建一个分布（这里是整数分布）
std::uniform_int_distribution<int> dist(-10000, 10000); // 生成1到100之间的随机整数

struct Particle
{
    float x, y;
    float speedX, speedY;
};

Particle particles[particle_count];

void initParticles()
{
    for (int i = 0; i < particle_count; i++)
    {
        particles[i].x = 0;
        particles[i].y = 0;
        particles[i].speedX = dist(mt) / 200.0f;
        particles[i].speedY = dist(mt) / 200.0f;
    }
}

void MoveParticles(int i)
{
    particles[i].speedY += SDL_STANDARD_GRAVITY / 100.0f;
    particles[i].x += particles[i].speedX;
    particles[i].y += particles[i].speedY;
}

void EdgeCollisionParticles(int i)
{
    if (particles[i].x < 0)
    {
        particles[i].x = 0;
        particles[i].speedX = -particles[i].speedX * collision_losses;
    }
    else if (particles[i].x > screen_width)
    {
        particles[i].x = screen_width;
        particles[i].speedX = -particles[i].speedX * collision_losses;
    }
    if (particles[i].y < 0)
    {
        particles[i].y = 0;
        particles[i].speedY = -particles[i].speedY * collision_losses;
    }
    else if (particles[i].y > screen_height)
    {
        particles[i].y = screen_height;
        particles[i].speedY = -particles[i].speedY * collision_losses;
    }
}

void PeersCollisionParticles(int i)
{
    for (int j = i + 1; j < particle_count; j++)
    {
        float dx = particles[i].x - particles[j].x;
        float dy = particles[i].y - particles[j].y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < 2 * particle_radius)
        {
            // 如果粒子之间距离小于2倍的粒子半径，表示碰撞
            // 修正粒子的位置
            float overlap = 2 * particle_radius - distance;
            float moveX = (dx / distance) * (overlap / 2);
            float moveY = (dy / distance) * (overlap / 2);

            particles[i].x += moveX;
            particles[i].y += moveY;
            particles[j].x -= moveX;
            particles[j].y -= moveY;

            // 修改粒子的速度（可根据需要进一步调整）
            // float tempSpeedX = particles[i].speedX * collision_losses;
            // float tempSpeedY = particles[i].speedY * collision_losses;
            // particles[i].speedX = particles[j].speedX * collision_losses;
            // particles[i].speedY = particles[j].speedY * collision_losses;
            // particles[j].speedX = tempSpeedX;
            // particles[j].speedY = tempSpeedY;
        }
    }
}

void updateParticles()
{
    for (int i = 0; i < particle_count; i++)
    {
        // 重置粒子位置
        MoveParticles(i);

        // 边界碰撞检测
        EdgeCollisionParticles(i);

        // 粒子碰撞检测
        PeersCollisionParticles(i);
    }
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL初始化失败: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("粒子仿真", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    initParticles();

    int frameCount = 0;
    Uint32 startTime = SDL_GetTicks();

    bool quit = false;
    while (!quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
                quit = true;

        // 更新粒子位置
        updateParticles();

        // 清空屏幕
        SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
        SDL_RenderClear(renderer);

        // 渲染粒子
        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // for (int i = 0; i < particle_count; i++)
        // {
        //     SDL_RenderDrawPoint(renderer, static_cast<int>(particles[i].x), static_cast<int>(particles[i].y));
        // }

        // 渲染粒子（绘制圆圈）
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < particle_count; i++)
        {
            int centerX = static_cast<int>(particles[i].x);
            int centerY = static_cast<int>(particles[i].y);

            for (int dx = -particle_radius; dx <= particle_radius; dx++)
            {
                for (int dy = -particle_radius; dy <= particle_radius; dy++)
                {
                    // 检查点是否在圆内
                    if (dx * dx + dy * dy <= particle_radius * particle_radius)
                    {
                        int x = centerX + dx;
                        int y = centerY + dy;
                        SDL_RenderDrawPoint(renderer, x, y);
                    }
                }
            }
        }

        // 更新窗口
        SDL_RenderPresent(renderer);

        // 计算帧率
        frameCount++;
        Uint32 endTime = SDL_GetTicks();
        Uint32 frameTime = endTime - startTime;

        if (frameTime >= 1000)
        {
            float fps = frameCount / (frameTime / 1000.0f);
            frameCount = 0;
            startTime = endTime;

            // 在窗口标题上输出帧率
            std::string fpsText = "帧率: " + std::to_string(static_cast<int>(fps));
            SDL_SetWindowTitle(window, fpsText.c_str());
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
