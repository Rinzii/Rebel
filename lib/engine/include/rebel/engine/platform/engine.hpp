#pragma once
#include <string>

namespace rebel
{
    class Engine
    {
    public:
	  Engine();
        explicit Engine(std::string windowTitle);
        ~Engine();

        // Run the main game
        void Run();

    private:
        void InitializeServices();
        static void DestroyServices();

    protected:
        virtual void PhysUpdate(float deltaTime) {};
        virtual void Update(float deltaTime) {};

    public:



    private:
        std::string m_windowTitle;
        bool m_isRunning;
    };

    extern Engine* Init();
}



