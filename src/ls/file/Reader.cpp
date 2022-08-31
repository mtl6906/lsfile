#include "ls/file/Reader.h"
#include "ls/Exception.h"
#include "unistd.h"

namespace ls
{
    namespace file
    {
        Reader::Reader(int fd) : fd(fd)
        {

        }

        int Reader::read(void *data, int len)
        {
            int n = ::read(fd, data, len);
            if(n == 0)
                return Exception::LS_EEOF;
            if(n < 0)
                return Exception::LS_EREAD;
            return n;
        }

        int Reader::tryRead(void *data, int len)
        {
            return read(data, len);
        }
    }
}
