#include <rebel/engine/platform/entry_point.hpp>
#include <rebel/engine/platform/engine.hpp>
#include <utility>

class RebelGame : public rebel::Engine
{
public:
    explicit RebelGame(std::string title) : Engine(std::move(title))
    {
        std::cout << "RebelGame constructor" << std::endl;
    }

protected:
    void Update(float deltaTime) override
    {
        //std::cout << "RebelGame Update" << std::endl;
    }
};

// Runtime
rebel::Engine* rebel::Init()
{
    return new RebelGame("Rebel Game");
}

