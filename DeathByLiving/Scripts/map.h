class Map
{
public:
    // Data
    int width = 0;
    int height = 0;
    int layers = 0;
    std::vector<std::vector<char>> matrix;
    std::map<char, int> keys = {
        {' ', 0}, {'@', 1},
        {'$', 2}, {'.', 3},
        {',', 4}, {':', 5},
        {';', 6}, {'v', 7},
        {'%', 8}, {'&', 9},
        {'<',10}, {'>',11},
        {'-',12}, {'=',13},
        {'#',14}, {'W',15}
    };
    std::map<std::string, int> room_tally = {
        { "0001", 1 },
        { "0010", 1 },
        { "0011", 1 },
        { "0100", 1 },
        { "0101", 1 },
        { "0110", 1 },
        { "0111", 1 },
        { "1000", 1 },
        { "1001", 1 },
        { "1010", 1 },
        { "1011", 1 },
        { "1100", 1 },
        { "1101", 1 },
        { "1110", 1 },
        { "1111", 1 }
    };

    // Map
    Map(int w, int h, int l) { width = w; height = h; for (int i = 0; i < l; i++) { AppendLayer(); } LoadTally(); }
    // Layer
    void EmptyLayer(int layer) { matrix[layer].clear(); }
    void ClearLayer(int layer) { matrix[layer].clear(); InitLayer(layer); }
    void InitLayer(int layer) { for (int i = 0; i < width*height; i++) { matrix[layer].push_back(' '); } }
    void AppendLayer() { std::vector<char> l; matrix.push_back(l); InitLayer(layers); layers++; }
    void InsertLayer(int layer) { std::vector<char> l; matrix.insert(matrix.begin()+layer, l); InitLayer(layer); layers++; }
    void DeleteLayer(int layer) { matrix.erase(matrix.begin()+layer); layers--; }
    // Cell
    void SetCell(char tile, int x, int y, int layer) { if (x < width && y < height) { matrix[layer][y*width+x] = tile; } }
    char GetCell(int x, int y, int layer) { if (matrix.size() <= layer && x >= 0 && x < width && y >= 0 && y < height) { return matrix[layer][y*width+x]; } }
    bool GetCollision(int x, int y, int layer) { return (matrix[layer][y*width+x] == '#'); }

    int Neighbors(int x, int y, int layer, char target)
    {
        int n=0, n1=target, n2=target, n4=target, n8=target;

        if (y != 0 && y < height-1) { n1 = matrix[layer][(y-1)*width+x]; }
        if (y != height-1 && y > 0) { n8 = matrix[layer][(y+1)*width+x]; }
        if (x != 0 && x < width-1)  { n2 = matrix[layer][y*width+(x-1)]; }
        if (x != width-1 && x > 0)  { n4 = matrix[layer][y*width+(x+1)]; }

        if (target != ' ')
        {
            if (n8 == target) { n += 8; }
            if (n4 == target) { n += 4; }
            if (n2 == target) { n += 2; }
            if (n1 == target) { n += 1; }
        }
        return n;
    }

    // File I/O
    
    void SaveTally()
    {
        std::ofstream data_file("Data/maps/room_tally.data");
        if (data_file.is_open())
        {
            std::cout << "opened" << std::endl;
            data_file << room_tally["0001"] << std::endl;
            data_file << room_tally["0010"] << std::endl;
            data_file << room_tally["0011"] << std::endl;
            data_file << room_tally["0100"] << std::endl;
            data_file << room_tally["0101"] << std::endl;
            data_file << room_tally["0110"] << std::endl;
            data_file << room_tally["0111"] << std::endl;
            data_file << room_tally["1000"] << std::endl;
            data_file << room_tally["1001"] << std::endl;
            data_file << room_tally["1010"] << std::endl;
            data_file << room_tally["1011"] << std::endl;
            data_file << room_tally["1100"] << std::endl;
            data_file << room_tally["1101"] << std::endl;
            data_file << room_tally["1110"] << std::endl;
            data_file << room_tally["1111"] << std::endl;
            data_file.close();
        }
    }

    void LoadTally()
    {
        std::string line;
        std::ifstream data_file("Data/maps/room_tally.data");

        if (data_file.is_open())
        {
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["0001"] = std::stoi(line);
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["0010"] = std::stoi(line);
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["0011"] = std::stoi(line);
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["0100"] = std::stoi(line);
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["0101"] = std::stoi(line);
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["0110"] = std::stoi(line);
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["0111"] = std::stoi(line);
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["1000"] = std::stoi(line);
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["1001"] = std::stoi(line);
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["1010"] = std::stoi(line);
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["1011"] = std::stoi(line);
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["1100"] = std::stoi(line);
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["1101"] = std::stoi(line);
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["1110"] = std::stoi(line);
            getline(data_file, line); line.erase(std::remove(line.begin(), line.end(), '\n'), line.end()); room_tally["1111"] = std::stoi(line);
            data_file.close();
        }
    }

    void SaveData(std::string _dir)
    {
        bool success = false;
        std::string file_path = "Data/maps/"+_dir+"-"+std::to_string(room_tally[_dir])+".map";
        std::ofstream data_file(file_path);
        std::cout << "Opening: " << file_path << std::endl;        
        if (data_file.is_open())
        {
            for (int l = 0; l < layers; l++)
            {
                for (int i = 0; i < matrix[l].size(); i++)
                {
                    data_file << matrix[l][i];
                    if (i % width == width-1) { data_file << std::endl; }
                }
                data_file << '>' << std::endl;
            }
            data_file.close();
            std::cout << "Closing: " << file_path << std::endl;

            success = true;
        } else std::cout << "Failed to create/open: " << file_path << std::endl;
        
        if (success) room_tally[_dir]++;
    }

    void LoadData(std::string _dir)
    {
        std::string line;
        std::ifstream data_file("Data/maps/" + _dir + ".map");
        if (data_file.is_open())
        {
            int layer = 0, y = 0;
            while (getline(data_file, line))
            {
                if (line.length() > 0)
                {
                    if (line.substr(0, 1) != ">")
                    { for (int x = 0; x < line.length(); x++) { matrix[layer][y*width+x] = line.at(x); } y++; }
                    else { layer++; y = 0; }
                }
            }
            data_file.close();
        }
        else 
        {
            for (int i = 0; i < layers; i++) ClearLayer(i);
        }
    }
};
