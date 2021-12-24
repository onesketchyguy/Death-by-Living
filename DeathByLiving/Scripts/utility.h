#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#pragma once
#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <cstring>

namespace util
{

    unsigned int GetSeed(std::string seedString)
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

        return value;
    }

    unsigned int GetStringWidth(std::string str)
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

    unsigned int GetStringHeight(std::string str)
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

    std::string GetCWD()
        {
            char buff[FILENAME_MAX];
            GetCurrentDir(buff, FILENAME_MAX);
            std::string _dir(buff);
            return _dir;
        }

}

#endif
