#pragma once
#ifndef UTIL_H_
#define UTIL_H_

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <iostream>
#include <cstring>

namespace util
{
    inline unsigned int GetSeed(std::string seedString)
    {
        unsigned int value = 0;

        if (seedString.empty())
        {
            value = static_cast<int>(time(0));
        }
        else
        {
            for (size_t i = 0; i < seedString.length(); i++)
                value = (value + static_cast<int>(seedString[i])) % INT32_MAX;
        }

        return value;
    }

    inline unsigned int GetStringWidth(std::string str)
    {
        unsigned int size = 0;
        unsigned int cSize = 0;

        for (size_t i = 0; i < str.size(); i++)
        {
            cSize++;

            if (str.at(i) == '\n')
            {
                cSize = 0;
            }

            if (cSize > size) size = cSize;
        }

        return size;
    }

    inline unsigned int GetStringHeight(std::string str)
    {
        unsigned int size = 0;

        for (size_t i = 0; i < str.size(); i++)
        {
            if (str.at(i) == '\n')
            {
                size++;
            }
        }

        return size;
    }

    inline std::string GetCWD(const char* _content = "")
    {
        char buff[FILENAME_MAX];
        GetCurrentDir(buff, FILENAME_MAX);
        std::string _dir(buff);

        if (_content != nullptr && _content[0] != '\0')
        {
            if (_content[0] != '/') _dir += '/';
            _dir += _content;
        }

        return _dir.c_str();
    }
}

#endif
