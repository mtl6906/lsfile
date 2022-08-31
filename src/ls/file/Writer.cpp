#include "ls/file/Writer.h"
#include "ls/Exception.h"
#include "unistd.h"

namespace ls
{
    namespace file
    {
        Writer::Writer(int fd) : fd(fd)
        {

        }

        int Writer::write(void *data, int len)
        {
            int n = ::write(fd, data, len);
            if(n < 0)
                return Exception::LS_EWRITE;
            return n;
        }

        int Writer::tryWrite(void *data, int len)
        {
            return write(data, len);
        }
    }
}
