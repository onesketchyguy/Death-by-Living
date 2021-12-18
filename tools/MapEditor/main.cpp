#define OLC_PGE_APPLICATION
#include "../../DeathByLiving/lib/olcPixelGameEngine15.h"

#include "var.h"
#include "map.h"
#include "project.h"

int main()
{
	Game game;
	if (game.Construct(var::width, var::height, var::pixel_size, var::pixel_size))
		game.Start();

	return 0;
}
