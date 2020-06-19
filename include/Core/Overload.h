#pragma once

/** @file */

/** \struct Overload
 *
 *
 *  \ingroup Core
 *
 *  *  \brief Overload lambda <em>hack</em> for variant std::visit
 *
 *
 * */
template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>; ///< deduction guide