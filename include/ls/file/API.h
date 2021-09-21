#ifndef LS_FILE_API_H
#define LS_FILE_API_H

#define NORMAL_MODE (S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR)
#include "ls/file/File.h"

namespace ls
{
    namespace file
    {
        class API
        {
            public:
                void create(const std::string &filename, int mode);
                void remove(const std::string &filename);
                void rename(File *file, const std::string &name);
                File *get(const std::string &filename);
                File *get(const std::string &dirname, const std::string &filename);
                bool exist(const std::string &filename);
        };
        extern API api;
    }
}

#endif
