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
 * Template parameter `arity` (optional):  Number of arguments to the function `f`
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


template<std::size_t arity, class Fn>
constexpr decltype(auto) foldr(Fn && f) {
  return std::forward<Fn>(f)();
}

template<std::size_t arity, class Fn, class... Ts>
constexpr decltype(auto) foldr(Fn && f, Ts && ... args);
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


template<std::size_t arity, class Fn>
constexpr decltype(auto) foldl(Fn && f){
  return std::forward<Fn>(f)();
}

template<std::size_t arity, class Fn, class... Ts>
constexpr decltype(auto) foldl(Fn && f, Ts && ... args);
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


template<std::size_t arity, class Fn>
constexpr decltype(auto) foldt(Fn && f) {
  return std::forward<Fn>(f)();
}

template<std::size_t arity, class Fn, class... Ts>
constexpr decltype(auto) foldt(Fn && f, Ts && ... args);
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
  constexpr decltype(auto) foldr_impl(Fn && f, T0 && x0, T1 && x1, T2 && x2, T3 && x3, T4 && x4, U && y, Ts && ... args) {
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


  template<size_t arity, class Elems>
  struct foldl_arity;

  template<class... Ts>
  struct foldl_arity<2, brigand::list<Ts...>>
  {
    template<class Fn, class... Us>
    static constexpr decltype(auto) impl(Fn && f, Us && ... args) {
      return ::falcon::fold::foldl(std::forward<Fn>(f), std::forward<Us>(args)...);
    }
  };

  template<size_t arity, class... Ts>
  struct foldl_arity<arity, brigand::list<Ts...>>
  {
    template<class Fn>
    static constexpr decltype(auto) impl(Fn && f, Ts... e) {
      return std::forward<Fn>(f)(std::forward<Ts>(e)...);
    }

    template<class Fn, class... Us>
    static constexpr decltype(auto) impl(Fn && f, Ts... e, Us && ... args) {
      return foldl_arity<
        arity,
        make_elems_t<
          (sizeof...(Us) + 1u < arity ? sizeof...(Us) + 1u : arity),
          decltype(f(std::forward<Ts>(e)...)),
          Us && ...
        >
      >::impl(std::forward<Fn>(f), f(std::forward<Ts>(e)...), std::forward<Us>(args)...);
    }
  };
} } }

namespace fold {
  template<std::size_t arity, class Fn, class... Ts>
  constexpr decltype(auto) foldl(Fn && f, Ts && ... args) {
    static_assert(arity > 1u, "arity must be greater than 1");
    return detail::fold::foldl_arity<
      arity,
      detail::fold::make_elems_t<
        (sizeof...(Ts) < arity ? sizeof...(Ts) : arity),
        Ts && ...
      >
    >::impl(std::forward<Fn>(f), std::forward<Ts>(args)...);
  }
} // namespace fold


namespace detail { namespace { namespace fold {
  template<size_t arity, class Elems>
  struct foldr_arity;

  template<class... Ts>
  struct foldr_arity<2, brigand::list<Ts...>>
  {
    template<class Fn, class... Us>
    static constexpr decltype(auto) first_step_impl(Fn && f, Us && ... args) {
      return ::falcon::fold::foldr(std::forward<Fn>(f), std::forward<Us>(args)...);
    }
  };

  constexpr size_t count_foldr_element(size_t count_element, size_t arity) {
    return count_element < arity
      ? count_element - 1u
      : (arity - 1u) - (count_element - arity) % (arity - 1u);
  }

  template<size_t arity, class... Ts>
  struct foldr_arity<arity, brigand::list<Ts...>>
  {
    template<class Fn>
    static constexpr decltype(auto) impl(Fn & f, Ts... e) {
      return f(static_cast<Ts>(e)...);
    }

    template<class Fn, class T>
    static constexpr decltype(auto) impl(Fn & f, Ts... e, T && arg) {
      return f(static_cast<Ts>(e)..., std::forward<T>(arg));
    }

    template<class Fn, class... Us>
    static constexpr decltype(auto) impl(Fn & f, Ts... e, Us && ... args) {
      return f(static_cast<Ts>(e)..., foldr_arity<
        arity,
        make_elems_t<
          count_foldr_element(sizeof...(Us), arity),
          Us && ...
        >
      >::impl(f, std::forward<Us>(args)...));
    }

    template<class Fn, class T>
    static constexpr decltype(auto) first_step_impl(Fn && f, Ts... e, T && arg) {
      return std::forward<Fn>(f)(static_cast<Ts>(e)..., std::forward<T>(arg));
    }

    template<class Fn, class... Us>
    static constexpr decltype(auto) first_step_impl(Fn && f, Ts... e, Us && ... args) {
      return std::forward<Fn>(f)(static_cast<Ts>(e)..., foldr_arity<
        arity,
        make_elems_t<
          count_foldr_element(sizeof...(Us), arity),
          Us && ...
        >
      >::impl(f, std::forward<Us>(args)...));
    }
  };
} } }

namespace fold {
  template<std::size_t arity, class Fn, class... Ts>
  constexpr decltype(auto) foldr(Fn && f, Ts && ... args) {
    static_assert(arity > 1u, "arity must be greater or equal than 2");
    return detail::fold::foldr_arity<
      arity,
      detail::fold::make_elems_t<
        detail::fold::count_foldr_element(sizeof...(Ts), arity),
        Ts && ...
      >
    >::first_step_impl(std::forward<Fn>(f), std::forward<Ts>(args)...);
  }
} // namespace fold


#if !defined(_MSC_VER) || _MSC_VER > 1900
namespace detail { namespace { namespace fold {
  template<size_t I> using seqi = brigand::range<std::size_t, 0, I>;

  template<class> struct arg;

  struct any { template<class T> any(T const &) {} };

  template<class... Any>
  struct arg<brigand::list<Any...>>
  {
    template<class T, class... Ts>
    static constexpr decltype(auto) impl(Any..., T && x, Ts && ...) {
      return std::forward<T>(x);
    }
  };

  template<class... I, class Fn, class... Ts>
  constexpr decltype(auto) invoke(brigand::list<I...>, Fn & f, Ts && ... args) {
    return f(arg<brigand::filled_list<any, I::value>>::impl(std::forward<Ts>(args)...)...);
  }

  template<class Ints, class Inc> struct seq_inc;

  template<class... I, class Inc>
  struct seq_inc<brigand::list<I...>, Inc>
  { using type = brigand::list<brigand::size_t<(I::value + Inc::value * sizeof...(I))>...>; };

  template<class SeqArity, class Inc>
  using seq_inc_t = typename seq_inc<SeqArity, Inc>::type;

  template<class SeqArity, class Seq> struct seqseqi_impl;

  template<class SeqArity, class... IPack>
  struct seqseqi_impl<SeqArity, brigand::list<IPack...>>
  { using type = brigand::list<seq_inc_t<SeqArity, IPack>...>; };

  template<size_t arity, size_t N>
  using seqseqi = typename seqseqi_impl<
    seqi<arity>,
    seqi<N / arity>
  >::type;

  template<size_t arity, class... IResidue, class Fn, class... Ts>
  constexpr decltype(auto)
  foldt_impl(brigand::list<>, brigand::list<IResidue...>, Fn && f, Ts && ... args) {
    return std::forward<Fn>(f)(std::forward<Ts>(args)...);
  }

  template<size_t arity, class Ints, class Fn, class... Ts>
  constexpr decltype(auto)
  foldt_impl(brigand::list<Ints>, brigand::list<>, Fn && f, Ts && ... args) {
    return std::forward<Fn>(f)(std::forward<Ts>(args)...);
  }

  template<
    size_t arity, class... Ints, class... IResidue, class Fn, class... Ts,
    // avort ambiguous call with gcc
    class = std::enable_if_t<
      ((sizeof...(Ints) > 1 || sizeof...(IResidue))
     && sizeof...(Ints) != 0)>>
  constexpr decltype(auto)
  foldt_impl(brigand::list<Ints...>, brigand::list<IResidue...>, Fn && f, Ts && ... args) {
    return foldt_impl<arity>(
      seqseqi<arity, sizeof...(Ints) + sizeof...(IResidue)>{},
      seqi<(sizeof...(Ints) + sizeof...(IResidue)) % arity>{},
      std::forward<Fn>(f),
      invoke(Ints{}, f, std::forward<Ts>(args)...)...,
      arg<brigand::filled_list<any, IResidue::value + sizeof...(Ints) * arity>>::impl(std::forward<Ts>(args)...)...
    );
  }
} } }

namespace fold {
  template<class Fn, class T, class U, class... Ts>
  constexpr decltype(auto) foldt(Fn && f, T && x, U && y, Ts && ... args) {
    return detail::fold::foldt_impl<2u>(
      detail::fold::seqseqi<2u, 2u+sizeof...(Ts)>{},
      detail::fold::seqi<sizeof...(Ts) % 2u>{},
      std::forward<Fn>(f),
      std::forward<T>(x),
      std::forward<U>(y),
      std::forward<Ts>(args)...
    );
  }

  template<std::size_t arity, class Fn, class... Ts>
  constexpr decltype(auto) foldt(Fn && f, Ts && ... args) {
    static_assert(arity > 1u, "arity must be greater than 1");
    return detail::fold::foldt_impl<arity>(
      detail::fold::seqseqi<arity, sizeof...(Ts)>{},
      detail::fold::seqi<sizeof...(Ts) % arity>{},
      std::forward<Fn>(f),
      std::forward<Ts>(args)...
    );
  }
} // namespace fold


namespace detail { namespace { namespace fold {
  template<size_t arity, class Elems, size_t Pow>
  struct foldi_arity;

  template<size_t arity, class... Ts, size_t Pow>
  struct foldi_arity<arity, brigand::list<Ts...>, Pow>
  {
    template<class Fn>
    static constexpr decltype(auto) impl(Fn & f, Ts... e) {
      return ::falcon::fold::foldt<arity>(f, static_cast<Ts>(e)...);
    }

    template<class Fn, class... Us>
    static constexpr decltype(auto) impl(Fn & f, Ts... e, Us && ... args) {
      return f(::falcon::fold::foldt<arity>(f, static_cast<Ts>(e)...), foldi_arity<
        arity,
        make_elems_t<
          Pow * arity < sizeof...(args) ? Pow * arity : sizeof...(args),
          Us && ...
        >,
        Pow * arity
      >::impl(f, std::forward<Us>(args)...));
    }

    template<class Fn>
    static constexpr decltype(auto) first_step_impl(Fn && f, Ts... e) {
      return std::forward<Fn>(f)(static_cast<Ts>(e)...);
    }

    template<class Fn, class... Us>
    static constexpr decltype(auto) first_step_impl(Fn && f, Ts... e, Us && ... args) {
      return std::forward<Fn>(f)(static_cast<Ts>(e)..., foldi_arity<
        arity,
        make_elems_t<
          Pow * arity < sizeof...(args) ? Pow * arity : sizeof...(args),
          Us && ...
        >,
        Pow * arity
      >::impl(f, std::forward<Us>(args)...));
    }
  };
} } }

namespace fold {
  template<class Fn, class T, class U, class V, class... Ts>
  constexpr decltype(auto) foldi(Fn && f, T && x, U && y, V && z, Ts && ... args) {
    return std::forward<Fn>(f)(
      std::forward<T>(x),
      detail::fold::foldi_arity<
        2u,
        brigand::list<U&&, V&&>,
        2u
      >::impl(f, std::forward<U>(y), std::forward<V>(z), std::forward<Ts>(args)...)
    );
  }

  template<std::size_t arity, class Fn, class... Ts>
  constexpr decltype(auto) foldi(Fn && f, Ts && ... args) {
    static_assert(arity > 1u, "arity must be greater than 1");
    return detail::fold::foldi_arity<
      arity,
      detail::fold::make_elems_t<arity-1, Ts&&...>,
      1u
    >::first_step_impl(std::forward<Fn>(f), std::forward<Ts>(args)...);
  }
} // namespace fold

using fold::foldt;
using fold::foldi;
#endif

using fold::foldr;
using fold::foldl;

} // namespace falcon

#endif
