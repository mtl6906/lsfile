#include "ls/file/File.h"
#include "ls/Exception.h"
#include "ls/file/Writer.h"
#include "ls/file/Reader.h"
#include "unistd.h"
#include "fcntl.h"

using namespace std;

namespace ls
{
    namespace file
    {
        File::File(const string &filename, int flag) : fd(-1), filename(filename), statbuf(nullptr), flag(flag)
        {

        }

    	File::~File()
        {
            if(fd > 0)
    		      close(fd);
	}

        int File::size()
        {
        	if(statbuf != nullptr)
			return statbuf -> st_size;
		statbuf.reset(new struct stat());
		if(lstat(filename.c_str(), statbuf.get()) < 0)
		{
            		statbuf.reset(nullptr);
                	return Exception::LS_ESTAT;
		}
            	return statbuf -> st_size;
        }

	int openfile(const string &filename, int flag)
        {
		int fd = ::open(filename.c_str(), flag);
		if(fd < 0)
			return Exception::LS_EOPEN;
		return fd;
	}

        io::Writer *File::getWriter()
        {
        	if(writer)
			return writer.get();
		if(fd < 0)
			fd = openfile(filename, O_WRONLY | flag);
           	writer.reset(new Writer(fd));
		return writer.get();
        }

        io::Reader *File::getReader()
        {
            if(reader)
		return reader.get();
	    if(fd < 0)
		fd = openfile(filename, O_RDONLY | flag);
            reader.reset(new Reader(fd));
	    return reader.get();
        }
    }
}
