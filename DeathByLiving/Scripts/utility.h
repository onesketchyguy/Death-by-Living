namespace util
{

    void ApplySeed(std::string seedString)
    {
        unsigned int value = 0;

        if (seedString.empty())
        {
            value = time(0);
        }
        else
        {
            for (size_t i = 0; i < seedString.length(); i++)
                value = (value + static_cast<int>(seedString[i])) % INT32_MAX;
        }

        seed = value;

        srand(value);
    }

}
