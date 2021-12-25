#include "var.h"
#include "../../DeathByLiving/Scripts/button.h"
#include "../../DeathByLiving/Scripts/entry.h"
#include "../../DeathByLiving/Scripts/map.h"
#include "../../DeathByLiving/Scripts/world.h"

class Game : public olc::PixelGameEngine
{

public:
    Game()
    {
        sAppName = "Map Editor";
    }

public:

    bool tile_mode = true;
    
    int layer = 0;
    int room_x = 8;
    int room_y = 8;
    
    char selected = ' ';
    std::string _tile = "gravel";
    
    Entry map_dir = Entry(0, var::height-20, 1.0, "test.map", 42);

    Map map = Map(var::room_width, var::room_height, 3);
    World world = World(16, 16);
    
    olc::Renderable tileset;
    
    olc::Pixel color0 = olc::Pixel(128, 128, 128, 64);
    olc::Pixel color1 = olc::Pixel(  4,   4,   6);
    olc::Pixel color2 = olc::Pixel(  8,   8,  12);
    olc::Pixel color3 = olc::Pixel( 16,  16,  24);
    olc::Pixel color4 = olc::Pixel( 64,  64,  96);
    olc::Pixel color5 = olc::Pixel(128, 128, 160);
    olc::Pixel color6 = olc::Pixel(250, 250, 255);



    bool ShiftKey() { return GetKey(olc::Key::SHIFT).bHeld; }

