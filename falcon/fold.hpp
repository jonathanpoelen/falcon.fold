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
 * \brief     Fold functions on parameter list: foldl, foldr, foldbl, foldbr, foldt and foldp.
 *
 * `f`: Binary function. If no element in a fold, is used as a generator (cf: `f()`)
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
constexpr decltype(auto)
foldr(Fn && f) {
  return std::forward<Fn>(f)();
}

template<class Fn, class T>
constexpr decltype(auto)
foldr(Fn &&, T && x) {
  return std::forward<T>(x);
}

template<class Fn, class T, class U>
constexpr decltype(auto)
foldr(Fn && f, T && x, U && y) {
  return std::forward<Fn>(f)(std::forward<T>(x), std::forward<U>(y));
}

template<class Fn, class T, class U, class... Ts>
constexpr decltype(auto)
foldr(Fn && f, T && x, U && y, Ts && ... args);
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
constexpr decltype(auto)
foldl(Fn && f) {
  return std::forward<Fn>(f)();
}

template<class Fn, class T>
constexpr decltype(auto)
foldl(Fn &&, T && x) {
  return std::forward<T>(x);
}

template<class Fn, class T, class U>
constexpr decltype(auto)
foldl(Fn && f, T && x, U && y) {
  return std::forward<Fn>(f)(std::forward<T>(x), std::forward<U>(y));
}

template<class Fn, class T, class U, class... Ts>
constexpr decltype(auto)
foldl(Fn && f, T && x, U && y, Ts && ... args);
/** @} */


/**
 * \brief  Apply \a f as a balanced left tree
 *
 * \code foldbl(f, 1, 2, 3, 4, 5, 6, 7, 8) \endcode
 * equivalent to
 * \code f(f(f(1, 2), f(3, 4)), f(f(5, 6), f(7, 8))) \endcode
 *
 * \code foldbl(f, 1, 2, 3, 4, 5, 6, 7) \endcode
 * equivalent to
 * \code f(f(f(1, 2), f(3, 4)), f(f(5, 6), 7)) \endcode
 * @{
 */
template<class Fn>
constexpr decltype(auto)
foldbl(Fn && f) {
  return std::forward<Fn>(f)();
}

template<class Fn, class T>
constexpr decltype(auto)
foldbl(Fn &&, T && x) {
  return std::forward<T>(x);
}

template<class Fn, class T, class U>
constexpr decltype(auto)
foldbl(Fn && f, T && x, U && y) {
  return std::forward<Fn>(f)(std::forward<T>(x), std::forward<U>(y));
}

template<class Fn, class T, class U, class... Ts>
constexpr decltype(auto)
foldbl(Fn && f, T && x, U && y, Ts && ... args);
/** @} */


/**
 * \brief  Apply \a f as a balanced right tree
 *
 * \code foldbr(f, 1, 2, 3, 4, 5, 6, 7, 8) \endcode
 * equivalent to
 * \code f(f(f(1, 2), f(3, 4)), f(f(5, 6), f(7, 8))) \endcode
 *
 * \code foldbr(f, 1, 2, 3, 4, 5, 6, 7) \endcode
 * equivalent to
 * \code f(f(1, f(2, 3)), f(f(4, 5), f(6, 7))) \endcode
 * @{
 */
template<class Fn>
constexpr decltype(auto)
foldbr(Fn && f) {
  return std::forward<Fn>(f)();
}

template<class Fn, class T>
constexpr decltype(auto)
foldbr(Fn &&, T && x) {
  return std::forward<T>(x);
}

template<class Fn, class T, class U>
constexpr decltype(auto)
foldbr(Fn && f, T && x, U && y) {
  return std::forward<Fn>(f)(std::forward<T>(x), std::forward<U>(y));
}

template<class Fn, class T, class U, class... Ts>
constexpr decltype(auto)
foldbr(Fn && f, T && x, U && y, Ts && ... args);
/** @} */


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
constexpr decltype(auto)
foldt(Fn && f) {
  return std::forward<Fn>(f)();
}

