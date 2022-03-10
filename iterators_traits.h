/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators_traits.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:48:00 by yer-raki          #+#    #+#             */
/*   Updated: 2022/03/07 15:30:24 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <class Iterator> class iterator_traits
{
    typedef typename Iterator::value_type      		value_type;
    typedef typename Iterator::difference_type		difference_type;
    typedef typename Iterator::pointer				pointer;
    typedef typename Iterator::reference			reference;
    typedef typename Iterator::iterator_category	iterator_category;
};

// Specialization
template <class T> class iterator_traits<T*>
{
	typedef	T								value_type;
	typedef	ptrdiff_t						difference_type;
	typedef	T*								pointer;
	typedef	T& 								reference;
	typedef	std::random_access_iterator_tag	iterator_category;
};

template <class T> class iterator_traits<const T*>
{
    typedef	T								value_type;
	typedef	ptrdiff_t						difference_type;
	typedef	T*								pointer;
	typedef	T& 								reference;
	typedef	std::random_access_iterator_tag	iterator_category;
};

// https://docs.oracle.com/cd/E19422-01/819-3704/ite_2405.htm