    std::string GetCharacter()
    {
        std::string c = "null";
        if (!ShiftKey())
        {
            if (GetKey(olc::Key::A).bPressed) { c = "a"; }
            else if (GetKey(olc::Key::B).bPressed) { c = "b"; }
            else if (GetKey(olc::Key::C).bPressed) { c = "c"; }
            else if (GetKey(olc::Key::D).bPressed) { c = "d"; }
            else if (GetKey(olc::Key::E).bPressed) { c = "e"; }
            else if (GetKey(olc::Key::F).bPressed) { c = "f"; }
            else if (GetKey(olc::Key::G).bPressed) { c = "g"; }
            else if (GetKey(olc::Key::H).bPressed) { c = "h"; }
            else if (GetKey(olc::Key::I).bPressed) { c = "i"; }
            else if (GetKey(olc::Key::J).bPressed) { c = "j"; }
            else if (GetKey(olc::Key::K).bPressed) { c = "k"; }
            else if (GetKey(olc::Key::L).bPressed) { c = "l"; }
            else if (GetKey(olc::Key::M).bPressed) { c = "m"; }
            else if (GetKey(olc::Key::N).bPressed) { c = "n"; }
            else if (GetKey(olc::Key::O).bPressed) { c = "o"; }
            else if (GetKey(olc::Key::P).bPressed) { c = "p"; }
            else if (GetKey(olc::Key::Q).bPressed) { c = "q"; }
            else if (GetKey(olc::Key::R).bPressed) { c = "r"; }
            else if (GetKey(olc::Key::S).bPressed) { c = "s"; }
            else if (GetKey(olc::Key::T).bPressed) { c = "t"; }
            else if (GetKey(olc::Key::U).bPressed) { c = "u"; }
            else if (GetKey(olc::Key::V).bPressed) { c = "v"; }
            else if (GetKey(olc::Key::W).bPressed) { c = "w"; }
            else if (GetKey(olc::Key::X).bPressed) { c = "x"; }
            else if (GetKey(olc::Key::Y).bPressed) { c = "y"; }
            else if (GetKey(olc::Key::Z).bPressed) { c = "z"; }
            else if (GetKey(olc::Key::K0).bPressed) { c = "0"; }
            else if (GetKey(olc::Key::K1).bPressed) { c = "1"; }
            else if (GetKey(olc::Key::K2).bPressed) { c = "2"; }
            else if (GetKey(olc::Key::K3).bPressed) { c = "3"; }
            else if (GetKey(olc::Key::K4).bPressed) { c = "4"; }
            else if (GetKey(olc::Key::K5).bPressed) { c = "5"; }
            else if (GetKey(olc::Key::K6).bPressed) { c = "6"; }
            else if (GetKey(olc::Key::K7).bPressed) { c = "7"; }
            else if (GetKey(olc::Key::K8).bPressed) { c = "8"; }
            else if (GetKey(olc::Key::K9).bPressed) { c = "9"; }
            else if (GetKey(olc::Key::EQUALS).bPressed) { c = "="; }
            else if (GetKey(olc::Key::COMMA).bPressed) { c = ","; }
            else if (GetKey(olc::Key::MINUS).bPressed) { c = "-"; }
            else if (GetKey(olc::Key::PERIOD).bPressed) { c = "."; }
            else if (GetKey(olc::Key::OEM_1).bPressed) { c = ";"; }
            else if (GetKey(olc::Key::OEM_2).bPressed) { c = "/"; }
            else if (GetKey(olc::Key::OEM_4).bPressed) { c = "["; }
            else if (GetKey(olc::Key::OEM_5).bPressed) { c = "\\"; }
            else if (GetKey(olc::Key::OEM_7).bPressed) { c = "\'"; }
            else if (GetKey(olc::Key::SPACE).bPressed) { c = " "; }
            else if (GetKey(olc::Key::BACK).bPressed) { c = "BACK"; }
            else if (GetKey(olc::Key::DEL).bPressed) { c = "DEL"; }
            else if (GetKey(olc::Key::LEFT).bPressed) { c = "LEFT"; }
            else if (GetKey(olc::Key::RIGHT).bPressed) { c = "RIGHT"; }

        }
        else if (ShiftKey())
        {
            if (GetKey(olc::Key::A).bPressed) { c = "A"; }
            else if (GetKey(olc::Key::B).bPressed) { c = "B"; }
            else if (GetKey(olc::Key::C).bPressed) { c = "C"; }
            else if (GetKey(olc::Key::D).bPressed) { c = "D"; }
            else if (GetKey(olc::Key::E).bPressed) { c = "E"; }
            else if (GetKey(olc::Key::F).bPressed) { c = "F"; }
            else if (GetKey(olc::Key::G).bPressed) { c = "G"; }
            else if (GetKey(olc::Key::H).bPressed) { c = "H"; }
            else if (GetKey(olc::Key::I).bPressed) { c = "I"; }
            else if (GetKey(olc::Key::J).bPressed) { c = "J"; }
            else if (GetKey(olc::Key::K).bPressed) { c = "K"; }
            else if (GetKey(olc::Key::L).bPressed) { c = "L"; }
            else if (GetKey(olc::Key::M).bPressed) { c = "M"; }
            else if (GetKey(olc::Key::N).bPressed) { c = "N"; }
            else if (GetKey(olc::Key::O).bPressed) { c = "O"; }
            else if (GetKey(olc::Key::P).bPressed) { c = "P"; }
            else if (GetKey(olc::Key::Q).bPressed) { c = "Q"; }
            else if (GetKey(olc::Key::R).bPressed) { c = "R"; }
            else if (GetKey(olc::Key::S).bPressed) { c = "S"; }
            else if (GetKey(olc::Key::T).bPressed) { c = "T"; }
            else if (GetKey(olc::Key::U).bPressed) { c = "U"; }
            else if (GetKey(olc::Key::V).bPressed) { c = "V"; }
            else if (GetKey(olc::Key::W).bPressed) { c = "W"; }
            else if (GetKey(olc::Key::X).bPressed) { c = "X"; }
            else if (GetKey(olc::Key::Y).bPressed) { c = "Y"; }
            else if (GetKey(olc::Key::Z).bPressed) { c = "Z"; }
            else if (GetKey(olc::Key::K0).bPressed) { c = ")"; }
            else if (GetKey(olc::Key::K1).bPressed) { c = "!"; }
            else if (GetKey(olc::Key::K2).bPressed) { c = "@"; }
            else if (GetKey(olc::Key::K3).bPressed) { c = "#"; }
            else if (GetKey(olc::Key::K4).bPressed) { c = "$"; }
            else if (GetKey(olc::Key::K5).bPressed) { c = "%"; }
            else if (GetKey(olc::Key::K6).bPressed) { c = "^"; }
            else if (GetKey(olc::Key::K7).bPressed) { c = "&"; }
            else if (GetKey(olc::Key::K8).bPressed) { c = "*"; }
            else if (GetKey(olc::Key::K9).bPressed) { c = "("; }
            else if (GetKey(olc::Key::OEM_1).bPressed) { c = ":"; }
            else if (GetKey(olc::Key::OEM_2).bPressed) { c = "?"; }
            else if (GetKey(olc::Key::OEM_4).bPressed) { c = "{"; }
            else if (GetKey(olc::Key::OEM_5).bPressed) { c = "|"; }
            else if (GetKey(olc::Key::OEM_7).bPressed) { c = "\""; }
            else if (GetKey(olc::Key::EQUALS).bPressed) { c = "+"; }
            else if (GetKey(olc::Key::COMMA).bPressed) { c = "<"; }
            else if (GetKey(olc::Key::MINUS).bPressed) { c = "_"; }
            else if (GetKey(olc::Key::PERIOD).bPressed) { c = ">"; }
        }
        return c;
    }

