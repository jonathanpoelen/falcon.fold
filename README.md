g++-4.9, g++-5, clang-3.6: [![Travis Build Status](https://travis-ci.org/jonathanpoelen/falcon.fold.svg?branch=master)](https://travis-ci.org/jonathanpoelen/falcon.fold)

VS 2015: [![Appveyor Build Status](https://ci.appveyor.com/api/projects/status/github/jonathanpoelen/falcon.fold)](https://ci.appveyor.com/project/jonathanpoelen/falcon-fold)

# Falcon.fold

Fold functions on parameter list.

Header only (c++14).


# Documentation

All functions are in namespaces `falcon` and `falcon::fold` in the form `decltype(auto) fold(fn &&, Ts && ...)`.

- Parameter `fn`:  Binary function. If no element in a fold, is used as a generator (cf: `fn()`)
- `Ts... args`: list of values

The ref-qualifier functions are supported and used for the last call if `fn` is a rvalue.


## foldr

Apply `fn` from right to left.

``` cpp
foldr(fn, 1, 2, 3, 4, 5, 6)
// Equivalent to
fn(1, fn(2, fn(3, fn(4, fn(5, 6)))))
```


## foldl

Apply `fn` from left to right.

``` cpp
foldl(fn, 1, 2, 3, 4, 5, 6)
// Equivalent to
fn(fn(fn(fn(fn(1, 2), 3), 4), 5), 6)
```


## foldbl

Apply `fn` as a balanced left tree.

``` cpp
foldbl(fn, 1, 2, 3, 4, 5, 6, 7, 8)
// Equivalent to
fn(fn(fn(1, 2), fn(3, 4)), fn(fn(5, 6), fn(7, 8)))

foldbl(fn, 1, 2, 3, 4, 5)
// Equivalent to
fn(fn(fn(1, 2), 3),fn(4,5))
```


## foldbr

Apply `fn` as a balanced right tree.

``` cpp
foldbr(fn, 1, 2, 3, 4, 5, 6, 7, 8)
// Equivalent to
fn(fn(fn(1, 2), fn(3, 4)), fn(fn(5, 6), fn(7, 8)))

foldbr(fn, 1, 2, 3, 4, 5)
// Equivalent to
fn(fn(1, 2), fn(3, fn(4, 5)))
```


## foldt

Apply `fn` as a nested sub-expressions.

``` cpp
foldt(fn, 1, 2, 3, 4, 5, 6, 7, 8)
// Equivalent to
fn(fn(fn(1, 2), fn(3, 4)), fn(fn(5, 6), fn(7, 8)))

foldt(fn, 1, 2, 3, 4, 5)
// Equivalent to
fn(fn(fn(1, 2), fn(3, 4)), 5)
```


## foldp

Apply `fn` as a nested sub-expressions of 1 item, then 2, 4, 8, etc.

``` cpp
foldp(folder, f, 1, 2, 3, 4, 5, 6, 7, 8)
// Equivalent to
f(0, f(folder(1, 2), f(folder(3, 4, 5, 6), folder(7, 8))))
```
