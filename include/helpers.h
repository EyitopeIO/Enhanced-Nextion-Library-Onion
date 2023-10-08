#ifndef HELPERS_H
#define HELPERS_H

#ifdef FLAVOUR_DEBUG
#define DEBUG_PRINT(x) std::cerr << x << std::endl
#else
#define DEBUG_PRINT(x)
#endif

#endif