#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "engine.hpp"

int main(int argc, char** argv)
{

    // Create the application
    auto* game = rebel::Init();

    // Run the application
    game->Run();

    // Destroy the application
    delete game;
}