template<class Fn, class T>
constexpr decltype(auto)
foldt(Fn &&, T && x) {
  return std::forward<T>(x);
}

template<class Fn, class T, class U>
constexpr decltype(auto)
foldt(Fn && f, T && x, U && y) {
  return std::forward<Fn>(f)(std::forward<T>(x), std::forward<U>(y));
}

template<class Fn, class T, class U, class... Ts>
constexpr decltype(auto)
foldt(Fn && f, T && x, U && y, Ts && ... args);
/** @} */


/**
 * \brief  Apply \a f as a nested sub-expressions of 1 item, then 2, 4, 8, etc.
 *
 * \code foldp(foldt, f, 1, 2, 3, 4, 5, 6, 7, 8) \endcode
 * equivalent to
 * \code f(0, f(folder(1, 2), f(folder(3, 4, 5, 6), folder(7, 8)))) \endcode
 * @{
 */
template<class Folder, class Fn>
constexpr decltype(auto)
foldp(Folder &&, Fn && f) {
  return std::forward<Fn>(f)();
}

template<class Folder, class Fn, class T>
constexpr decltype(auto)
foldp(Folder &&, Fn &&, T && x) {
  return std::forward<T>(x);
}

template<class Folder, class Fn, class T, class U>
constexpr decltype(auto)
foldp(Folder &&, Fn && f, T && x, U && y) {
  return std::forward<Fn>(f)(std::forward<T>(x), std::forward<U>(y));
}

template<class Folder, class Fn, class T, class U, class V, class... Ts>
constexpr decltype(auto)
foldp(Folder && folder, Fn && f, T && x, U && y, V && z, Ts && ... args);
/** @} */

} // namespace fold


// Implementation

namespace detail { namespace { namespace fold {
  using std::size_t;

  template<size_t n, class... Ts>
#if defined(__GNUC__) and !defined(__clang__) and __GNUC__ <= 5
  using make_elems_t = brigand::pop_back<brigand::list<Ts...>, brigand::size_t<(brigand::size<brigand::list<Ts...>>::value - n)>>;
#else
  using make_elems_t = brigand::pop_back<brigand::list<Ts...>, brigand::size_t<(sizeof...(Ts) - n)>>;
#endif
} } }


//#if defined(__cpp_fold_expressions) && __cpp_fold_expressions >= 201411
#if __cplusplus > 201402L
# define FALCON_HAS_FOLD_EXPRESSION 1
#else
# define FALCON_HAS_FOLD_EXPRESSION 0
#endif


#if FALCON_HAS_FOLD_EXPRESSION
namespace detail { namespace { namespace fold {
  template<class F, class T = void>
  struct FoldFn
  {
    F fn;
    T value;
  };

  template<class F>
  struct FoldFn<F, void>
  {
    F fn;
  };

  template<class F, class T>
  constexpr FoldFn<F&, T> foldfn(F & f, T && x)
  { return {f, std::forward<T>(x)}; }

  template<class F>
  constexpr FoldFn<F&> foldfn(F & f)
  { return {f}; }

  template<class F, class T, class U>
  constexpr decltype(auto)
  operator, (T && x, FoldFn<F, U> && w) {
    return foldfn(w.fn, w.fn(std::forward<T>(x), std::forward<U>(w.value)));
  }

  template<class F, class T>
  constexpr decltype(auto)
  operator, (T && x, FoldFn<F> && w) {
    return FoldFn<F, T&&>{w.fn, std::forward<T>(x)};
  }
} } }

namespace fold {
  template<class Fn, class T, class U, class... Ts>
  constexpr decltype(auto)
  foldr(Fn && f, T && x, U && y, Ts && ... args)
  {
    return std::forward<Fn>(f)(
      std::forward<T>(x),
      f(
        std::forward<U>(y),
        (std::forward<Ts>(args), ..., detail::fold::foldfn(f)).value
      )
    );
  }
}


