#ifndef LS_FILE_READER_H
#define LS_FILE_READER_H

#include "ls/io/Reader.h"

namespace ls
{
        namespace file
        {
            class Reader : public io::Reader
            {
                public:
                    Reader(int fd);
                    int read(void *data, int len) override;
                    int tryRead(void *data, int len) override;
                protected:
                    int fd;
            };
        }
}

#endif
