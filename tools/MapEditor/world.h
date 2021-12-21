struct V2 { int x, y; V2(int X, int Y) { x=X; y=Y; } };

class World
{

public:

    int width;
    int height;

    std::vector<std::string> matrix;

    World(int w, int h) { width = w; height = h; InitMatrix(); }

    void EmptyMatrix() { matrix.clear(); }
    void ClearMatrix() { matrix.clear(); InitMatrix(); }
    void InitMatrix() { for (int y = 0; y < height; y++) { for (int x = 0; x < width; x++) { matrix.push_back("0000"); } } }

    void GenerateMatrix()
    {
        ClearMatrix();
        bool generating = true;
        std::vector<V2> checked;
        std::vector<V2> to_check;
        to_check.push_back(V2(8, 8));
        matrix[8*width+8] = "1111";

        while (generating)
        {
            bool can_do = true;
            int x, y;
            if (to_check.size() > 0) { x = to_check[0].x; y = to_check[0].y; to_check.erase(to_check.begin()); } else { generating = false; break; }
            std::string room = matrix[y*width+x], n8 = room.substr(0, 1), n4 = room.substr(1, 1), n2 = room.substr(2, 1), n1 = room.substr(3, 1);
            for (int i = 0; i < checked.size(); i++) { if (checked[i].x == x and checked[i].y == y) { can_do = false; } }
            if (can_do)
            {
                if (y != 0 && y < height-1 && n1 == "1") { matrix[(y-1)*width+x] = GetRoom(1); to_check.push_back(V2(x, y-1)); }
                else { if (n1 == "1") matrix[y*width+x] = "1000"; }
                if (y != height-1 && y > 0 && n8 == "1") { matrix[(y+1)*width+x] = GetRoom(8); to_check.push_back(V2(x, y+1)); }
                else { if (n8 == "1") matrix[y*width+x] = "0001"; }
                if (x != 0 && x < width -1 && n2 == "1") { matrix[y*width+(x-1)] = GetRoom(2); to_check.push_back(V2(x-1, y)); }
                else { if (n2 == "1") matrix[y*width+x] = "0100"; }
                if (x != width -1 && x > 0 && n4 == "1") { matrix[y*width+(x+1)] = GetRoom(4); to_check.push_back(V2(x+1, y)); }
                else { if (n4 == "1") matrix[y*width+x] = "0010"; }
                checked.push_back(V2(x, y));
            }
        }
    }

    std::string GetRoom(int door)
    {
        std::string room;
        std::string n1 = "0"; if (rand()%100<25) n1 = "1";
        std::string n2 = "0"; if (rand()%100<25) n2 = "1";
        std::string n3 = "0"; if (rand()%100<25) n3 = "1";
        switch (door)
        {
            case 1 : { room = "1"+n1+n2+n3; } break;
            case 2 : { room = n1+"1"+n2+n3; } break;
            case 4 : { room = n1+n2+"1"+n3; } break;
            case 8 : { room = n1+n2+n3+"1"; } break;
        }
        return room;
    }

};
