// gmd-tree-library - C++ - gmd global members

// Copyright (C) 2017 Gustavo Martins

// This file is part of the gmd-tree-library. This library is free
// software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this library.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _GMD_GMD_
#define _GMD_GMD_

namespace gmd {

using ushort = unsigned short;

/* === Random === */
::std::random_device _random_generator;
::std::uniform_int_distribution<size_t> _uniform_int_distribution;
::std::uniform_real_distribution<double> _uniform_real_distribution;
/* === Random === */

/* === Transparent === */
template <typename A, typename B = void, typename = ::std::void_t<>> struct _is_transparent : public ::std::false_type {};
template <typename A, typename B> struct _is_transparent<A, B, ::std::void_t<typename A::is_transparent>>
	: public ::std::true_type { using _type = void; };
template <typename A, typename B = void, typename = ::std::void_t<>>
	using _is_transparent_t = typename _is_transparent<A, B>::_type;
template <typename A, typename B = void, typename = ::std::void_t<>>
	constexpr bool _is_transparent_v = _is_transparent<A, B>::value;
/* === Transparent === */

/* === Visit === */
template <typename A, typename B> struct _visit {
	constexpr bool operator() (A *) { return false; }
	constexpr bool operator() (B *) { return true;  } };
/* === Visit === */

}

#endif
