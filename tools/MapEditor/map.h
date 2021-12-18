class Map
{

public:

    int width;
    int height;
    int layers;

    std::vector<std::vector<char>> matrix = { {}, {} };

    std::map<char, int> keys =
    {
        { '.', 0 },
        { ',', 1 },
        { ':', 2 },
        { ';', 3 },
        { '%', 4 },
        { '&', 5 },
        { '#', 6 },
    };

    Map(int w, int h, int l=2) { width = w; height = h; layers = l; for (int i = 0; i < layers; i++) { InitMatrix(i); } }

    int Neighbors(int x, int y, int layer, char target)
    {
        int n = 0;
        int n8 = matrix[layer][(y-1)*width+x]; 
        int n4 = matrix[layer][y*width+(x-1)];
        int n2 = matrix[layer][y*width+(x+1)];
        int n1 = matrix[layer][(y+1)*width+x];
        if (target != ' ')
        {
            if (n8 == target) { n += 8; }
            if (n4 == target) { n += 4; }
            if (n2 == target) { n += 2; }
            if (n1 == target) { n += 1; }
        }
        return n;
    }

    void ClearMatrix(int layer) { matrix[layer].clear(); }
    void InitMatrix(int layer) { for (int i = 0; i < width*height; i++) { matrix[layer].push_back(' '); } }
    void SetCell(char tile, int x, int y, int layer) { if (x < width && y < height) { matrix[layer][y*width+x] = tile; } }

    void SaveData(std::string _dir)
    {
        std::fstream data_file;
        data_file.open(_dir);
        if (data_file.is_open())
        {
            for (int l = 0; l < layers; l++)
            {
                data_file << '>' << std::endl;
                for (int i = 0; i < matrix[l].size(); i++)
                {
                    data_file << matrix[l][i];
                    if (i % width == width-1) { data_file << std::endl; }
                }
            }
        }
        else
        { std::ofstream new_file (_dir); SaveData(_dir); }
    }

    void LoadData(std::string _dir)
    {
        std::string line;
        std::fstream data_file;
        data_file.open(_dir);
        if (data_file.is_open())
        {
            int layer = 0;
            int y = 0;
            while (getline(data_file, line))
            {
                if (line.length() > 0)
                {
                    if (line.substr(0, 1) != ">") { for (int x = 0; x < line.length(); x++) { matrix[layer][y*width+x] = line.at(x); } y++; }
                    else { layer++; y = 0; }
                }
                std::cout << y << std::endl;
            }
            data_file.close();
            layers = layer+1;
        }
    }

};
