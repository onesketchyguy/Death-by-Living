class Game : public olc::PixelGameEngine
{

public:
    Game()
    {
        sAppName = "Map Editor";
    }

public:

    bool mode = true;
    char selected = '.';
    int layer = 0;
    int room_x;
    int room_y;
    std::string _tile = "gravel";
    std::string map_dir = "test.map";
    Map map = Map(var::room_width, var::room_height, 3);
    olc::Renderable tileset;



    bool ShiftKey() { return GetKey(olc::Key::SHIFT).bHeld; }

    char GetCharacter()
    {
        char c = '~';
        if (!ShiftKey())
        {
            if (GetKey(olc::Key::A).bPressed) { c = 'a'; }
            else if (GetKey(olc::Key::B).bPressed) { c = 'b'; }
            else if (GetKey(olc::Key::C).bPressed) { c = 'c'; }
            else if (GetKey(olc::Key::D).bPressed) { c = 'd'; }
            else if (GetKey(olc::Key::E).bPressed) { c = 'e'; }
            else if (GetKey(olc::Key::F).bPressed) { c = 'f'; }
            else if (GetKey(olc::Key::G).bPressed) { c = 'g'; }
            else if (GetKey(olc::Key::H).bPressed) { c = 'h'; }
            else if (GetKey(olc::Key::I).bPressed) { c = 'i'; }
            else if (GetKey(olc::Key::J).bPressed) { c = 'j'; }
            else if (GetKey(olc::Key::K).bPressed) { c = 'k'; }
            else if (GetKey(olc::Key::L).bPressed) { c = 'l'; }
            else if (GetKey(olc::Key::M).bPressed) { c = 'm'; }
            else if (GetKey(olc::Key::N).bPressed) { c = 'n'; }
            else if (GetKey(olc::Key::O).bPressed) { c = 'o'; }
            else if (GetKey(olc::Key::P).bPressed) { c = 'p'; }
            else if (GetKey(olc::Key::Q).bPressed) { c = 'q'; }
            else if (GetKey(olc::Key::R).bPressed) { c = 'r'; }
            else if (GetKey(olc::Key::S).bPressed) { c = 's'; }
            else if (GetKey(olc::Key::T).bPressed) { c = 't'; }
            else if (GetKey(olc::Key::U).bPressed) { c = 'u'; }
            else if (GetKey(olc::Key::V).bPressed) { c = 'v'; }
            else if (GetKey(olc::Key::W).bPressed) { c = 'w'; }
            else if (GetKey(olc::Key::X).bPressed) { c = 'x'; }
            else if (GetKey(olc::Key::Y).bPressed) { c = 'y'; }
            else if (GetKey(olc::Key::Z).bPressed) { c = 'z'; }
            else if (GetKey(olc::Key::K0).bPressed) { c = '0'; }
            else if (GetKey(olc::Key::K1).bPressed) { c = '1'; }
            else if (GetKey(olc::Key::K2).bPressed) { c = '2'; }
            else if (GetKey(olc::Key::K3).bPressed) { c = '3'; }
            else if (GetKey(olc::Key::K4).bPressed) { c = '4'; }
            else if (GetKey(olc::Key::K5).bPressed) { c = '5'; }
            else if (GetKey(olc::Key::K6).bPressed) { c = '6'; }
            else if (GetKey(olc::Key::K7).bPressed) { c = '7'; }
            else if (GetKey(olc::Key::K8).bPressed) { c = '8'; }
            else if (GetKey(olc::Key::K9).bPressed) { c = '9'; }
            else if (GetKey(olc::Key::EQUALS).bPressed) { c = '='; }
            else if (GetKey(olc::Key::COMMA).bPressed) { c = ','; }
            else if (GetKey(olc::Key::MINUS).bPressed) { c = '-'; }
            else if (GetKey(olc::Key::PERIOD).bPressed) { c = '.'; }
            else if (GetKey(olc::Key::OEM_1).bPressed) { c = ';'; }
            else if (GetKey(olc::Key::OEM_2).bPressed) { c = '/'; }
            else if (GetKey(olc::Key::OEM_4).bPressed) { c = '['; }
            else if (GetKey(olc::Key::OEM_5).bPressed) { c = '\\'; }
            else if (GetKey(olc::Key::OEM_7).bPressed) { c = '\''; }
            else if (GetKey(olc::Key::SPACE).bPressed) { c = ' '; }

        }
        else if (ShiftKey())
        {
            if (GetKey(olc::Key::A).bPressed) { c = 'A'; }
            else if (GetKey(olc::Key::B).bPressed) { c = 'B'; }
            else if (GetKey(olc::Key::C).bPressed) { c = 'C'; }
            else if (GetKey(olc::Key::D).bPressed) { c = 'D'; }
            else if (GetKey(olc::Key::E).bPressed) { c = 'E'; }
            else if (GetKey(olc::Key::F).bPressed) { c = 'F'; }
            else if (GetKey(olc::Key::G).bPressed) { c = 'G'; }
            else if (GetKey(olc::Key::H).bPressed) { c = 'H'; }
            else if (GetKey(olc::Key::I).bPressed) { c = 'I'; }
            else if (GetKey(olc::Key::J).bPressed) { c = 'J'; }
            else if (GetKey(olc::Key::K).bPressed) { c = 'K'; }
            else if (GetKey(olc::Key::L).bPressed) { c = 'L'; }
            else if (GetKey(olc::Key::M).bPressed) { c = 'M'; }
            else if (GetKey(olc::Key::N).bPressed) { c = 'N'; }
            else if (GetKey(olc::Key::O).bPressed) { c = 'O'; }
            else if (GetKey(olc::Key::P).bPressed) { c = 'P'; }
            else if (GetKey(olc::Key::Q).bPressed) { c = 'Q'; }
            else if (GetKey(olc::Key::R).bPressed) { c = 'R'; }
            else if (GetKey(olc::Key::S).bPressed) { c = 'S'; }
            else if (GetKey(olc::Key::T).bPressed) { c = 'T'; }
            else if (GetKey(olc::Key::U).bPressed) { c = 'U'; }
            else if (GetKey(olc::Key::V).bPressed) { c = 'V'; }
            else if (GetKey(olc::Key::W).bPressed) { c = 'W'; }
            else if (GetKey(olc::Key::X).bPressed) { c = 'X'; }
            else if (GetKey(olc::Key::Y).bPressed) { c = 'Y'; }
            else if (GetKey(olc::Key::Z).bPressed) { c = 'Z'; }
            else if (GetKey(olc::Key::K0).bPressed) { c = ')'; }
            else if (GetKey(olc::Key::K1).bPressed) { c = '!'; }
            else if (GetKey(olc::Key::K2).bPressed) { c = '@'; }
            else if (GetKey(olc::Key::K3).bPressed) { c = '#'; }
            else if (GetKey(olc::Key::K4).bPressed) { c = '$'; }
            else if (GetKey(olc::Key::K5).bPressed) { c = '%'; }
            else if (GetKey(olc::Key::K6).bPressed) { c = '^'; }
            else if (GetKey(olc::Key::K7).bPressed) { c = '&'; }
            else if (GetKey(olc::Key::K8).bPressed) { c = '*'; }
            else if (GetKey(olc::Key::K9).bPressed) { c = '('; }
            else if (GetKey(olc::Key::OEM_1).bPressed) { c = ':'; }
            else if (GetKey(olc::Key::OEM_2).bPressed) { c = '?'; }
            else if (GetKey(olc::Key::OEM_4).bPressed) { c = '{'; }
            else if (GetKey(olc::Key::OEM_5).bPressed) { c = '|'; }
            else if (GetKey(olc::Key::OEM_7).bPressed) { c = '"'; }
            else if (GetKey(olc::Key::EQUALS).bPressed) { c = '+'; }
            else if (GetKey(olc::Key::COMMA).bPressed) { c = '<'; }
            else if (GetKey(olc::Key::MINUS).bPressed) { c = '_'; }
            else if (GetKey(olc::Key::PERIOD).bPressed) { c = '>'; }
        }
        else
        {
            if (GetKey(olc::Key::BACK).bPressed) { c = '-'; }
            if (GetKey(olc::Key::LEFT).bPressed) { c = '>'; }
            if (GetKey(olc::Key::RIGHT).bPressed) { c = '<'; }
        }
        return c;
    }

    void DrawButton(Button b)
    {
        DrawStringDecal({ b.TextX(),b.TextY() }, b.text, olc::WHITE, {b.font, b.font});
        if (b.IsColliding(GetMouseX(), GetMouseY()))
        { DrawRect(b.x, b.y, b.width, b.height, olc::WHITE); return; }
        DrawRect(b.x, b.y, b.width, b.height, olc::DARK_GREY);
    }

    void DrawEntry(Entry e)
    {
        float x = e.x+(float(e.cursor)*(8.0*e.font));
        float y = e.y-(e.font*4.0);
        DrawStringDecal({ e.x,e.y }, e.text, olc::WHITE, {e.font, e.font});
        FillRect(x, y, e.font*8.0, e.font*16.0, olc::WHITE);
    }

    void DrawGrid()
    {
        for (int y = 0; y < var::room_height*var::tile+1; y += var::tile) { DrawLine(0, y, var::room_width*var::tile, y); }
        for (int x = 0; x < var::room_width*var::tile+1; x += var::tile) { DrawLine(x, 0, x, var::room_height*var::tile); }
    }

    void DrawChars()
    {
        for (int y = 0; y < var::room_height; y++)
        {
            for (int x = 0; x < var::room_width; x++)
            {
                float X = x*var::tile, Y = y*var::tile;
                std::string tile = ""; tile += map.matrix[layer][y*map.width+x];
                DrawStringDecal({ X,Y }, tile, olc::Pixel(255,255,255), { 2.0,2.0 });
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
                DrawPartialDecal({ X,Y }, tileset.Decal(), { tx,ty }, { 16.0,16.0 }, { 3.0,3.0 }, olc::Pixel(128, 128, 128));
                if (mx > X && mx < X+t && my > Y && my < Y+t)
                {
                    DrawPartialDecal({ X,Y }, tileset.Decal(), { tx,ty }, { 16.0,16.0 }, { 3.0,3.0 }, olc::Pixel(255, 255, 255));
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

    void DrawHUD()
    {
        int X = GetMouseX(), Y = GetMouseY();
        int x = X/var::tile, y = Y/var::tile;
        char _t = map.matrix[layer][y*map.width+x];
        std::string l = std::to_string(layer);
        std::string n = std::to_string(map.Neighbors(x, y, layer, _t));
        std::string t = ""+std::to_string(selected);
        float xoff = var::room_width*var::tile;
        DrawStringDecal({ xoff,0  }, " Layer:      "+l, olc::Pixel(255,255,255), { 1.0,1.0 });
        DrawStringDecal({ xoff,8  }, " Cell Value: "+n, olc::Pixel(255,255,255), { 1.0,1.0 });
        DrawStringDecal({ xoff,16 }, " Tile Value: "+t, olc::Pixel(255,255,255), { 1.0,1.0 });

        FillRect(xoff+(200), 48, 56, 212, olc::Pixel(8, 8, 12));

        Button save_layer = Button(xoff+(204), 52.0, 48.0, 16.0, 1.0, "Save"); DrawButton(save_layer);
        Button load_layer = Button(xoff+(204), 68.0, 48.0, 16.0, 1.0, "Load"); DrawButton(load_layer);
        Button increment_layer = Button(xoff+(204), 89.0, 48.0, 16.0, 1.0, "Layer+"); DrawButton(increment_layer);
        Button decrement_layer = Button(xoff+(204), 105.0, 48.0, 16.0, 1.0, "Layer-"); DrawButton(decrement_layer);
        Button append_layer = Button(xoff+(204), 126.0, 48.0, 16.0, 1.0, "Append"); DrawButton(append_layer);
        Button insert_layer = Button(xoff+(204), 142.0, 48.0, 16.0, 1.0, "Insert"); DrawButton(insert_layer);
        Button delete_layer = Button(xoff+(204), 158.0, 48.0, 16.0, 1.0, "Delete"); DrawButton(delete_layer);

        if (save_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.SaveData(map_dir); }
        if (load_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.LoadData(map_dir); }
        if (increment_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { if (layer < map.layers-1) layer++; }
        if (decrement_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { if (layer > 0) layer--; }
        if (append_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.AppendLayer(); }
        if (insert_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.InsertLayer(layer); }
        if (delete_layer.IsColliding(X, Y) && GetMouse(0).bPressed) { map.DeleteLayer(layer); }
    }

    void Update()
    {
        int x = GetMouseX()/var::tile, y = GetMouseY()/var::tile;
        Clear(olc::Pixel(16, 16, 24));
        
        // Input
        char new_select = GetCharacter();
        if (new_select != '~') { selected = new_select; }
        if (GetKey(olc::TAB).bPressed) { mode = !mode; }
        if (GetKey(olc::NP_ADD).bPressed) { if (layer < map.layers-1) layer++; }
        if (GetKey(olc::NP_SUB).bPressed) { if (layer > 0) layer--; }
        if (GetMouse(0).bHeld) { map.SetCell(selected, x, y, layer); }
        if (GetKey(olc::CTRL).bHeld) { if (GetKey(olc::W).bPressed) { map.SaveData(map_dir); } if (GetKey(olc::R).bPressed) { map.LoadData(map_dir); } }

        // Draw
        if (mode) { DrawTiles(); } else { DrawChars(); }
        DrawGrid(); DrawHUD(); DrawTileset();
    }

    bool OnUserCreate() override
    {
        tileset = olc::Renderable();
        tileset.Load("../../DeathByLiving/Data/tiles-16x16.png");
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Update();
        return true;
    }
};