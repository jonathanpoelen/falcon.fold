/* The MIT License (MIT)

Copyright (c) 2015 Jonathan Poelen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * \author    Jonathan Poelen <jonathan.poelen+fold@gmail.com>
 * \version   1.0
 * \brief     Fold functions on parameter list: foldl, foldr, foldt and foldi.
 *
 * Parameter `f`:  Binary function. If no element in a fold, is used as a generator (cf: `f()`)
 * `Ts... args`: list of values
 *
 * The ref-qualifier functions are supported and used for the last call if `f` is a rvalue.
 */

#ifndef FALCON_FOLD_HPP
#define FALCON_FOLD_HPP

#include <utility>
#include <type_traits>

#include <brigand/brigand.hpp>


namespace falcon {
namespace fold {

/**
 * \brief  Apply \a f from right to left
 *
 * \code foldr(f, 1, 2, 3, 4, 5, 6) \endcode
 * equivalent to
 * \code f(1, f(2, f(3, f(4, f(5, 6))))) \endcode
 * @{
 */
template<class Fn>
constexpr decltype(auto) foldr(Fn && f) {
  return std::forward<Fn>(f)();
}

template<class Fn, class T>
constexpr decltype(auto) foldr(Fn &&, T && x) {
  return std::forward<T>(x);
}

template<class Fn, class T, class U>
constexpr decltype(auto) foldr(Fn && f, T && x, U && y) {
  return std::forward<Fn>(f)(std::forward<T>(x), std::forward<U>(y));
}

template<class Fn, class T, class U, class... Ts>
constexpr decltype(auto) foldr(Fn && f, T && x, U && y, Ts && ... args);
/** @} */


/**
 * \brief  Apply \a f from right to left
 *
 * \code foldl(f, 1, 2, 3, 4, 5, 6) \endcode
 * equivalent to
 * \code f(f(f(f(f(1, 2), 3), 4), 5), 6) \endcode
 * @{
 */
template<class Fn>
constexpr decltype(auto) foldl(Fn && f) {
  return std::forward<Fn>(f)();
}

template<class Fn, class T>
constexpr decltype(auto) foldl(Fn &&, T && x) {
  return std::forward<T>(x);
}

template<class Fn, class T, class U>
constexpr decltype(auto) foldl(Fn && f, T && x, U && y) {
  return std::forward<Fn>(f)(std::forward<T>(x), std::forward<U>(y));
}

template<class Fn, class T, class U, class... Ts>
constexpr decltype(auto) foldl(Fn && f, T && x, U && y, Ts && ... args) {
  return foldl(
    std::forward<Fn>(f),
    f(std::forward<T>(x), std::forward<U>(y)),
    std::forward<Ts>(args)...
  );
}

template<class Fn, class T0, class T1, class T2, class T3, class T4, class U, class... Ts>
constexpr decltype(auto) foldl(Fn && f, T0 && x0, T1 && x1, T2 && x2, T3 && x3, T4 && x4, U && y, Ts && ... args) {
  return foldl(
    std::forward<Fn>(f),
    f(f(f(f(std::forward<T0>(x0), std::forward<T1>(x1)), std::forward<T2>(x2)), std::forward<T3>(x3)), std::forward<T4>(x4)),
    std::forward<U>(y),
    std::forward<Ts>(args)...
  );
}
/** @} */


#if !defined(_MSC_VER) || _MSC_VER > 1900
/**
 * \brief  Apply \a f as a nested sub-expressions
 *
 * \code foldt(f, 1, 2, 3, 4, 5, 6, 7, 8) \endcode
 * equivalent to
 * \code f(f(f(1, 2), f(3, 4)), f(f(5, 6), f(7, 8))) \endcode
 *
 * \code foldt(f, 1, 2, 3, 4, 5) \endcode
 * equivalent to
 * \code f(f(f(1, 2), f(3, 4)), 5) \endcode
 * @{
 */
template<class Fn>
constexpr decltype(auto) foldt(Fn && f) {
  return std::forward<Fn>(f)();
}

template<class Fn, class T>
constexpr decltype(auto) foldt(Fn &&, T && x) {
  return std::forward<T>(x);
}

template<class Fn, class T, class U>
constexpr decltype(auto) foldt(Fn && f, T && x, U && y) {
  return std::forward<Fn>(f)(std::forward<T>(x), std::forward<U>(y));
}

template<class Fn, class T, class U, class... Ts>
constexpr decltype(auto) foldt(Fn && f, T && x, U && y, Ts && ... args);
/** @} */


/**
 * \brief  Apply \a f as a nested sub-expressions of 1 item, then 2, 4, 8, etc.
 *
 * \code foldi(f, 1, 2, 3, 4, 5, 6, 7, 8) \endcode
 * equivalent to
 * \code f(0, f(f(1, 2), f(f(f(3, 4), f(5, 6)), f(7, 8)))) \endcode
 * or
 * \code f(foldt(f, 0), f(foldt(f, 1, 2), foldt(f, 3, 4, 5, 6, 7, 8)))) \endcode
 * @{
 */
template<class Fn>
constexpr decltype(auto) foldi(Fn && f) {
  return std::forward<Fn>(f)();
}

template<class Fn, class T>
constexpr decltype(auto) foldi(Fn &&, T && x) {
  return std::forward<T>(x);
}

template<class Fn, class T, class U>
constexpr decltype(auto) foldi(Fn && f, T && x, U && y) {
  return std::forward<Fn>(f)(std::forward<T>(x), std::forward<U>(y));
}

template<class Fn, class T, class U, class V, class... Ts>
constexpr decltype(auto) foldi(Fn && f, T && x, U && y, V && z, Ts && ... args);
/** @} */
#endif

} // namespace fold


// Implementation

namespace detail { namespace { namespace fold {
  template<class Fn, class T, class U>
  constexpr decltype(auto) foldr_impl(Fn & f, T && x, U && y) {
    return f(std::forward<T>(x), std::forward<U>(y));
  }

