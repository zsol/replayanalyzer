ADD_EXECUTABLE( unpack unpack.cpp )
TARGET_LINK_LIBRARIES( unpack mpq )

ADD_EXECUTABLE( playerinfo playerinfo.cpp )
TARGET_LINK_LIBRARIES( playerinfo ReplayAnalyzer)
