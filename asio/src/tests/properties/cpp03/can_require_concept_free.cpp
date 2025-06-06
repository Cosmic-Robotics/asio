//
// cpp03/can_require_concept_free.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2025 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "asio/require_concept.hpp"
#include <cassert>

template <int>
struct prop
{
  static const bool is_requirable_concept = true;
};

template <int>
struct object
{
  template <int N>
  friend object<N> require_concept(const object&, prop<N>)
  {
    return object<N>();
  }
};

namespace asio {

template<int N, int M>
struct is_applicable_property<object<N>, prop<M> >
{
  static const bool value = true;
};

namespace traits {

template<int N, int M>
struct require_concept_free<object<N>, prop<M> >
{
  static const bool is_valid = true;
  static const bool is_noexcept = true;
  typedef object<M> result_type;
};

} // namespace traits
} // namespace asio

int main()
{
  assert((asio::can_require_concept<object<1>, prop<2> >::value));
  assert((asio::can_require_concept<const object<1>, prop<2> >::value));
}
