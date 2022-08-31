#ifndef LS_FILE_FILE_H
#define LS_FILE_FILE_H

#include "sys/stat.h"
#include "ls/Buffer.h"
#include "ls/io/Writer.h"
#include "ls/io/Reader.h"
#include "memory"

namespace ls
{
    namespace file
    {
        class File
	{
	    public:
		File(const std::string &filename, int flag = 0);
	        ~File();
	        int size();
	        bool exist();
	        io::Writer *getWriter();
	        io::Reader *getReader();
          protected:
                int fd;
		int flag;
                std::string filename;
                std::unique_ptr<struct stat> statbuf;
                std::unique_ptr<io::Writer> writer;
                std::unique_ptr<io::Reader> reader;
        };
    }
}

#endif