namespace detail { namespace { namespace fold {
  template<class F, class T, class U>
  constexpr decltype(auto)
  operator, (FoldFn<F, T> && w, U && y) {
    return foldfn(w.fn, w.fn(std::forward<T>(w.value), std::forward<U>(y)));
  }

  template<class F, class U>
  constexpr decltype(auto)
  operator, (FoldFn<F> && w, U && y) {
    return FoldFn<F, U&&>{w.fn, std::forward<U>(y)};
  }

  template<class Elems>
  struct foldl_impl;

  template<class... Ts>
  struct foldl_impl<brigand::list<Ts...>>
  {
    template<class Fn, class U>
    static constexpr decltype(auto)
    impl(Fn && f, Ts... e, U && y) {
      return std::forward<Fn>(f)(
        (foldfn(f), ..., static_cast<Ts>(e)).value,
        std::forward<U>(y)
      );
    }
  };
} } }

namespace fold {
  template<class Fn, class T, class U, class... Ts>
  constexpr decltype(auto)
  foldl(Fn && f, T && x, U && y, Ts && ... args)
  {
    return detail::fold::foldl_impl<
      detail::fold::make_elems_t<
        sizeof...(Ts)+1,
        T&&, U&&, Ts&&...
      >
    >::impl(
      std::forward<Fn>(f),
      std::forward<T>(x),
      std::forward<U>(y),
      std::forward<Ts>(args)...
    );
  }

  template<class Fn, class T, class U, class... Ts>
  constexpr decltype(auto)
  foldl(Fn & f, T && x, U && y, Ts && ... args)
  {
    return (
      detail::fold::foldfn(f, f(std::forward<T>(x), std::forward<U>(y)))
    , ...
    , std::forward<Ts>(args)
    ).value;
  }
}
#else
namespace detail { namespace { namespace fold {
  template<class Elems>
  struct foldr_impl;

  template<class T>
  struct foldr_impl<brigand::list<T>>
  {
    template<class Fn, class U>
    static constexpr decltype(auto)
    impl(Fn && f, T a, U && b) {
      return std::forward<Fn>(f)(static_cast<T>(a), std::forward<U>(b));
    }

    template<class Fn, class U1, class U2>
    static constexpr decltype(auto)
    impl(Fn && f, T a, U1 && b, U2 && c) {
      return std::forward<Fn>(f)(
        static_cast<T>(a),
        f(std::forward<U1>(b), std::forward<U2>(c))
      );
    }
  };

  template<class... Ts>
  struct foldr_impl<brigand::list<Ts...>>
  {
    template<class Fn, class... Us>
    static constexpr decltype(auto)
    impl(Fn & f, Ts... e, Us && ... args) {
      return foldr_impl<
        make_elems_t<
          (1u+sizeof...(Ts))/2,
          Ts...
        >
      >::impl(
        f,
        static_cast<Ts>(e)...,
        foldr_impl<
          make_elems_t<
            sizeof...(Us)/2,
            Us&&...
          >
        >::impl(f, std::forward<Us>(args)...)
      );
    }
  };
} } }

namespace fold {
  template<class Fn, class T, class U, class... Ts>
  constexpr decltype(auto)
  foldr(Fn && f, T && x, U && y, Ts && ... args) {
    return std::forward<Fn>(f)(
      std::forward<T>(x),
      detail::fold::foldr_impl<
        detail::fold::make_elems_t<
          (1u+sizeof...(Ts))/2,
          U&&, Ts&&...
        >
      >::impl(f, std::forward<U>(y), std::forward<Ts>(args)...)
    );
  }
} // namespace fold


namespace detail { namespace { namespace fold {
  template<class Elems>
  struct foldl_impl;

  template<class T>
  struct foldl_impl<brigand::list<T>>
  {
    template<class Fn, class U1>
    static constexpr decltype(auto)
    impl(Fn && f, U1 && a, T b) {
      return std::forward<Fn>(f)(std::forward<U1>(a), static_cast<T>(b));
    }

