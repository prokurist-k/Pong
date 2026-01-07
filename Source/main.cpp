#include "Game/Game.h"

int main(int argc, char* argv[])
{
    const int window_width = 800;
    const int window_height = 600;

    CGame game;
    if(game.Initialize(window_width, window_height))
    {
        game.Run();
    }
    game.Shutdown();

    return 0;
}