    void GenerateLevel()
    {
        world.GenerateMatrix();
        for (int i = 0; i < world.matrix.size(); i++)
        {
            std::string room = world.matrix[i];
            if (room != "0000" && room.length() == 4) { world.matrix[i] = world.matrix[i]+"-"+std::to_string(rand()%map.room_tally[room]); }
        }
        LoadMap();
    }

    void LoadMap()
    {
        std::string _dir = world.matrix[room_y*world.width+room_x];
        map_dir.text=_dir+".map"; map_dir.cursor=map_dir.text.length();
        map.LoadData(_dir);
    }

    void DrawButton(Button b) { b.Draw(this, color2, color4, color5, color6); }
    void DrawEntry(Entry e) { e.Draw(this, color1, color3, color4, color5, color6); }

    void DrawGrid()
    {
        for (int y = 0; y < map.height*var::tile+1; y += var::tile) { DrawLine(0, y, map.width*var::tile, y, color5); }
        for (int x = 0; x < map.width*var::tile+1; x += var::tile) { DrawLine(x, 0, x, map.height*var::tile, color5); }
    }

    void DrawChars()
    {
        for (int y = 0; y < map.height; y++)
        {
            for (int x = 0; x < map.width; x++)
            {
                float X = x*var::tile, Y = y*var::tile;
                std::string tile = ""; tile += map.matrix[layer][y*map.width+x];
                DrawStringDecal({ X,Y }, tile, color6, { 2.0,2.0 });
            }
        }
    }

    void DrawTiles()
    {
        for (int l = 0; l < map.layers; l++)
        {
            for (int y = 0; y < map.height; y++)
            {
                for (int x = 0; x < map.width; x++)
                {
                    char _t=map.matrix[l][y*map.width+x];
                    float t=float(var::tile), X=x*t, Y=y*t;
                    float tx=map.Neighbors(x, y, l, _t)*var::tile, ty=map.keys[_t]*var::tile;
                    DrawPartialDecal({ X,Y }, tileset.Decal(), { tx,ty }, { 16.f, 16.f });
                }
            }
        }
    }

    void DrawObjects()
    {
    }

