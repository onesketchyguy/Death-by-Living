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
        GenerateCorridors(8, 8, 4, 4);
        TileMatrix();
    }

    void GenerateCorridors(int sx, int sy, int min_blobs=1, int blob_size=16)
    {
        int blob_count = 0;
        std::vector<int> blobs = {1, 2, 4, 8};
        int north=rand()%int((height)*0.4),
            south=rand()%int((height)*0.4),
            east=rand()%int((width)*0.4),
            west=rand()%int((width)*0.4);
        for (int n = 0; n < north; n++) { matrix[(sy-n)*width+sx] = "1111"; } if (rand()%100 < 50) { GenerateBlob(sx, sy-north, rand()%blob_size); blob_count++; }
        for (int w = 0; w < west; w++)  { matrix[sy*width+(sx-w)] = "1111"; } if (rand()%100 < 50) { GenerateBlob(sx-west,  sy, rand()%blob_size); blob_count++; }
        for (int e = 0; e < east; e++)  { matrix[sy*width+(sx+e)] = "1111"; } if (rand()%100 < 50) { GenerateBlob(sx+east,  sy, rand()%blob_size); blob_count++; }
        for (int s = 0; s < south; s++) { matrix[(sy+s)*width+sx] = "1111"; } if (rand()%100 < 50) { GenerateBlob(sx, sy+south, rand()%blob_size); blob_count++; }
        if (blob_count < min_blobs)
        {
            for (int b = 0; b < min_blobs; b++)
            {
                int choice = rand()%blobs.size();
                switch (choice)
                {
                    case 1 : { GenerateBlob(sx, sy-north, rand()%blob_size); } break;
                    case 2 : { GenerateBlob(sx-west,  sy, rand()%blob_size); } break;
                    case 4 : { GenerateBlob(sx+east,  sy, rand()%blob_size); } break;
                    case 8 : { GenerateBlob(sx, sy+south, rand()%blob_size); } break;
                }
                blobs.erase(blobs.begin()+choice);
            }
        }
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
