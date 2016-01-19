cmake_minimum_required(VERSION 2.6)
project(uMario)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${uMario_SOURCE_DIR}/cmake")
set(BIN_DIR ${uMario_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -Wall  -std=gnu++11 ")
 if (PSP) 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}    -G0 -D__PSP__ -fno-exceptions -fno-rtti -D_PSP_FW_VERSION=150 ") #PSP Stuff
endif()
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_Mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})

file(COPY uNext/files DESTINATION .)

include_directories(uNext)

file(GLOB_RECURSE uMario_SOURCES "uNext/*.cpp")
add_executable (uMario ${uMario_SOURCES})

if (PSPSDK_PATH)
#target_include_directories(RPGEngine PUBLIC ${PSPSDK_PATH}/include)
#list(APPEND CMAKE_CXX_FLAGS "-I${PSPSDK_PATH}/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${PSPSDK_PATH}/include -L${PSPSDK_PATH}/lib ")
set(CMAKE_CXX_COMPILER "${CMAKE_C_COMPILER}")
target_link_libraries(uMario -lSDL2_image -lSDL2_mixer  -lSDL2  -lvorbisfile -lvorbis -logg  -lpspgu -lpng -lz -ljpeg  -lm -lGL -lpspvfpu -lpsprtc -lpspaudio -lpsphprm -lpspvram -lstdc++ -lpspdebug -lpspdisplay -lpspge -lpspctrl -lpspsdk -lc -lpspnet -lpspnet_inet -lpspnet_apctl -lpspnet_resolver -lpsputility -lpspuser -lpspkernel )
#target_link_libraries(RPGEngine ${PSPSDK_PATH}/lib)
message(STATUS "PSPSDK found in ${PSPSDK_PATH}")
add_psp_executable(uMario)
else ()
target_link_libraries(uMario ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_MIXER_LIBRARY} )
endif()

install(TARGETS uMario RUNTIME DESTINATION ${BIN_DIR})
