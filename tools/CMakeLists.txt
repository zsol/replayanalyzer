ADD_EXECUTABLE( unpack unpack.cpp )
TARGET_LINK_LIBRARIES( unpack mpq )

ADD_EXECUTABLE( playerinfo playerinfo.cpp )
TARGET_LINK_LIBRARIES( playerinfo ReplayAnalyzer)

ADD_EXECUTABLE( detailsparser detailsparser.cpp )
TARGET_LINK_LIBRARIES( detailsparser ReplayAnalyzer )

#ADD_EXECUTABLE( test test.cpp )
#TARGET_LINK_LIBRARIES( test ReplayAnalyzer )