    template<class Fn, class U1, class U2>
    static constexpr decltype(auto)
    impl(Fn && f, U1 && a, T b, U2 && c) {
      return std::forward<Fn>(f)(f(std::forward<U1>(a), static_cast<T>(b)), std::forward<U2>(c));
    }

    template<class Fn, class U1, class U2, class U3>
    static constexpr decltype(auto)
    impl(Fn && f, U1 && a, T b, U2 && c, U3 && d) {
      return std::forward<Fn>(f)(
        f(
          f(
            std::forward<U1>(a),
            static_cast<T>(b)
          ),
          std::forward<U2>(c)
        ),
        std::forward<U3>(d)
      );
    }
  };

  template<class... Ts>
  struct foldl_impl<brigand::list<Ts...>>
  {
    template<class Fn, class T, class... Us>
    static constexpr decltype(auto)
    impl(Fn && f, T && a, Ts... e, Us && ... args) {
      return foldl_impl<
        make_elems_t<
          (sizeof...(Us))/2,
          Us&&...
        >
      >::impl(
        std::forward<Fn>(f),
        foldl_impl<
          make_elems_t<
            (sizeof...(Ts))/2,
            Ts...
          >
        >::impl(
          f,
          std::forward<T>(a),
          static_cast<Ts>(e)...
        ),
        std::forward<Us>(args)...
      );
    }
  };
} } }

namespace fold {
  template<class Fn, class T, class U, class... Ts>
  constexpr decltype(auto)
  foldl(Fn && f, T && x, U && y, Ts && ... args) {
    return detail::fold::foldl_impl<
      detail::fold::make_elems_t<
        sizeof...(Ts)/2+1,
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
#endif


namespace detail { namespace { namespace fold {
  template<class Elems>
  struct foldbr_impl;

  template<>
  struct foldbr_impl<brigand::list<>>
  {
    template<class Fn, class T>
    static constexpr T &&
    impl(Fn &&, T && e) {
      return std::forward<T>(e);
    }
  };

  template<class T>
  struct foldbr_impl<brigand::list<T>>
#if FALCON_HAS_FOLD_EXPRESSION
  {
    template<class Fn, class U>
    static constexpr decltype(auto)
    impl(Fn && f, T a, U && b) {
      return std::forward<Fn>(f)(static_cast<T>(a), std::forward<U>(b));
    }

    template<class Fn, class U1, class U2>
    static constexpr decltype(auto)
    impl(Fn && f, T a, U1 && b, U2 && c) {
      return std::forward<Fn>(f)(
        static_cast<T>(a),
        f(std::forward<U1>(b), std::forward<U2>(c))
      );
    }
  };
#else
  : foldr_impl<brigand::list<T>>
  {};
#endif

  template<class... Ts>
  struct foldbr_impl<brigand::list<Ts...>>
  {
    template<class Fn, class... Us>
    static constexpr decltype(auto)
    impl(Fn && f, Ts... e, Us && ... args) {
      return std::forward<Fn>(f)(
        foldbr_impl<
          make_elems_t<
            sizeof...(Ts)/2,
            Ts...
          >
        >::impl(f, static_cast<Ts>(e)...),
        foldbr_impl<
          make_elems_t<
            sizeof...(Us)/2,
            Us&&...
          >
        >::impl(f, std::forward<Us>(args)...)
      );
    }
  };
} } }

namespace fold {
  template<class Fn, class T, class U, class... Ts>
  constexpr decltype(auto)
  foldbr(Fn && f, T && x, U && y, Ts && ... args) {
    return
    detail::fold::foldbr_impl<
      detail::fold::make_elems_t<
        (2u+sizeof...(Ts))/2,
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
  template<class Elems>
  struct foldbl_impl;

  template<class T>
  struct foldbl_impl<brigand::list<T>>
  {
    template<class Fn>
    static constexpr T
    impl(Fn &&, T a) {
      return static_cast<T>(a);
    }

    template<class Fn, class U>
    static constexpr decltype(auto)
    impl(Fn && f, T a, U && b) {
      return std::forward<Fn>(f)(static_cast<T>(a), std::forward<U>(b));
    }

    template<class Fn, class U1, class U2>
    static constexpr decltype(auto)
    impl(Fn && f, T a, U1 && b, U2 && c) {
      return std::forward<Fn>(f)(
        f(static_cast<T>(a), std::forward<U1>(b)),
        std::forward<U2>(c)
      );
    }
  };

  template<class... Ts>
  struct foldbl_impl<brigand::list<Ts...>>
  {
    template<class Fn, class... Us>
    static constexpr decltype(auto)
    impl(Fn && f, Ts... e, Us && ... args) {
      return std::forward<Fn>(f)(
        foldbl_impl<
          make_elems_t<
            sizeof...(Ts)/2 + sizeof...(Ts) % 2,
            Ts...
          >
        >::impl(f, static_cast<Ts>(e)...),
        foldbl_impl<
          make_elems_t<
            sizeof...(Us)/2 + sizeof...(Us) % 2,
            Us&&...
          >
        >::impl(f, std::forward<Us>(args)...)
      );
    }
  };
} } }

namespace fold {
  template<class Fn, class T, class U, class... Ts>
  constexpr decltype(auto)
  foldbl(Fn && f, T && x, U && y, Ts && ... args) {
    return detail::fold::foldbl_impl<
      detail::fold::make_elems_t<
        sizeof...(Ts)/2 + sizeof...(Ts) % 2 + 1,
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
  constexpr size_t
  count_foldt_element(size_t count)
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
    static constexpr T
    impl(Fn &, T e) {
      return static_cast<T>(e);
    }
  };

