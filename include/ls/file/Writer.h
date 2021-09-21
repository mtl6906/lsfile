#ifndef LS_FILE_WRITER_H
#define LS_FILE_WRITER_H

#include "ls/io/Writer.h"

namespace ls
{
    namespace file
    {
        class Writer : public io::Writer
        {
            public:
                Writer(int fd);
                int write(void *data, int len) override;
                int tryWrite(void *data, int len) override;
            protected:
                int fd;
        };
    }
}

#endif
