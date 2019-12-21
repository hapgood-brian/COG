//------------------------------------------------------------------------------
//       Copyright 2014-2019 Creepy Doll Games LLC. All rights reserved.
//
//                  The best method for accelerating a computer
//                     is the one that boosts it by 9.8 m/s2.
//------------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY EXPRESS
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
// NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//------------------------------------------------------------------------------

#pragma once

/** \addtogroup engine
  * @{
  *   \addtogroup base
  *   @{
  *     \addtogroup compiler
  *     @{
  */

//================================================|=============================
//Detect platform:{                               |

  #ifdef _MSC_VER
    #ifdef __cplusplus
      extern"C"{
    #endif
      __declspec(dllimport)void __stdcall DebugBreak();
    #ifdef __cplusplus
      }
    #endif
    #define __PRETTY_FUNCTION__ __FUNCTION__
    #include<memory.h>
    #include<stdarg.h>
    #include<stdio.h>
    #ifdef min
    #undef min
    #endif
    #ifdef max
    #undef max
    #endif
    //Disabled warnings:{
      //possible loss of data
      #pragma warning(disable:4244)
      //nonstandard extension used : nameless struct/union
      #pragma warning(disable:4201)
      //unreferenced inline function has been removed
      #pragma warning(disable:4514)
      //no function prototype given: converting '()' to '()'
      #pragma warning(disable:4255)
      //'this' : used in base member initializer list
      #pragma warning(disable:4355)
      //Unsafe function or variable(_CRT_SECURE_NO_WARNINGS)
      #pragma warning(disable:4996)
      //C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
      #pragma warning(disable:4290)
      //unknown pragma
      #pragma warning(disable:4068)
    //}:
    //Intrinsic SSE headers:{                     |

      #include<intrin.h>

    //}:                                          |
    //Restricted pointers:{                       |

      #ifndef __llvm__
        #define RESTRICT __restrict
      #endif

    //}:                                          |
    //Platform types:{                            |
      //e_declptrs:{                              |

        /** \brief Engine ptr type definition macro.
          *
          * The e_declptrs macro is used to define pointer types with the right
          * naming convention.
          *
          * \param x The one letter name of the type.
          * \param y The base type.
          */

        #define e_declptrs( x, y )                                              \
          typedef const y* c##x##p;                                             \
          typedef       y*    x##p                                              \

        namespace EON{
          e_declptrs( l, long );
          e_declptrs( c, char );
          e_declptrs( i, int  );
          e_declptrs( v, void );
        }

      //}:                                        |
      //e_declints:{                              |

        /** \brief Engine integer type definition macro.
          *
          * The e_declints macro is used to define pointer types with the right
          * naming convention.
          *
          * \param x The name of the type.
          * \param y The base type.
          */

        #define e_declints( bits )                                              \
          typedef   signed __int##bits s##bits;                                 \
          typedef unsigned __int##bits u##bits                                  \

        namespace EON{
          e_declints( 64 );
          e_declints( 32 );
          e_declints( 16 );
          e_declints(  8 );
        }

      //}:                                        |
      //__thread:{                                |

        #define __thread                                                        \
            __declspec( thread )                                                \

      //}:                                        |
    //}:                                          |
    //Detect C++11:{                              |

      #if __cplusplus <= 199711L
        #define __compiling_cpp11__ 1
      #endif

    //}:                                          |
    //Compiler:{                                  |
      //Graphics:{                                |

        #define __compiling_directx__ 0
        #define __compiling_vulkan__ 0
        #define __compiling_opengl__ 1
        #define __compiling_glsl__ \
          (!__compiling_directx__)&&(__compiling_vulkan__||__compiling_opengl__)

      //}:                                        |
      //Vendor:{                                  |

        #define __compiling_microsoft__ 1
        #define __compiling_pc__ 1

      //}:                                        |
      //Packed:{                                  |

        #ifndef e_packed
        #define e_packed(T,...)                                                 \
          __pragma( pack( push, 1 ))struct T{__VA_ARGS__;}                      \
          __pragma( pack( pop ))
        #endif

      //}:                                        |
    //}:                                          |
    //Export:{                                    |

      #if e_compiling( enabling_dll )
        #if e_compiling( engine_dll )
          #define E_PUBLISH __declspec( dllexport )
          #define E_REFLECT __declspec( dllexport )
          #define E_EXPORT  __declspec( dllexport )
          #define E_IMPORT  __declspec( dllimport )
        #else
          #define E_PUBLISH __declspec( dllimport )
          #define E_REFLECT
          #define E_EXPORT
          #define E_IMPORT
        #endif
      #else
        #define E_PUBLISH
        #define E_REFLECT
        #define E_EXPORT
        #define E_IMPORT
      #endif

    //}:                                          |
  #endif

//}:                                              |
//================================================|=============================

/**     @}
  *   @}
  * @}
  */
