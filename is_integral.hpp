/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:00:44 by yer-raki          #+#    #+#             */
/*   Updated: 2022/03/29 18:27:09 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    template< class T >
    struct is_integral
    {
        static const bool value = false /* = true if T is integral, false otherwise */;
    };
    // specialisation
    template <> struct is_integral<bool> { static const bool value = true; };
    template <> struct is_integral<char> { static const bool value = true; };
    template <> struct is_integral<char16_t> { static const bool value = true; };
    template <> struct is_integral<char32_t> { static const bool value = true; };
    template <> struct is_integral<wchar_t> { static const bool value = true; };
    template <> struct is_integral<short> { static const bool value = true; };
    template <> struct is_integral<int> { static const bool value = true; };
    template <> struct is_integral<long> { static const bool value = true; };
    template <> struct is_integral<long long> { static const bool value = true; };
}
