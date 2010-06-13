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

#include <mpq.h>
#include <player.h>
using namespace boost::spirit::qi;
using namespace boost::spirit;
using namespace boost::phoenix;
namespace ios = boost::iostreams;


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "detailsparser <replay.details>" << std::endl;
        return 1;
    }

    sc2replay::MPQArchive mpq;
    mpq.load(argv[1]);
    sc2replay::MPQFile* f = mpq.getFile("replay.details");

    sc2replay::MPQFile::array_stream* s = f->getFileStream();

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
    
    const unsigned char* begin = f->getFileContent();
    const unsigned char* end = begin + f->getFileSize() / sizeof(unsigned char*);

    sc2replay::Player p;

    parse(begin, end, 
          omit[repeat(0x3f)[byte_]] >> player,
          p);
    
    std::cout << p.getFullName() << std::endl;
}


// Local Variables:
// compile-command: "cd ../build/; make detailsparser"
// End:
