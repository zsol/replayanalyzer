#include <iostream>
#include <fstream>
#include <string>


#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream_buffer.hpp>

#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_parse_attr.hpp>
#include <boost/spirit/include/qi_rule.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>

#include <boost/program_options.hpp>

#include <mpq.h>
#include <player.h>
using namespace boost::spirit::qi;
using namespace boost::spirit;
using namespace boost::phoenix;
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
        
        sc2replay::MPQFile::array_stream* s = f->getFileStream();
        
        begin = f->getFileContent();
        end = begin + f->getFileSize() / sizeof(unsigned char*);
    }


    rule<const unsigned char*, locals<int>, std::string() > str;
    rule<const unsigned char*, int()> v;
    rule<const unsigned char*, std::pair<sc2replay::uint16_t, int>()> kv;
    rule<const unsigned char*, sc2replay::Player()> player;

    str = byte_[_a = _1] >> repeat(_a/2)[char_[_val += _1]];

    v = (&byte_[if_(0==(_1 & 0x80))[_pass=false]] >> big_word[_val = _1 & 0x7fff]) | byte_;

    kv %= big_word >> v;

    player %= omit[byte_(0x5) >> byte_(0x12) >> byte_(0x0) >> byte_(0x2)] >>
        str >> omit[byte_(0x2) >> byte_(0x5) >> byte_(0x8)] >> omit[kv] >> 
        omit[repeat(6)[byte_]] >> omit[kv] >> omit[byte_(0x6) >> byte_(0x2)] >>
        str >> omit[byte_(0x4) >> byte_(0x2)] >> 
        str >> omit[byte_(0x6) >> byte_(0x5) >> byte_(0x8)] >>
        omit[repeat(9)[kv]];


    sc2replay::Player p;

    parse(begin, end, 
          omit[repeat(0x3f)[byte_]] >> player,
          p);
    
    std::cout << p.getFullName() << std::endl;
}


// Local Variables:
// compile-command: "cd ../build/; make detailsparser"
// End:
