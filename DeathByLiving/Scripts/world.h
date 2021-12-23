class World
{

public:

    int width;
    int height;
    struct V2 { int x, y; V2(int X, int Y) { x=X; y=Y; } };

public:

    std::vector<std::string> matrix;
    std::vector<V2> checked;
    std::vector<V2> to_check;

public:

    World(int w, int h) { width = w; height = h; InitMatrix(); }

    void EmptyMatrix() { matrix.clear(); }
    void ClearMatrix() { matrix.clear(); InitMatrix(); }
    void InitMatrix() { for (int y = 0; y < height; y++) { for (int x = 0; x < width; x++) { matrix.push_back("0000"); } } }

    void GenerateMatrix()
    {
        ClearMatrix();
        GenerateCorridors(8, 8);
        TileMatrix();
    }

    void GenerateCorridors(int sx, int sy)
    {
        int north=rand()%int(float(height/2)*0.8), south=rand()%int(float(height/2)*0.8), east=rand()%int(float(width/2)*0.8), west=rand()%int(float(width/2)*0.8);
        for (int n = 0; n < north; n++) { matrix[(sy-n)*width+sx] = "1111"; } if (rand()%100 < 50) { GenerateBlob(sx, sy-(north-1), rand()%16); }
        for (int w = 0; w < west; w++)  { matrix[sy*width+(sx-w)] = "1111"; } if (rand()%100 < 50) { GenerateBlob(sx-(west-1),  sy, rand()%16); }
        for (int e = 0; e < east; e++)  { matrix[sy*width+(sx+e)] = "1111"; } if (rand()%100 < 50) { GenerateBlob(sx+(east-1),  sy, rand()%16); }
        for (int s = 0; s < south; s++) { matrix[(sy+s)*width+sx] = "1111"; } if (rand()%100 < 50) { GenerateBlob(sx, sy+(south-1), rand()%16); }
    }

    void GenerateBlob(int sx, int sy, int room_limit)
    {
        bool generating = true;
        int room_count=1;
        to_check.push_back(V2(sx, sy)); matrix[sy*width+sx] = "1111";
        while (generating)
        {
            int x, y, c1=rand()%80, c2=rand()%80, c4=rand()%80, c8=rand()%80;
            if (to_check.size() > 0) { x = to_check[0].x; y = to_check[0].y; to_check.erase(to_check.begin()); } else { generating = false; }//break; }
            if (room_count >= room_limit) { generating = false; }//break; }
            if (!InChecked(x, y))
            {
                if (y != 0 && y < height-1 && rand()%100 < c1) { matrix[(y-1)*width+x] = "1111"; to_check.push_back(V2(x, y-1)); room_count++; }
                if (x != 0 && x < width -1 && rand()%100 < c2) { matrix[y*width+(x-1)] = "1111"; to_check.push_back(V2(x-1, y)); room_count++; }
                if (x != width -1 && x > 0 && rand()%100 < c4) { matrix[y*width+(x+1)] = "1111"; to_check.push_back(V2(x+1, y)); room_count++; }
                if (y != height-1 && y > 0 && rand()%100 < c8) { matrix[(y+1)*width+x] = "1111"; to_check.push_back(V2(x, y+1)); room_count++; }
                checked.push_back(V2(x, y));
            }
        }
        checked.clear(); to_check.clear();
        if (room_count == 1) { matrix[sy*width+sx] = "1111"; }
    }

    void TileMatrix()
    {
        bool* level = new bool[width*height] {false};
        for (int i = 0; i < matrix.size(); i++) { if (matrix[i] != "0000") level[i] = true; }
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                std::string n1 = "0"; if (y != 0 && y < height-1 && level[(y-1)*width+x] == true) { n1 = "1"; }
                std::string n2 = "0"; if (x != width -1 && x > 0 && level[y*width+(x-1)] == true) { n2 = "1"; }
                std::string n4 = "0"; if (x != 0 && x < width -1 && level[y*width+(x+1)] == true) { n4 = "1"; }
                std::string n8 = "0"; if (y != height-1 && y > 0 && level[(y+1)*width+x] == true) { n8 = "1"; }
                if (level[y*width+x]) { matrix[y*width+x] = n8+n4+n2+n1; }
            }
        }
        delete level;
    }

    bool InChecked(int x, int y) { for (int i = 0; i < checked.size(); i++) { if (checked[i].x == x && checked[i].y == y) { return true; } } return false;}

};
