#include "Game/Game.h"

int main(int argc, char* argv[])
{
    CGame game;
    if(game.Initialize())
    {
        game.Run();
    }
    game.Shutdown();

    return 0;
}
