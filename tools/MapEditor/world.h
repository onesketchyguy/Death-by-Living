class World
{

public:

    int width;
    int height;

    std::vector<std::string> matrix;

    World(int w, int h) { width = w; height = h; InitMatrix(); }

    struct V2 { int x, y; V2(int X, int Y) { x=X; y=Y; } };

    void EmptyMatrix() { matrix.clear(); }
    void ClearMatrix() { matrix.clear(); InitMatrix(); }
    void InitMatrix() { for (int y = 0; y < height; y++) { for (int x = 0; x < width; x++) { matrix.push_back("0000"); } } }

    void GenerateMatrix(int sx = 8, int sy = 8)
    {
        ClearMatrix();
        bool generating = true;
        std::vector<V2> checked;
        std::vector<V2> to_check;
        bool level[width*height] {false};

        to_check.push_back(V2(sx, sy));
        level[sy*width+sx] = true;

        int room_count=1, room_limit=16;
        while (generating)
        {
            bool can_do = true;
            int x, y, c1=rand()%80, c2=rand()%80, c4=rand()%80, c8=rand()%80;
            if (to_check.size() > 0) { x = to_check[0].x; y = to_check[0].y; to_check.erase(to_check.begin()); } else { generating = false; break; }
            if (room_count >= room_limit) { generating = false; break; }
            for (int i = 0; i < checked.size(); i++) { if (checked[i].x == x && checked[i].y == y) { can_do = false; } }
            if (can_do)
            {
                if (y != 0 && y < height-1 && rand()%100 < c1) { level[(y-1)*width+x] = true; to_check.push_back(V2(x, y-1)); room_count++; }
                if (x != 0 && x < width -1 && rand()%100 < c2) { level[y*width+(x-1)] = true; to_check.push_back(V2(x-1, y)); room_count++; }
                if (x != width -1 && x > 0 && rand()%100 < c4) { level[y*width+(x+1)] = true; to_check.push_back(V2(x+1, y)); room_count++; }
                if (y != height-1 && y > 0 && rand()%100 < c8) { level[(y+1)*width+x] = true; to_check.push_back(V2(x, y+1)); room_count++; }
                checked.push_back(V2(x, y));
            }
        }
        std::cout << room_count << std::endl;
        checked.clear();

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int N = 1;
                std::string n1 = "0"; if (y != 0 && y < height-1 && level[(y-1)*width+x] == true) { n1 = "1"; }
                std::string n2 = "0"; if (x != width -1 && x > 0 && level[y*width+(x-1)] == true) { n2 = "1"; }
                std::string n4 = "0"; if (x != 0 && x < width -1 && level[y*width+(x+1)] == true) { n4 = "1"; }
                std::string n8 = "0"; if (y != height-1 && y > 0 && level[(y+1)*width+x] == true) { n8 = "1"; }
                if (N > 0) { matrix[y*width+x] = n8+n4+n2+n1; }
            }
        }
        if (room_count == 1) { matrix[sy*width+sx] = "1111"; }
    }

};
