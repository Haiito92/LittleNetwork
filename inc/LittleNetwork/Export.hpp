#pragma once

#ifdef LN_COMPILE
#define LN_API __declspec(dllexport)
#else
#define LN_API __declspec(dllimport)
#endif