    void DrawTileset()
    {
        float t = var::tile*3.0;
        float mx = GetMouseX();
        float my = GetMouseY();
        int count = 0;
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                float X = (x*t)+(map.width*var::tile)+2;
                float Y = (y*t)+(var::tile*4);
                float tx=0, ty=count*var::tile;
                DrawPartialDecal({ X,Y }, tileset.Decal(), { tx,ty }, { 16.0,16.0 }, { 3.0,3.0 }, color0);
                if (mx > X && mx < X+t && my > Y && my < Y+t)
                {
                    DrawPartialDecal({ X,Y }, tileset.Decal(), { tx,ty }, { 16.0,16.0 }, { 3.0,3.0 });
                    if (GetMouse(0).bPressed)
                    {
                        switch (count)
                        {
                            case 0 : { selected = ' '; } break;
                            case 1 : { selected = '.'; } break;
                            case 2 : { selected = ','; } break;
                            case 3 : { selected = ':'; } break;
                            case 4 : { selected = ';'; } break;
                            case 5 : { selected = '%'; } break;
                            case 6 : { selected = '&'; } break;
                            case 7 : { selected = '#'; } break;
                        }
                    }
                }
                count++;
            }
        }
    }

    void DrawObjectset()
    {
    }

    void DrawMinimap(int X, int Y)
    {
        int scale = 3;
        FillRect(X, Y, world.width*scale, world.height*scale, color1);
        DrawRect(X-1, Y-1, (world.width*scale)+1, (world.height*scale)+1, color5);
        for (int y = 0; y < world.height; y++)
        {
            for (int x = 0; x < world.width; x++)
            {
                int offx=(x*scale)+X, offy=(y*scale)+Y;
                if (world.matrix[y*world.width+x] != "0000") { DrawRect(offx, offy, scale, scale, color4); }
            }
        }
        DrawRect((room_x*scale)+X, (room_y*scale)+Y, scale, scale, color6);
    }

    void DrawHUD()
    {
        int X = GetMouseX(), Y = GetMouseY();
        int x = X/var::tile, y = Y/var::tile;
        char _t = map.matrix[layer][y*map.width+x];
        std::string l = std::to_string(layer);
        std::string n = std::to_string(map.Neighbors(x, y, layer, _t));
        std::string t = ""+std::to_string(selected);
        float xoff = map.width*var::tile;
        if (map.GetCollision(x, y, layer)) { n += " Collision"; }
        DrawStringDecal({ xoff,0  }, " Layer:      "+l, color6, { 1.0,1.0 });
        DrawStringDecal({ xoff,8  }, " Cell Value: "+n, color6, { 1.0,1.0 });
        DrawStringDecal({ xoff,16 }, " Tile Value: "+t, color6, { 1.0,1.0 });

        // Button Panel
        FillRect(xoff+(200), 48, 55, 223, color1);
        DrawRect(xoff+(200), 48, 55, 223, color5);

        map_dir.Update(GetCharacter());
        DrawEntry(map_dir);

        Button save_layer      = Button(xoff+(204),  52.0, 47.0, 14.0, 1.0, "Save");   DrawButton(save_layer);
        Button load_layer      = Button(xoff+(204),  68.0, 47.0, 14.0, 1.0, "Load");   DrawButton(load_layer);
        Button increment_layer = Button(xoff+(204),  89.0, 47.0, 14.0, 1.0, "Layer+"); DrawButton(increment_layer);
        Button decrement_layer = Button(xoff+(204), 105.0, 47.0, 14.0, 1.0, "Layer-"); DrawButton(decrement_layer);
        Button append_layer    = Button(xoff+(204), 126.0, 47.0, 14.0, 1.0, "Append"); DrawButton(append_layer);
        Button insert_layer    = Button(xoff+(204), 142.0, 47.0, 14.0, 1.0, "Insert"); DrawButton(insert_layer);
        Button delete_layer    = Button(xoff+(204), 158.0, 47.0, 14.0, 1.0, "Delete"); DrawButton(delete_layer);
        Button generate        = Button(xoff+(225), 198.0,  9.0,  9.0, 0.5, "5");     DrawButton(generate);
        Button move_up         = Button(xoff+(225), 188.0,  9.0,  9.0, 0.5, "8");     DrawButton(move_up);
        Button move_down       = Button(xoff+(225), 208.0,  9.0,  9.0, 0.5, "2");   DrawButton(move_down);
        Button move_left       = Button(xoff+(215), 198.0,  9.0,  9.0, 0.5, "4");   DrawButton(move_left);
        Button move_right      = Button(xoff+(235), 198.0,  9.0,  9.0, 0.5, "6");  DrawButton(move_right);

        if (save_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.SaveData(world.matrix[room_y*world.width+room_x]); map.SaveTally(); }
        if (load_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.LoadData(map_dir.text.substr(0, map_dir.Size()-4) ); }
        if (increment_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { if (layer < map.layers-1) layer++; }
        if (decrement_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { if (layer > 0) layer--; }
        if (append_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.AppendLayer(); }
        if (insert_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.InsertLayer(layer); }
        if (delete_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.DeleteLayer(layer); }
        bool load_map = false;
        if (generate.IsColliding(X, Y) && GetMouse(0).bPressed)    { world.GenerateMatrix(); load_map = true; }
        if (move_up.IsColliding(X, Y) && GetMouse(0).bPressed)    { if (room_y > 0)                   { room_y--; load_map = true; } }
        if (move_down.IsColliding(X, Y) && GetMouse(0).bPressed)  { if (room_y < var::world_height-1) { room_y++; load_map = true; } }
        if (move_left.IsColliding(X, Y) && GetMouse(0).bPressed)  { if (room_x > 0)                   { room_x--; load_map = true; } }
        if (move_right.IsColliding(X, Y) && GetMouse(0).bPressed) { if (room_x < var::world_width-1)  { room_x++; load_map = true; } }
        if (load_map) { LoadMap(); }

        DrawGrid(); DrawTileset(); DrawMinimap(var::width-52, var::height-52);
    }

    void Update()
    {
        int x = GetMouseX()/var::tile, y = GetMouseY()/var::tile;
        Clear(color2);
        
        // Input
        bool load_map = false;
        if (GetKey(olc::NP8).bPressed) { if (room_y > 0)                   { room_y--; load_map = true; } }
        if (GetKey(olc::NP2).bPressed) { if (room_y < var::world_height-1) { room_y++; load_map = true; } }
        if (GetKey(olc::NP4).bPressed) { if (room_x > 0)                   { room_x--; load_map = true; } }
        if (GetKey(olc::NP6).bPressed) { if (room_x < var::world_width-1)  { room_x++; load_map = true; } }
        if (load_map) { LoadMap(); }
        if (GetKey(olc::NP5).bPressed) { world.GenerateMatrix(); GenerateLevel(); }
        if (GetKey(olc::TAB).bPressed) { tile_mode = !tile_mode; }
        if (GetMouse(0).bHeld) { map.SetCell(selected, x, y, layer); }

        // Draw
        if (tile_mode) { DrawTiles(); } else { DrawChars(); }
        DrawHUD();
    }

    bool OnUserCreate() override
    {
        tileset.Load("../../DeathByLiving/Data/tiles-16x16.png");
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Update();
        return true;
    }
};