  template<class Fn, class T, class U, class... Ts>
  constexpr decltype(auto) foldr_impl(Fn & f, T && x, U && y, Ts && ... args) {
    return f(
      std::forward<T>(x),
      foldr_impl(f, std::forward<U>(y), std::forward<Ts>(args)...)
    );
  }

  template<class Fn, class T0, class T1, class T2, class T3, class T4, class U, class... Ts>
  constexpr decltype(auto) foldr_impl(Fn & f, T0 && x0, T1 && x1, T2 && x2, T3 && x3, T4 && x4, U && y, Ts && ... args) {
    return
      f(std::forward<T0>(x0),
        f(std::forward<T1>(x1),
          f(std::forward<T2>(x2),
            f(std::forward<T3>(x3),
              f(std::forward<T4>(x4),
                foldr_impl(f, std::forward<U>(y), std::forward<Ts>(args)...)
              )
            )
          )
        )
      );
  }
} } }

namespace fold {
  template<class Fn, class T, class U, class... Ts>
  constexpr decltype(auto) foldr(Fn && f, T && x, U && y, Ts && ... args) {
    return std::forward<Fn>(f)(
      std::forward<T>(x),
      detail::fold::foldr_impl(f, std::forward<U>(y), std::forward<Ts>(args)...)
    );
  }
} // namespace fold


namespace detail { namespace { namespace fold {
  using std::size_t;

  template<size_t n, class... Ts>
#if defined(__GNUC__) and !defined(__clang__) and __GNUC__ <= 5
  using make_elems_t = brigand::pop_back<brigand::list<Ts...>, brigand::size_t<(brigand::size<brigand::list<Ts...>>::value - n)>>;
#else
  using make_elems_t = brigand::pop_back<brigand::list<Ts...>, brigand::size_t<(sizeof...(Ts) - n)>>;
#endif
} } }


#if !defined(_MSC_VER) || _MSC_VER > 1900
namespace detail { namespace { namespace fold {
  constexpr size_t count_foldt_element(size_t count)
  {
    size_t n = 2;
    while (n * 2 < count) {
      n *= 2;
    }
    return std::min(n, count);
  }

