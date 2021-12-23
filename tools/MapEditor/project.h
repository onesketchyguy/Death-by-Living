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
    char selected = ' ';
    int layer = 0;
    int room_x = 8;
    int room_y = 8;
    std::string _tile = "gravel";
    Entry map_dir = Entry(var::room_width*var::tile, 33, 1.0, "test.map", 32);
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

    void LoadMap() { std::string _dir = world.matrix[room_y*world.width+room_x]+".map"; map_dir.text=_dir; map_dir.cursor=map_dir.text.length(); map.LoadData(_dir); }

    void DrawButton(Button b)
    {
        DrawStringDecal({ b.TextX(),b.TextY() }, b.text, color6, {b.font, b.font});
        if (b.IsColliding(GetMouseX(), GetMouseY())) { DrawRect(b.x, b.y, b.width, b.height, color5); return; }
        DrawRect(b.x, b.y, b.width, b.height, color4);
    }

    void DrawEntry(Entry e)
    {
        float x = e.x+(float(e.cursor)*(8.0*e.font));
        float y = e.y-(e.font*4.0);
        FillRect(e.x, y, e.max_chars*(8.0*e.font), 16.0*e.font, color1);
        DrawRect(e.x, y, e.max_chars*(8.0*e.font), 16.0*e.font, color5);
        DrawStringDecal({ e.x,e.y }, e.text, color6, {e.font, e.font});
        FillRect(x, y, e.font*8.0, e.font*16.0, color3);
        DrawRect(x, y, e.font*8.0, e.font*16.0, color4);
    }

    void DrawGrid()
    {
        for (int y = 0; y < var::room_height*var::tile+1; y += var::tile) { DrawLine(0, y, var::room_width*var::tile, y, color5); }
        for (int x = 0; x < var::room_width*var::tile+1; x += var::tile) { DrawLine(x, 0, x, var::room_height*var::tile, color5); }
    }

    void DrawChars()
    {
        for (int y = 0; y < var::room_height; y++)
        {
            for (int x = 0; x < var::room_width; x++)
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
            for (int y = 0; y < var::room_height; y++)
            {
                for (int x = 0; x < var::room_width; x++)
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
                float X = (x*t)+(var::room_width*var::tile)+2;
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

    void DrawMinimap()
    {
        int X = (var::room_width*var::tile)+210;
        int Y = 6;
        DrawRect(X-1, Y-1, 17, 17, color1);
        DrawRect(X-1, Y-1, 17, 17, color5);
        for (int y = 0; y < var::world_height; y++)
        {
            for (int x = 0; x < var::world_width; x++)
            {
                if (world.matrix[y*world.width+x] != "0000") { Draw(x+X, y+Y, color4); }
                if (x == room_x && y == room_y) Draw(x+X, y+Y, color6);
            }
        }
    }

    void DrawHUD()
    {
        int X = GetMouseX(), Y = GetMouseY();
        int x = X/var::tile, y = Y/var::tile;
        char _t = map.matrix[layer][y*map.width+x];
        std::string l = std::to_string(layer);
        std::string n = std::to_string(map.Neighbors(x, y, layer, _t));
        std::string t = ""+std::to_string(selected);
        float xoff = var::room_width*var::tile;
        if (map.GetCollision(x, y, layer)) { n += " Collision"; }
        DrawStringDecal({ xoff,0  }, " Layer:      "+l, color6, { 1.0,1.0 });
        DrawStringDecal({ xoff,8  }, " Cell Value: "+n, color6, { 1.0,1.0 });
        DrawStringDecal({ xoff,16 }, " Tile Value: "+t, color6, { 1.0,1.0 });

        // Button Panel
        FillRect(xoff+(200), 48, 55, 212, color1);
        DrawRect(xoff+(200), 48, 55, 212, color5);

        map_dir.Update(GetCharacter());
        DrawEntry(map_dir);

        Button save_layer      = Button(xoff+(204),  52.0, 47.0, 14.0, 1.0, "Save");   DrawButton(save_layer);
        Button load_layer      = Button(xoff+(204),  68.0, 47.0, 14.0, 1.0, "Load");   DrawButton(load_layer);
        Button increment_layer = Button(xoff+(204),  89.0, 47.0, 14.0, 1.0, "Layer+"); DrawButton(increment_layer);
        Button decrement_layer = Button(xoff+(204), 105.0, 47.0, 14.0, 1.0, "Layer-"); DrawButton(decrement_layer);
        Button append_layer    = Button(xoff+(204), 126.0, 47.0, 14.0, 1.0, "Append"); DrawButton(append_layer);
        Button insert_layer    = Button(xoff+(204), 142.0, 47.0, 14.0, 1.0, "Insert"); DrawButton(insert_layer);
        Button delete_layer    = Button(xoff+(204), 158.0, 47.0, 14.0, 1.0, "Delete"); DrawButton(delete_layer);
        Button move_up         = Button(xoff+(237),   1.0,  8.0,  8.0, 1.0, "");     DrawButton(move_up);
        Button move_down       = Button(xoff+(237),  19.0,  8.0,  8.0, 1.0, "");   DrawButton(move_down);
        Button move_left       = Button(xoff+(228),  10.0,  8.0,  8.0, 1.0, "");   DrawButton(move_left);
        Button move_right      = Button(xoff+(246),  10.0,  8.0,  8.0, 1.0, "");  DrawButton(move_right);

        if (save_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.SaveData(map_dir.text); }
        if (load_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.LoadData(map_dir.text); }
        if (increment_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { if (layer < map.layers-1) layer++; }
        if (decrement_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { if (layer > 0) layer--; }
        if (append_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.AppendLayer(); }
        if (insert_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.InsertLayer(layer); }
        if (delete_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.DeleteLayer(layer); }
        bool load_map = false;
        if (move_up.IsColliding(X, Y) && GetMouse(0).bPressed)    { if (room_y > 0)                   { room_y--; load_map = true; } }
        if (move_down.IsColliding(X, Y) && GetMouse(0).bPressed)  { if (room_y < var::world_height-1) { room_y++; load_map = true; } }
        if (move_left.IsColliding(X, Y) && GetMouse(0).bPressed)  { if (room_x > 0)                   { room_x--; load_map = true; } }
        if (move_right.IsColliding(X, Y) && GetMouse(0).bPressed) { if (room_x < var::world_width-1)  { room_x++; load_map = true; } }
        if (load_map) { LoadMap(); }
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
        if (GetKey(olc::ENTER).bPressed) { world.GenerateMatrix(); LoadMap(); }
        if (GetKey(olc::TAB).bPressed) { tile_mode = !tile_mode; }
        if (GetMouse(0).bHeld) { map.SetCell(selected, x, y, layer); }

        // Draw
        if (tile_mode) { DrawTiles(); } else { DrawChars(); }
        DrawGrid(); DrawHUD(); DrawTileset(); DrawMinimap();
    }

    bool OnUserCreate() override
    {
        //tileset = olc::Renderable();
        tileset.Load("../../DeathByLiving/Data/tiles-16x16.png");
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Update();
        return true;
    }
};
