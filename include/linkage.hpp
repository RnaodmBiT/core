#pragma once

#if defined(TK_SHARED) && defined(_MSC_VER)
#   if defined(TK_BUILD)
#       define TK_API   __declspec(dllexport)
#   else
#       define TK_API   __declspec(dllimport)
#   endif
#else
#   define TK_API
#endif