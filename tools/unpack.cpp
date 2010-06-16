#include <iterator>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <libmpq/mpq.h>

std::pair<bool, std::vector<char> >
getFile(mpq_archive_s* archive, const std::string& filename_)
{
    unsigned int file_number;
    if (libmpq__file_number(archive, filename_.c_str(), &file_number) != 0)
    {
        return std::make_pair(false, std::vector<char>());
    }

    off_t file_size;
    libmpq__file_unpacked_size(archive, file_number, &file_size);

    uint8_t* buf = new uint8_t[file_size];
    libmpq__file_read(archive, file_number, buf, file_size, NULL);
    std::vector<char> ret;
    std::copy(buf, buf+file_size, std::back_inserter(ret));
    return std::make_pair(true, ret);
}


int main( int argc, char** argv )
{
#ifndef NEW_LIBMPQ
    libmpq__init();
#endif
    mpq_archive_s *a;
    if (libmpq__archive_open(&a, argv[1], -1) != 0)
    {
        std::cerr << "Error opening " << argv[1] << std::endl;
        return 1;
    }

    std::pair<bool, std::vector<char> > pair = getFile(a, "(listfile)");

    if (not pair.first)
        return 1;

    std::string tmp;
    std::copy(pair.second.begin(), pair.second.end()-2, std::back_inserter(tmp)); // chop off \r\n
    std::istringstream ss(tmp);
    while (not ss.eof())
    {
        std::string filename;
        ss >> filename;

        std::pair<bool, std::vector<char> > file = getFile(a, filename);
        
        if (not file.first)
        {
            std::cerr << "Error occured while processing " << filename << std::endl;
            continue;
        }

        std::ofstream fs(filename.c_str());
        std::copy(file.second.begin(), file.second.end(), std::ostream_iterator<char>(fs));
    }

    libmpq__archive_close(a);
    
    return 0;
}
