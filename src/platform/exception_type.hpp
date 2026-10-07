#ifndef EXCEPTION_TYPE_HPP
#define EXCEPTION_TYPE_HPP

#include <string>

#include <cpptrace/basic.hpp>

#include "platform/platform.hpp"

#if CPPTRACE_HAS_RTTI
 #include <typeinfo>
 #include <cpptrace/utils.hpp>
#endif

// libstdc++ and libc++
#if defined(CPPTRACE_HAS_CXX_EXCEPTION_TYPE) && (IS_LIBSTDCXX || IS_LIBCXX)
 #include <typeinfo>
 #include <cxxabi.h>
 #include "demangle/demangle.hpp"
#endif

CPPTRACE_BEGIN_NAMESPACE
namespace detail {
    inline std::string exception_type_name() {
        #if defined(CPPTRACE_HAS_CXX_EXCEPTION_TYPE) && (IS_LIBSTDCXX || IS_LIBCXX)
         const std::type_info* t = abi::__cxa_current_exception_type();
         return t ? detail::demangle(t->name(), false) : "<unknown>";
        #else
         return "<unknown>";
        #endif
    }

    // Dynamic type of a caught exception, read from the exception runtime when RTTI is off.
    template<typename E>
    std::string caught_exception_type_name(const E& e) {
        #if CPPTRACE_HAS_RTTI
         return cpptrace::demangle(typeid(e).name());
        #else
         (void)e;
         return exception_type_name();
        #endif
    }
}
CPPTRACE_END_NAMESPACE

#endif
