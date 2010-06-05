#include <iostream>
#include <string>
#include <fstream>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

uint8_t
read(std::istream& s)
{
    uint8_t ret = s.peek();
    s.seekg(1, std::ios::cur);
    return ret;
}

uint16_t
read2(std::istream& s)
{
    uint16_t ret;
    ret = read(s) << 8;
    ret += read(s);
    return ret;
}

std::string
readStr(std::istream& s)
{
    uint8_t l;
    int len = ((int)read(s))/2;
    char* buf = new char[len+1];
    s.read(buf, len);
    buf[len] = 0;

    return buf;
}

typedef std::pair<uint16_t, int> KV;

KV
readKV(std::istream& s)
{
    uint16_t key = read2(s);
    uint8_t tmp = read(s);
    int val(0);
    val = tmp & 0x7f;
    if ((tmp & 0x80) > 0)
    {
        val <<= 8;
        val += (int)read(s);
    }
    //std::cout << std::hex << key << " => " << val << std::endl;
    return std::make_pair(key, val);
}
  
bool
readPlayer(std::istream& s)
{
    // player header is 05 12 00 02
    // check for that
    uint8_t hdr[] = { 0x5, 0x12, 0x0, 0x2 };
    for (int idx = 0; idx < sizeof(hdr)/sizeof(uint8_t); ++idx)
    {
        if (read(s) != hdr[idx])
        {
            s.seekg(-1 - idx, std::ios::cur); //reset file to state before call
            return false;
        }
    }

    std::cout << readStr(s) << std::endl; // shortName

    s.seekg(3, std::ios::cur); // 02 05 08

    readKV(s); // key = 00 09

    s.seekg(6, std::ios::cur); // unknown2

    readKV(s); // key = 04 09

    s.seekg(2, std::ios::cur); // 06 02

    std::cout << readStr(s) << std::endl; // fullName

    s.seekg(2, std::ios::cur); // 04 02

    std::cout << readStr(s) << std::endl; // race

    s.seekg(3, std::ios::cur); // 06 05 08

    for (int i=0; i < 9; ++i)
        readKV(s);

    return true;
}


int main(int argc, char** argv)
{
  if (argc != 2)
  {
      std::cerr << "playerinfo <details>" << std::endl;
      return 1;
  }

  std::ifstream file(argv[1], std::ios::in | std::ios::binary);
  file.seekg(0x3f);

  while(readPlayer(file))
  {
      std::cout <<std::hex<< "============== " << file.tellg() << " =====================" << std::endl;
  }

  file.seekg(2, std::ios::cur);

  std::cout << readStr(file) << std::endl; // mapName

  file.seekg(2, std::ios::cur); // 04 02

  std::cout << readStr(file) << std::endl; //what's this?

  file.seekg(5, std::ios::cur); // 06 05 02 00 02

  std::cout << readStr(file) << std::endl; //minimap
  file.close();
}
