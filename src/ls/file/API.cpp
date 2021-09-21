#include "ls/file/API.h"
#include "ls/cstring/API.h"
#include "ls/Exception.h"
#include "unistd.h"
#include "fcntl.h"

using namespace std;

namespace ls
{
    namespace file
    {
        API api;

        void API::create(const string &filename, int mode)
        {
            int fd = creat(filename.c_str(), mode);
            if(fd < 0)
                throw Exception(Exception::LS_ECREAT);
            close(fd);
        }

        void API::remove(const string &filename)
        {
            if(unlink(filename.c_str()) < 0)
                throw Exception(Exception::LS_EUNLINK);
        }

        File *API::get(const string &filename)
        {
            return new File(filename);
        }

        File *API::get(const string &dirname, const string &filename)
        {
            auto pathname = cstring::api.merge({dirname, "/", filename});
            return new File(pathname);
        }

        bool API::exist(const string &filename)
        {
            return access(filename.c_str(), F_OK) == 0;
        }
    }
}