  template<class Elems>
  struct foldt_impl;

  template<class T>
  struct foldt_impl<brigand::list<T>>
  {
    template<class Fn>
    static constexpr T impl(Fn &, T e) {
      return static_cast<T>(e);
    }
  };

  template<class... Ts>
  struct foldt_impl<brigand::list<Ts...>>
  {
    template<class Fn>
    static constexpr decltype(auto) impl(Fn && f, Ts... e) {
      return std::forward<Fn>(f)(static_cast<Ts>(e)...);
    }

    template<class Fn, class... Us>
    static constexpr decltype(auto) impl(Fn && f, Ts... e, Us && ... args) {
      return std::forward<Fn>(f)(
        foldt_impl<
          make_elems_t<
            count_foldt_element(sizeof...(Ts)),
            Ts&&...
          >
        >::impl(f, std::forward<Ts>(e)...),
        foldt_impl<
          make_elems_t<
            count_foldt_element(sizeof...(Us)),
            Us&&...
          >
        >::impl(f, std::forward<Us>(args)...)
      );
    }
  };

} } }

namespace fold {
  template<class Fn, class T, class U, class... Ts>
  constexpr decltype(auto) foldt(Fn && f, T && x, U && y, Ts && ... args) {
    return detail::fold::foldt_impl<
      detail::fold::make_elems_t<
        detail::fold::count_foldt_element(sizeof...(Ts)+2),
        T&&, U&&, Ts&&...
      >
    >::impl(
      std::forward<Fn>(f),
      std::forward<T>(x),
      std::forward<U>(y),
      std::forward<Ts>(args)...
    );
  }
} // namespace fold


namespace detail { namespace { namespace fold {
  template<class Elems, size_t Pow>
  struct foldi_impl;

  template<class... Ts, size_t Pow>
  struct foldi_impl<brigand::list<Ts...>, Pow>
  {
    template<class Fn>
    static constexpr decltype(auto) impl(Fn & f, Ts... e) {
      return ::falcon::fold::foldt(f, static_cast<Ts>(e)...);
    }

    template<class Fn, class... Us>
    static constexpr decltype(auto) impl(Fn & f, Ts... e, Us && ... args) {
      return f(::falcon::fold::foldt(f, static_cast<Ts>(e)...), foldi_impl<
        make_elems_t<
          Pow * 2 < sizeof...(args) ? Pow * 2 : sizeof...(args),
          Us && ...
        >,
        Pow * 2
      >::impl(f, std::forward<Us>(args)...));
    }

    template<class Fn>
    static constexpr decltype(auto) first_step_impl(Fn && f, Ts... e) {
      return std::forward<Fn>(f)(static_cast<Ts>(e)...);
    }

    template<class Fn, class... Us>
    static constexpr decltype(auto) first_step_impl(Fn && f, Ts... e, Us && ... args) {
      return std::forward<Fn>(f)(static_cast<Ts>(e)..., foldi_impl<
        make_elems_t<
          Pow * 2 < sizeof...(args) ? Pow * 2 : sizeof...(args),
          Us && ...
        >,
        Pow * 2
      >::impl(f, std::forward<Us>(args)...));
    }
  };
} } }

namespace fold {
  template<class Fn, class T, class U, class V, class... Ts>
  constexpr decltype(auto) foldi(Fn && f, T && x, U && y, V && z, Ts && ... args) {
    return std::forward<Fn>(f)(
      std::forward<T>(x),
      detail::fold::foldi_impl<
        brigand::list<U&&, V&&>,
        2u
      >::impl(f, std::forward<U>(y), std::forward<V>(z), std::forward<Ts>(args)...)
    );
  }
} // namespace fold

using fold::foldt;
using fold::foldi;
#endif

using fold::foldr;
using fold::foldl;

} // namespace falcon

#endif
