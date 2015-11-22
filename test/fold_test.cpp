#include <falcon/fold.hpp>

#include <string>

std::string const & to_string(std::string const & s) {
  return s;
}
std::string const & to_string(std::string && s);

struct MkStr
{
  template<class... Ts>
  std::string operator()(Ts const & ... args) && {
    std::string ret = "[";
    ret += (*this)(args...);
    ret += "]";
    return ret;
  }

  std::string operator()() const & {
    return "empty";
  }

  template<class T>
  std::string operator()(T const & x) const & {
    using ::to_string;
    using std::to_string;
    return to_string(x);
  }

  template<class T, class U>
  std::string operator()(T const & x, U const & y) const & {
    using ::to_string;
    using std::to_string;
    std::string ret{"("};
    ret += to_string(x);
    ret += "+";
    ret += to_string(y);
    ret += ")";
    return ret;
  }

  template<class T, class U, class V>
  std::string operator()(T const & x, U const & y, V const & z) const & {
    using ::to_string;
    using std::to_string;
    std::string ret{"("};
    ret += to_string(x);
    ret += "+";
    ret += to_string(y);
    ret += "+";
    ret += to_string(z);
    ret += ")";
    return ret;
  }
};

template<int> struct int_ {};

template<int x, int y>
int_<x+y> operator+(int_<x>, int_<y>)
{ return {}; }

template<class...> struct list {};

struct MkList
{
  template<class T, class U, class... Us>
  auto operator()(T x, list<U, Us...>) const {
    return list<decltype(U{}+x), U, Us...>{};
  }

  template<class T>
  list<T> operator()(T, list<>) const {
    return {};
  }
};

template<class T> struct Check {};


#include <iostream>
#include <cstdlib>

