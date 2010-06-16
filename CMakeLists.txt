############################## Minimum CMake version to run ###################
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

############################## Checks #########################################
IF ( NOT CMAKE_BUILD_TYPE )
  SET( CMAKE_BUILD_TYPE Debug CACHE STRING "Available build types: Debug | Release" FORCE )
ENDIF ( NOT CMAKE_BUILD_TYPE )

############################## Project name ###################################
PROJECT( ReplayAnalyzer )

SET( ReplayAnalyzer_MAJOR_VERSION 0 )
SET( ReplayAnalyzer_MINOR_VERSION 0 )
SET( ReplayAnalyzer_PATCH_LEVEL   0 )

############################## Modules configuration ##########################
OPTION( BUILD_DOC    "Build the doxygen documentation"         ON  )
OPTION( BUILD_STATIC "Build as a static library"               ON  )
OPTION( BUILD_TOOLS  "Build the tools"                         ON  )
OPTION( NEW_LIBMPQ   "Use new (>0.4.2) version of libmpq"      OFF )

MESSAGE( STATUS "Building documentation:   " ${BUILD_DOC}    )
MESSAGE( STATUS "Building static:          " ${BUILD_STATIC} )
MESSAGE( STATUS "Building tools:           " ${BUILD_TOOLS}  )

############################## Sources ########################################
FILE( GLOB_RECURSE Sources        src/*.cpp )
FILE( GLOB_RECURSE Headers        src/*.hpp src/*.h )

# Group files in virtual folders under Visual Studio
SOURCE_GROUP( "Sources"           FILES ${Sources} )
SOURCE_GROUP( "Headers"           FILES ${Headers} )

############################## External libraries #############################
# Not used yet
INCLUDE( FindBoost )
SET( Boost_USE_MULTITHREADED ON )
SET( Boost_USE_STATIC_LIBS   ON )
FIND_PACKAGE( Boost REQUIRED COMPONENTS iostreams program_options)

FIND_LIBRARY( MPQLib NAMES mpq )


############################## Includes #######################################
INCLUDE_DIRECTORIES( ./src ) # Headers

############################## Project generation #############################
IF ( BUILD_STATIC )
  ADD_LIBRARY( ReplayAnalyzer STATIC ${Sources} ${PublicHeaders} ${PrivateHeaders} )
ELSE ( BUILD_STATIC )
  ADD_LIBRARY( ReplayAnalyzer SHARED ${Sources} ${PublicHeaders} ${PrivateHeaders} )
ENDIF ( BUILD_STATIC )

TARGET_LINK_LIBRARIES( ReplayAnalyzer ${Boost_LIBRARIES} ${MPQLib} )


################################### Options ###################################
IF ( BUILD_STATIC )
  ADD_DEFINITIONS( -DBUILD_STATIC )
ENDIF( BUILD_STATIC )

IF ( BUILD_DOC )
  #TODO build documentation using Doxygen
ENDIF( BUILD_DOC )

IF ( BUILD_TOOLS )
  ADD_SUBDIRECTORY( tools )
#  FIND_PACKAGE( Boost REQUIRED COMPONENTS program_options )
ENDIF( BUILD_TOOLS )

IF ( NEW_LIBMPQ )
  ADD_DEFINITIONS( -DNEW_LIBMPQ )
ENDIF ( NEW_LIBMPQ )

############################## Target Properties ##############################
SET_TARGET_PROPERTIES( ReplayAnalyzer PROPERTIES LINKER_LANGUAGE CXX ) # Language forced to C++

SET_TARGET_PROPERTIES( ReplayAnalyzer PROPERTIES DEBUG_POSTFIX "d" ) # Debug mode: a trailing "d"

SET_TARGET_PROPERTIES( ReplayAnalyzer PROPERTIES RELEASE_POSTFIX "" ) # Release mode: no postfix

SET_TARGET_PROPERTIES( ReplayAnalyzer PROPERTIES PREFIX  ""  ) # Remove the "lib" prefix

SET_TARGET_PROPERTIES( ReplayAnalyzer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./${CMAKE_BUILD_TYPE} ) # Path for shared libraries
SET_TARGET_PROPERTIES( ReplayAnalyzer PROPERTIES LIBRARY_OUTPUT_DIRECTORY ./${CMAKE_BUILD_TYPE} ) # Path for module libraries
SET_TARGET_PROPERTIES( ReplayAnalyzer PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ./${CMAKE_BUILD_TYPE} ) # Path for import libraries

SET_TARGET_PROPERTIES( ReplayAnalyzer PROPERTIES OUTPUT_NAME "repa" ) # Output name