  template<class... Ts>
  struct foldt_impl<brigand::list<Ts...>>
  {
    template<class Fn>
    static constexpr decltype(auto)
    impl(Fn && f, Ts... e) {
      return std::forward<Fn>(f)(static_cast<Ts>(e)...);
    }

    template<class Fn, class... Us>
    static constexpr decltype(auto)
    impl(Fn && f, Ts... e, Us && ... args) {
      return std::forward<Fn>(f)(
        foldt_impl<
          make_elems_t<
            count_foldt_element(sizeof...(Ts)),
            Ts...
          >
        >::impl(f, static_cast<Ts>(e)...),
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
  constexpr decltype(auto)
  foldt(Fn && f, T && x, U && y, Ts && ... args) {
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
  struct foldp_impl;

  template<class... Ts, size_t Pow>
  struct foldp_impl<brigand::list<Ts...>, Pow>
  {
    template<class Folder, class Fn>
    static constexpr decltype(auto)
    impl(Folder & folder, Fn &, Ts... e) {
      return folder(static_cast<Ts>(e)...);
    }

    template<class Folder, class Fn, class... Us>
    static constexpr decltype(auto)
    impl(Folder & folder, Fn & f, Ts... e, Us && ... args) {
      return f(
        folder(static_cast<Ts>(e)...),
        foldp_impl<
          make_elems_t<
            std::min(Pow * 2u, sizeof...(args)),
            Us && ...
          >,
          Pow * 2
        >::impl(
          folder,
          f,
          std::forward<Us>(args)...
        )
      );
    }
  };
} } }

namespace fold {
  template<class Folder, class Fn, class T, class U, class V, class... Ts>
  constexpr decltype(auto)
  foldp(Folder && folder, Fn && f, T && x, U && y, V && z, Ts && ... args) {
    return std::forward<Fn>(f)(
      std::forward<T>(x),
      detail::fold::foldp_impl<
        brigand::list<U&&, V&&>,
        2u
      >::impl(
        folder,
        f,
        std::forward<U>(y),
        std::forward<V>(z),
        std::forward<Ts>(args)...
      )
    );
  }
} // namespace fold

using fold::foldt;
using fold::foldp;
using fold::foldbr;
using fold::foldbl;
using fold::foldr;
using fold::foldl;

} // namespace falcon

#endif