int main()
{
  MkStr f;

#define CHECK(s, f)                                                            \
  do {                                                                         \
    auto r = (f);                                                              \
    if (s != r) {                                                              \
      std::cerr << __LINE__ << ":\n" << s << " != " #f "\n" << r << std::endl; \
      std::abort();                                                            \
    }                                                                          \
  } while (0)

  using namespace falcon::fold;

  CHECK("(1+(2+(3+(4+(5+(6+(7+(8+(9+(10+(11+(12+(13+0)))))))))))))", foldr(f, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0));
  CHECK("(((((((((((((0+1)+2)+3)+4)+5)+6)+7)+8)+9)+10)+11)+12)+13)", foldl(f, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13));
  CHECK("((((1+2)+(3+4))+((5+6)+(7+8)))+(((9+10)+(11+12))+(13+0)))", foldt(f, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0));
  CHECK("((((1+2)+(3+4))+((5+6)+(7+8)))+(((9+10)+(11+12))+13))", foldt(f, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13));
  CHECK("(((1+2)+(3+4))+5)", foldt(f, 1, 2, 3, 4, 5));
  CHECK("(1+((2+3)+(((4+5)+(6+7))+(((8+9)+(10+11))+((12+13)+0)))))", foldi(f, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0));

  CHECK("(1+2)", foldr(f, 1, 2));
  CHECK("(1+2)", foldl(f, 1, 2));
  CHECK("(1+2)", foldt(f, 1, 2));
  CHECK("(1+2)", foldi(f, 1, 2));

  CHECK(1, foldr(f, 1));
  CHECK(1, foldl(f, 1));
  CHECK(1, foldt(f, 1));
  CHECK(1, foldi(f, 1));

  CHECK("empty", foldr(f));
  CHECK("empty", foldl(f));
  CHECK("empty", foldt(f));
  CHECK("empty", foldi(f));

  CHECK("(0+1)", foldl<3>(f, 0, 1));
  CHECK("(0+1+2)", foldl<3>(f, 0, 1, 2));
  CHECK("((0+1+2)+3)", foldl<3>(f, 0, 1, 2, 3));
  CHECK("((0+1+2)+3+4)", foldl<3>(f, 0, 1, 2, 3, 4));
  CHECK("(((((((0+1+2)+3+4)+5+6)+7+8)+9+10)+11+12)+13)", foldl<3>(f, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13));

  CHECK("(12+13)", foldr<3>(f, 12, 13));
  CHECK("(12+13+0)", foldr<3>(f, 12, 13, 0));
  CHECK("(11+(12+13+0))", foldr<3>(f, 11, 12, 13, 0));
  CHECK("(10+11+(12+13+0))", foldr<3>(f, 10, 11, 12, 13, 0));
  CHECK("(1+(2+3+(4+5+(6+7+(8+9+(10+11+(12+13+0)))))))", foldr<3>(f, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0));

  CHECK("(0+1)", foldt<3>(f, 0, 1));
  CHECK("(0+1+2)", foldt<3>(f, 0, 1, 2));
  CHECK("((0+1+2)+3)", foldt<3>(f, 0, 1, 2, 3));
  CHECK("((0+1+2)+3+4)", foldt<3>(f, 0, 1, 2, 3, 4));
  CHECK("((0+1+2)+(3+4+5))", foldt<3>(f, 0, 1, 2, 3, 4, 5));
  CHECK("(((0+1+2)+(3+4+5)+6)+7)", foldt<3>(f, 0, 1, 2, 3, 4, 5, 6, 7));
  CHECK("(((1+2+3)+(4+5+6)+(7+8+9))+(10+11+12)+13)", foldt<3>(f, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13));

  CHECK("(0+1)", foldi<3>(f, 0, 1));
  CHECK("(0+1+2)", foldi<3>(f, 0, 1, 2));
  CHECK("(0+1+(2+3))", foldi<3>(f, 0, 1, 2, 3));
  CHECK("(0+1+(2+3+4))", foldi<3>(f, 0, 1, 2, 3, 4));
  CHECK("(0+1+((2+3+4)+5))", foldi<3>(f, 0, 1, 2, 3, 4, 5));
  CHECK("(1+2+((3+4+5)+(((6+7+8)+(9+10+11)+12)+13)))", foldi<3>(f, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13));
  CHECK("(1+2+((3+4+5)+(((6+7+8)+(9+10+11)+(12+13+14))+((15+16+17)+18))))", foldi<3>(f, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18));

  // ref qualifier tests
  CHECK("[((0+1)+2)]", foldl(MkStr{}, 0, 1, 2));
  CHECK("[(0+(1+2))]", foldr(MkStr{}, 0, 1, 2));
  CHECK("[((0+1)+(2+3))]", foldt(MkStr{}, 0, 1, 2, 3));
  CHECK("[(0+((1+2)+3))]", foldi(MkStr{}, 0, 1, 2, 3));
  CHECK("[(((0+1+2)+3+4)+5+6)]", foldl<3>(MkStr{}, 0, 1, 2, 3, 4, 5, 6));
  CHECK("[(0+1+(2+3+(4+5+6)))]", foldr<3>(MkStr{}, 0, 1, 2, 3, 4, 5, 6));
  CHECK("[((0+1+2)+(3+4+5)+6)]", foldt<3>(MkStr{}, 0, 1, 2, 3, 4, 5, 6));
  CHECK("[(0+1+((2+3+4)+(5+6)))]", foldi<3>(MkStr{}, 0, 1, 2, 3, 4, 5, 6));

  struct A {};
  struct ApplyA_rvalue { A operator()(A &&, A &&) { return {}; } };
  foldl(ApplyA_rvalue{}, A{}, A{});
  struct ApplyA_lvalue { A operator()(A &, A &) { return {}; } };
  {A a; foldl(ApplyA_lvalue{}, a, a);}

  Check<list<
    int_<1+2+3+4>,
    int_<2+3+4>,
    int_<3+4>,
    int_<4>
  >>{} = Check<decltype(foldr(MkList{}, int_<1>{}, int_<2>{}, int_<3>{}, int_<4>{}, list<>{}))>{};
}
