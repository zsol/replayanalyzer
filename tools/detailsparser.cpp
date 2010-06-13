#include <iostream>
#include <fstream>
#include <string>

#include <boost/program_options.hpp>

#include <mpq.h>
#include <player.h>
#include <info.h>

namespace ios = boost::iostreams;
namespace po = boost::program_options;


int main(int argc, char** argv)
{

    po::options_description desc("Allowed options");
    po::positional_options_description posdesc;
    po::variables_map vm;

    desc.add_options()
        ("help", "display this help message")
        ("noextract", "input file is a replay.details file, not an MPQ archive")
        ("input-file", po::value<std::string>(), "input file")
        ;
    posdesc.add("input-file", -1);

    po::store(po::command_line_parser(argc, argv).
              options(desc).positional(posdesc).run(), vm);
    po::notify(vm);

    if (vm.count("input-file") != 1)
    {
        std::cerr << "You have to specify an input file!" << std::endl;
        std::cout << desc << std::endl;
        return 1;
    }

    const unsigned char* begin, *end;

    if (vm.count("noextract"))
    {
        const int BUFSIZE = 8*1024;
        std::ifstream file(vm["input-file"].as<std::string>().c_str());
        char* buf = new char[BUFSIZE]; // Yes, this will leak, no biggie.
        file.read(buf, BUFSIZE);

        if (file)
        {
            std::cerr << "Replay.details file too large, try to use the original replay file or contact the author!" << std::endl;
            return 1;
        }

        begin = reinterpret_cast<unsigned char*>(buf);
        end = begin + file.gcount();
        file.close();
    }
    else
    {
        sc2replay::MPQArchive mpq;
        mpq.load(vm["input-file"].as<std::string>().c_str());
        sc2replay::MPQFile* f = mpq.getFile("replay.details");
        
        begin = f->getFileContent();
        end = begin + f->getFileSize() / sizeof(unsigned char*);
    }

    
    sc2replay::Info i;
    i.load(begin, end);

    for (std::vector<sc2replay::Player>::const_iterator it = i.getPlayers().begin();
         it != i.getPlayers().end(); ++it)
    {
        std::cout << "shortName: " << it->getShortName() << "\t Race: " << 
            it->getRace() << "\t fullName: " << it->getFullName() << std::endl;
    }

}


// Local Variables:
// compile-command: "cd ../build/; make detailsparser"
// End:
