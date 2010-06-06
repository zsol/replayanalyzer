#include <iostream>
#include <string>
#include <fstream>

#include <info.h>

int main(int argc, char** argv)
{
  if (argc != 2)
  {
      std::cerr << "playerinfo <details>" << std::endl;
      return 1;
  }

//  stream<file_source> file(argv[1], std::ios::in | std::ios::binary);
  std::ifstream file(argv[1], std::ios::in | std::ios::binary);

  sc2replay::Info i;

  i.load(file);

  std::cout << "Map: " << i.getMapName() << std::endl;

  int cnt(1);

  for (sc2replay::Info::Players::const_iterator it = i.getPlayers().begin();
       it != i.getPlayers().end(); ++it)
  {
      std::cout << "Player " << cnt++ << ": " 
                << (*it).getShortName() << " ( " 
                << (*it).getFullName() << " ) - " 
                << (*it).getRace() << std::endl;
  }

  file.close();
}
