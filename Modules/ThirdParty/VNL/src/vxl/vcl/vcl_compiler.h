#ifndef vcl_compiler_h_
#define vcl_compiler_h_
//:
// \file
// \brief Uniform macro definition scheme for finding out about the compiler
//
// It's much better to determine the compiler automatically here than to depend
// on command-line flags being set.
//
// Be careful when modifying this file. In general, you need to make
// sure that exactly one of the preprocessor flags is defined. For
// example, if the compiler is GCC 5.3.0, then VCL_GCC should be
// defined, VCL_GCC_5 should be defined, and VCL_GCC_53 should be
// defined. Others, like VCL_GCC_51 *should not* be defined.
//
// Note that this is most commonly implemented using a cascade of if
// statements. Be careful to add your statements to the correct place
// in the cascade list.
//
// Naming scheme:
// If you have a compiler name XYZ, then
//     #define VCL_XYZ
// Each each major release, define a release number
//     #define VCL_XYZ_4
// Avoid using the marketing name for the release number, because it's
// harder to follow. For example, Microsoft Visual C++ .NET 2003 is
// better called Visual C++ 7.
// For each minor version, define the appropriate minor version number
//     #define VCL_XYZ_40
// If necessary, define the patchlevel too:
//     #define VCL_XYZ_401
//
// Make sure that if the minor version is defined, then the release
// number and the compiler name are also defined.
//
// Add the corresponding test to tests/test_platform to make sure.

#if defined(__FreeBSD__)
# define VCL_FREEBSD
# ifndef _GLIBCXX_USE_C99
#  define _GLIBCXX_USE_C99 1
# endif
#endif

#if defined(__GNUC__) && !defined(__ICC) // icc 8.0 defines __GNUC__
# define VCL_GCC
# if (__GNUC__ < 4)
#  error "forget it."
# elif (__GNUC__==4)
#  define VCL_GCC_4
#  if (__GNUC_MINOR__ > 0 )
#   define VCL_GCC_41
#  else
#   define VCL_GCC_40
#  endif
# elif (__GNUC__==5)
#  define VCL_GCC_5
#  if (__GNUC_MINOR__ > 2 )
#   define VCL_GCC_53
#  elif (__GNUC_MINOR__ > 1 )
#   define VCL_GCC_52
#  elif (__GNUC_MINOR__ > 0 )
#   define VCL_GCC_51
#  else
#   define VCL_GCC_50
#  endif
# elif (__GNUC__==6)
#  define VCL_GCC_6
#  if (__GNUC_MINOR__ > 2 )
#   define VCL_GCC_63
#  elif (__GNUC_MINOR__ > 1 )
#   define VCL_GCC_62
#  elif (__GNUC_MINOR__ > 0 )
#   define VCL_GCC_61
#  else
#   define VCL_GCC_60
#  endif
# else
#  error "Dunno about this gcc"
# endif
#endif

#if defined(_WIN32) || defined(WIN32)
# define VCL_WIN32
# if defined(_MSC_VER)
#  define VCL_VC
#  define VCL_VC_DOTNET 1 // VC is at least version >= 7.0

// In future use VCL_VC_13_1 for 13.1, etc.
#  if _MSC_VER >= 1700     // Visual Studio 2011 = Version 11.x
#   define VCL_VC_11
#  elif _MSC_VER >= 1600     // Visual Studio 2010 = Version 10.x
#   define VCL_VC_10
#  elif _MSC_VER >= 1500     // Visual Studio 2008 = Version 9.x
#   define VCL_VC_9
#  else
#   error "Invalid VCL_VC version"
#  endif
# endif
#endif

// win32 or vc++ ?
// awf hack alert:
#ifdef VCL_VC
// Disable warnings about C standard library functions.
# ifndef _CRT_SECURE_NO_DEPRECATE
#  define _CRT_SECURE_NO_DEPRECATE 1
# endif
#endif

#if defined(__CYGWIN__) // Cygwin GCC Compiler
# define VCL_CYGWIN_GCC
#endif

#if defined(__ICC)
# define VCL_ICC
#endif

// include header files generated by configure.
#include <vcl_config_manual.h>
#include <vcl_config_compiler.h>
#include <vcl_config_headers.h>

