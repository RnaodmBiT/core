#pragma once

#if defined(TK_SHARED) && defined(_MSC_VER)
#   if defined(TK_BUILD_CORE)
#       define TK_CORE              __declspec(dllexport)
#   else
#       define TK_CORE              __declspec(dllimport)
#   endif

#   if defined(TK_BUILD_GRAPHICS)
#       define TK_GRAPHICS          __declspec(dllexport)
#   else
#       define TK_GRAPHICS          __declspec(dllimport)
#   endif

#   if defined(TK_BUILD_LAYOUT)
#       define TK_LAYOUT            __declspec(dllexport)
#   else
#       define TK_LAYOUT            __declspec(dllimport)
#   endif
#else
#   define TK_CORE
#   define TK_GRAPHICS
#   define TK_LAYOUT
#endif