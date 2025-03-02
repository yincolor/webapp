#ifndef ___WEBAPP_H___
#define ___WEBAPP_H___

#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    // windows 
#elif __APPLE__
    // APPLE

#elif __linux__
    // linux
    #include"core/linux/webapp.h"
#else 
    #error "unkown system"
#endif

#endif