// -------------------- default template parameters
#if VCL_CAN_DO_COMPLETE_DEFAULT_TYPE_PARAMETER
# define VCL_DFL_TYPE_PARAM_STLDECL(A, a) class A = a
#else
# define VCL_DFL_TYPE_PARAM_STLDECL(A, a) class A
#endif

#if VCL_CAN_DO_TEMPLATE_DEFAULT_TYPE_PARAMETER
# define VCL_DFL_TMPL_PARAM_STLDECL(A, a) class A = a
#else
# define VCL_DFL_TMPL_PARAM_STLDECL(A, a) class A
#endif

#define VCL_DFL_TMPL_ARG(classname) , classname

   //-------------------- template instantiation ------------------------------

// if the compiler doesn't understand "export", we just leave it out.
// gcc understands it, but ignore it noisily.
// icc understands it, but ignore it noisily.
#if !VCL_HAS_EXPORT || defined(VCL_GCC) || defined(VCL_ICC)
# define VCL_TEMPLATE_EXPORT /* ignore */
#else
# define VCL_TEMPLATE_EXPORT export
#endif

#if VCL_NEEDS_INLINE_INSTANTIATION
# define VCL_INSTANTIATE_INLINE(symbol) template symbol
#else
# define VCL_INSTANTIATE_INLINE(symbol) /* */
#endif

//--------------------------------------------------------------------------------

#if VCL_FOR_SCOPE_HACK
# undef for
# define for if (false) { } else for
typedef int saw_VCL_FOR_SCOPE_HACK;
#endif

// fix to instantiate template functions
#define VCL_INSTANTIATE_NONINLINE(fn_decl) template fn_decl

   // -------------------- handy macros ---------------------------------------

//: VCL_COMMA
//
// Handy for passing things with commas in them to CPP macros.  e.g.
// DO_MACRO(pair<A,B>) can be replaced by DO_MACRO(pair<A VCL_COMMA B>).
#define VCL_COMMA ,


//: VCL_VOID_RETURN
//
// VCL_VOID_RETURN is used as a return type where void is expected,
// as in return VCL_VOID_RETURN;
#define VCL_VOID_RETURN /*empty*/

//----------------------------------------------------------------------------
// Macros for safe-bool idiom.
# define VCL_SAFE_BOOL_TRUE (&safe_bool_dummy::dummy)
# define VCL_SAFE_BOOL_DEFINE \
   struct safe_bool_dummy { void dummy() {} }; \
   typedef void (safe_bool_dummy::* safe_bool)()

//----------------------------------------------------------------------------
// Check if the compiler (claims to) support C++11.
#if __cplusplus >= 201103L
# define VXL_CXX11 1
  // In c++11 the override keyword allows you to explicity define that a function
  // is intended to override the base-class version.  This makes the code more
  // managable and fixes a set of common hard-to-find bugs.
# define VXL_OVERRIDE override
  // In functions that should not be implemented, use the C++11 mechanism
  // to ensure that thye are purposely not implemented
# define VXL_DELETE_FUNCTION =delete
  // In c++11 there is an explicit nullptr type that introduces a new keyword to
  // serve as a distinguished null pointer constant: nullptr. It is of type
  // nullptr_t, which is implicitly convertible and comparable to any pointer type
  // or pointer-to-member type. It is not implicitly convertible or comparable to
  // integral types, except for bool.
# define VXL_NULLPTR  nullptr
  // In C++11 the throw-list specification has been deprecated,
  // replaces with the noexcept specifier. Using this function
  // specification adds the run-time check that the method does not
  // throw, if it does throw then std::terminate will be called.
  // Use cautiously.
# define VXL_NOEXCEPT noexcept
# define VXL_HAS_CXX11_STATIC_ASSERT
# define VXL_HAS_CXX11_RVREF
#else
//----------------------------------------------------------------------------
//  C++11 not supported
#include <cstddef>
# define VXL_CXX11 0
# define VXL_OVERRIDE
# define VXL_DELETE_FUNCTION
# define VXL_NULLPTR  NULL
# define VXL_NOEXCEPT throw()
#endif


//----------------------------------------------------------------------------
// Check if the compiler (claims to) support C++11.
#if defined(NDEBUG)
# define VXL_USED_IN_DEBUG(x)
#else
# define VXL_USED_IN_DEBUG(x) x
#endif

#endif // vcl_compiler_h_
