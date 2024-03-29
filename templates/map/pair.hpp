/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:02:01 by asimon            #+#    #+#             */
/*   Updated: 2023/02/07 19:41:59 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # include <header.hpp>

# include "../../private/header.hpp"

#ifndef __PAIR_HPP__
# define __PAIR_HPP__

namespace ft{
	
	template <typename K, typename V>
	struct pair{
		typedef K			key_type;
		typedef V			value_type;
		
		public:
			key_type		first;
			value_type		second;

			pair(key_type key, value_type value): first(key), second(value) {return ;}

			pair(): first(key_type()), second(value_type()) {}
			
			template <typename T, typename Y>
			pair(const pair<T, Y> param): first(param.first), second(param.second) {return ;}
			
			~pair() {return ;}

			////////////////////////////////////////////////////////////////////////////////
			
			pair&		operator=(const pair& param){
				if (this == &param)
					return (*this);
				this->first = param.first;
				this->second = param.second;
				return (*this);
			}
	};

	template <typename First,  typename Second>
	bool		operator==(const ft::pair<First, Second>& lhs, const ft::pair<First, Second>& rhs){
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	
	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }

	template <typename Key, typename V>
	ft::pair<Key, V>		make_pair(Key key, V value) {
		return (ft::pair<Key, V>(key, value));
	}


}
#endif