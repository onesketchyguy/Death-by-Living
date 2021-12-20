class World
{

public:

    int width;
    int height;

    std::vector<std::string> matrix;

    World(int w, int h) { width = w; height = h; InitMatrix(); }

    void EmptyMatrix() { matrix.clear(); }
    void ClearMatrix() { matrix.clear(); InitMatrix(); }
    void InitMatrix() { for (int y = 0; y < height; y++) { for (int x = 0; x < width; x++) { matrix.push_back(""); } } }
    
    void GenerateMatrix()
    {
        std::string choices[4] = {"item", "chest", "battle", "puzzle"};
        std::string n1 = "";
        std::string n2 = "";
        std::string n4 = "";
        std::string n8 = "";
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (y != 0 && y < height-1) { n1 = matrix[(y-1)*width+x]; }
                if (y != height-1 && y > 0) { n8 = matrix[(y+1)*width+x]; }
                if (x != 0 && x < width-1)  { n2 = matrix[y*width+(x-1)]; }
                if (x != width-1 && x > 0)  { n4 = matrix[y*width+(x+1)]; }

                std::string value = "";
                std::string choice = choices[rand()%4];
                std::string room = value+"-"+choice;
                matrix[y*width+x] = room;
            }
        }
    }
}
