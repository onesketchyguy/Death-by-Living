#include "world.h"
#include "map.h"

class LevelManager
{

public:

    float tile = 16.0;
    int room_x = 8, room_y = 8;

    World world = World(16, 16);
    Map map = Map(21, 15, 4);
    olc::Renderable* tileset = nullptr;

    LevelManager() { GenerateLevel(); }
    ~LevelManager() { std::cout << "Goodbye, cruel LevelManager." << std::endl; }

    void GenerateLevel()
    {
        world.GenerateMatrix();
        for (int i = 0; i < world.matrix.size(); i++)
        {
            std::string room = world.matrix[i];
            if (room != "0000") { world.matrix[i]+=std::to_string(rand()%map.room_tally[room]); }
        }
        LoadMap();
    }
    void LoadMap() { std::string _dir = world.matrix[room_y*world.width+room_x]+".map"; map.LoadData(_dir); }
    
    void DrawRoom(olc::PixelGameEngine* pge, olc::Renderable* sheet)
    {
        for (int l = 0; l < map.layers; l++)
        {
            for (int y = 0; y < map.height; y++)
            {
                for (int x = 0; x < map.width; x++)
                {
                    char _t=map.matrix[l][y*map.width+x];
                    float t=float(tile), X=x*t, Y=y*t;
                    float tx=map.Neighbors(x, y, l, _t)*tile, ty=map.keys[_t]*tile;
                    pge->DrawPartialDecal({ X,Y }, { t,t }, sheet->Decal(), { tx,ty }, { t, t });
                }
            }
        }
    }

};
