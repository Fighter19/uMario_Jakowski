#pragma once

#ifndef HEADER_H
#define HEADER_H

#ifdef PSP
#include <pspkernel.h>
#include <pspdebug.h>
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <stdio.h>

#include <sstream>

#define PRINT(x) sceIoWrite(1, x, strlen(x))

namespace std
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


#ifdef PSP
	inline int vprintf(const char *format, va_list args)
	{
	  static char buf[255];
		int ret;

		ret = vsnprintf(buf, 255, format, args);

		sceIoWrite(1, buf, ret);
		return ret;
	}

	inline int printf(const char *format, ...)
{
	va_list args;
	int ret;

	va_start(args, format);
	ret = vprintf(format, args);
	va_end(args);

	return ret;
}

#endif

#endif
