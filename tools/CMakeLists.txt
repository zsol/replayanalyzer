ADD_EXECUTABLE( unpack unpack.cpp )
TARGET_LINK_LIBRARIES( unpack mpq )

ADD_EXECUTABLE( detailsparser detailsparser.cpp )
TARGET_LINK_LIBRARIES( detailsparser ReplayAnalyzer ${Boost_LIBRARIES} )

#ADD_EXECUTABLE( test test.cpp )
#TARGET_LINK_LIBRARIES( test ReplayAnalyzer )