/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftnspace.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 00:33:50 by asimon            #+#    #+#             */
/*   Updated: 2023/02/20 20:24:43 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_NAMESPACE__
# define __FT_NAMESPACE__

# include "./header.hpp"

# if STD == 1 
#	define NAMESPACE std
# else
#	define NAMESPACE ft
# endif 

# include "../templates/functions/is_integral.hpp"
# include "../templates/functions/enable_if.hpp"
# include "../templates/functions/equal.hpp"
# include "../templates/iterator/iterator_traits.hpp"
# include "../templates/iterator/iterator.hpp"
# include "../templates/iterator/reverse_iterator.hpp" 
# include "../templates/map/Bst.hpp"
# include "../templates/map/pair.hpp"
# include "../templates/vector/vector.hpp"
# include "../templates/map/Bst.hpp"
# include "../templates/stack/stack.hpp"
# include "../templates/map/map.hpp"
# include "../templates/iterator/iterator_map.hpp"
# include "../templates/iterator/reverse_iterator_map.hpp"

namespace ft{

	// void		print(NAMESPACE::vector<int>& tab, std::string msg){
	// 	for (size_t i = 0; i < tab.size(); i++){
	// 		std:: cout <<  M_GREEN << "| " << M_M_RESET;
	// 		std::cout << msg << "[" << M_GREEN << tab[i] << M_M_RESET << "]" << std::endl;
	// 	}
	// 	std::cout << std::endl << "capacity: [" << M_GREEN << tab.capacity() << M_M_RESET << "]"<< std::endl;
	// 	std::cout << std::endl << "size: [" << M_GREEN << tab.size() << M_M_RESET << "]" << std::endl;
	// 	std::cout << std::endl << "max size: [" << M_GREEN << tab.max_size() << M_M_RESET << "]" << std::endl;
	// 	std::cout << M_GREEN << std::string(42, '-') << M_M_RESET << std::endl;
	// }
	
	// void		print( NAMESPACE::vector< NAMESPACE::vector<int> >& tab, std::string msg){
	// 	for (size_t i = 0; i < tab.size(); i++){
	// 		for (size_t j = 0; j < tab.at(i).size(); j++){
	// 			std:: cout <<  M_GREEN << "| " << M_M_RESET;
	// 			std::cout << msg << "[" << M_GREEN << tab.at(i).at(j) << M_M_RESET << "]" << std::endl;
	// 		}
	// 	}
	// 	std::cout << std::endl << "capacity: [" <<  M_GREEN << tab.capacity() << M_M_RESET << "]"<< std::endl;
	// 	std::cout << std::endl << "size: [" << M_GREEN << tab.size() << M_M_RESET << "]" << std::endl;
	// 	std::cout << std::endl << "max size: [" << M_GREEN << tab.max_size() << M_M_RESET << "]" << std::endl;
	// 	std::cout << M_GREEN << std::string(42, '-') << M_M_RESET << std::endl;
	// }

}

	
	


#endif