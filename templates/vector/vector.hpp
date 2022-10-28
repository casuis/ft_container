/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:43:46 by asimon            #+#    #+#             */
/*   Updated: 2022/10/28 16:17:56 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  
	https://cplusplus.com/reference/vector/vector/
*/

#ifndef __MY_VECTOR_HPP__
# define __MY_VECTOR_HPP__

# include <header.hpp>
# include <iterator.hpp>
# include <reverse_iterator.hpp>
# include <enable_if.hpp>
# include <is_integral.hpp>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
		
		////////////////////////////////////////////////////////////////////////////////
		/*                              Member Type                                  */
		////////////////////////////////////////////////////////////////////////////////
		
			typedef T													value_type;
			typedef Allocator											allocator_type;
			typedef std::size_t											size_type;
			typedef std::ptrdiff_t										difference_type;
			typedef value_type&											reference;
			typedef const value_type&									const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef const T*											const_pointer;
			typedef	typename ft::RandomIterator< value_type >			iterator;
			typedef	typename ft::RandomIterator< const value_type >		const_iterator;
			typedef typename ft::ReverseIterator< value_type >			r_iterator;
			typedef typename ft::ReverseIterator< const value_type >	const_r_iterator;

		////////////////////////////////////////////////////////////////////////////////
		/*                            Member Function                                 */
		////////////////////////////////////////////////////////////////////////////////
		/* Lifecycle */
		
			/* Default constructor */
			vector (const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _data(0x0), _size(0), _capacity(0) {}

			/* Fill Constructor */
			vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(n), _capacity(n + 1){
				this->_data = this->_alloc.allocate(n + 1);
				size_type		i = 0;
				for (; i < n; i++){
					this->_data[i] = val;
				}
				this->_data[i] = 0x0;
			}

			/* Range Constructor */
			template <typename InputIterator>
			vector (InputIterator first, typename ft::enable_if<!is_integral<InputIterator>::value_type, InputIterator>::type last, const allocator_type &alloc = allocator_type())
			: _alloc(alloc){
				size_t			size = 0;
				InputIterator	tmp = first;
				for (; tmp != last; tmp++){
					size++;
				}
				this->_data = this->_alloc.allocate(size);
				this->_capacity = size;
				this->_size = size;
				for (int i = 0; first != last; first++){
					this->_data[i] = *first;
					i++;
				}
				this->_data[this->_size] = 0x0;
			}
			
			/* Copy Constructor */
			vector(const ft::vector<T> &old)
			: _size(old._size), _capacity(old._capacity) {
				Allocator		alloc;
				size_t i = 0;
				this->_data = alloc.allocate(this->_capacity);
				for (; i < old._size; i++){
					this->_data[i] = old._data[i];
				}
				this->_data[i] = 0x0;
			};

			/* Destructor */
			~vector(){
				this->_alloc.deallocate(this->_data, this->_capacity);
			};

		////////////////////////////////////////////////////////////////////////////////
		/*                              Iterators                                     */
		////////////////////////////////////////////////////////////////////////////////
		
			/* begin return a iterator pointer to the first element of the container */
			const_iterator	begin() const{
				const_iterator		ret(this->_data);
				return (ret);
			}
			
			iterator		begin(){
				iterator		ret(this->_data);
				return (ret);
			}


			////////////////////////////////////////////////////////////////////////////////
			
			/* end return an iterator pointer to the end of the container */
			iterator		end(){
				T		*tmp = this->_data;
				size_t i = 0;
				while (i < this->_size)
					i++;
				iterator	ret(&tmp[i]);
				return (ret);
			}

			const_iterator	end() const{
				T		*tmp = this->_data;
				const_iterator	ret(&tmp[this->_size]);
				return (ret);
			}

			////////////////////////////////////////////////////////////////////////////////
			
			/* rbegin return a reverse pointer to the begining of the container */
			ft::ReverseIterator<T>			rbegin(){
				int		i = 0;
				T		*tmp = this->_data;
				while (i < this->_size)
					i++;
				ft::ReverseIterator<T>			ret(&tmp[i]);
				return (ret);
				
			}
			
			/* rend return a reverse pointer to the end of the container */
			ft::ReverseIterator<T>			rend(){
				ft::ReverseIterator<T>		ret(static_cast<const T>(this->_data));
				return (ret);
			}
			
		////////////////////////////////////////////////////////////////////////////////
		/* C++11 */
		
			/* cbegin return a const pointer to the begining of the container */
			const_iterator	cbegin(){
				const ft::RandomIterator<T> ret(static_cast<const T>(this->_data));		
				return (ret);
			}

			/* cend retutn a const pointer to the end of the container */
			const_iterator	cend(){
				int		i = 0;
				T*		tmp = this->_data;
				while (tmp[i])
					i++;
				const ft::RandomIterator<T>	ret(static_cast<const T>(&tmp[i]));
				return (ret);
			}
			
			////////////////////////////////////////////////////////////////////////////////
			
			/* crbegin return a const reverse pointer to the begining of the container */
			const ft::ReverseIterator<T>			crbegin(){
				int		i = 0;
				T*		tmp = this->_data;
				while (tmp[i])
					i++;
				const ft::ReverseIterator<T>		ret(static_cast<const T>(&tmp[i]));
				return (ret);
			}

			/* crend return a const reverse pointer to the end of the container */
			const ft::ReverseIterator<T>			crend(){
				const ft::ReverseIterator<T>		ret(static_cast<const T>(this->_data));
				return (ret);
			}
		
		////////////////////////////////////////////////////////////////////////////////
		/*                              Capacity                                      */
		////////////////////////////////////////////////////////////////////////////////
		

			/* return a bool, true if container is empty, false if not */
			bool			empty() { return (this->_size == 0); }

			/* return the size of the container */
			size_t			size() const { return (this->_size);}
			
			/* return the capacity of the vector */
			size_t			capacity() const {return (this->_capacity);}
			
			/* return the max sixe of the type T container */
			size_t			max_size() const  {return ((pow(2, (64 - sizeof(T))) - 1));}			

			////////////////////////////////////////////////////////////////////////////////
			
			/* realloc the container to change his capacity to new_cap, the size don't change */
			void			reserve(size_t new_cap) {
				if (this->_capacity > new_cap)
					return ;
				pointer newVec = this->_alloc.allocate(new_cap);
				for (size_t i = 0; i < new_cap && i < this->_size; i++){
					newVec[i] = this->_data[i];
				}
				this->_alloc.deallocate(this->_data, this->_capacity);
				this->_data = newVec;
				this->_capacity = new_cap;
			}

			/* Requests the container to reduce its capacity to fit its size */
			void			shrink_to_fit(){
				if (this->_size != this->_capacity){
					ft::vector<T>		tmp(*this);
					Allocator			alloc;

					delete this->_data;
					this->_data = alloc.allocate(tmp._size);
					for (size_t i = 0; i < tmp._size; i++){
						this->_data[i] = tmp._data[i];
					}
					this->_capacity = this->_size;
				}
			}

			////////////////////////////////////////////////////////////////////////////////
			
			void		resize(size_type n, value_type val = value_type()){
				if (this->_capacity == 0)
					this->reserve(1);
				while (n > this->_capacity)
					this->reserve(this->_capacity * 2);
				size_t i = this->_size;
				if (n > this->_size){
					for (iterator it = this->end(); i < n; i++){
						this->insert(it, val);
						it++;
					}
				}
				if (n < this->_size){
					for (; i > n; i--){
						this->pop_back();
					}
				}
			}
		
		////////////////////////////////////////////////////////////////////////////////
		/*                              Element Access                                */
		////////////////////////////////////////////////////////////////////////////////
		

			reference		operator[](size_t n){
				return (this->_data[n]);
			}
			
			const_reference	operator[](size_t n) const{
				return (this->_data[n]);
			}
			////////////////////////////////////////////////////////////////////////////////
			
			reference		at(size_t n){
				if (n != 0 && (n >= this->_size)){
					throw (std::out_of_range("Error index out of range\n"));
				}
				else
					return (this->_data[n]);
			}
			
			const_reference	at(size_t n) const{
				if (n != 0 && (n >= this->_size || n < 0)){
					throw (std::out_of_range("Error index out of range\n"));
				}
				return (this->_data[n]);
			}
			
			////////////////////////////////////////////////////////////////////////////////
			
			reference		front(){
				return (this->_data[0]);
			}

			const_reference	front() const{
				return (this->_data[0]);
			}

			////////////////////////////////////////////////////////////////////////////////
			
			reference		back(){
				return (this->_data[this->_size - 1]);
			}

			const_reference	back() const{
				return (this->_data[this->_size - 1]);
			}
			
			////////////////////////////////////////////////////////////////////////////////

			value_type*			data(){
				return (this->_data);
			}

			const value_type*	data() const{
				return (this->_data);
			}
		
		////////////////////////////////////////////////////////////////////////////////
		/*                              Modifier                                      */
		////////////////////////////////////////////////////////////////////////////////
		
			
			void push_back (const value_type& val){
				if (this->_capacity == 0)
					this->reserve(1);
				while (this->_size + 1 > this->_capacity)
					this->reserve(this->_capacity * 2);
				this->_data[this->_size] = val;
				this->_size += 1;
			}
			
			void	clear(){
				for (size_t i = 0; i < this->_size; i++){
					this->_data[i] = 0x0;
				}
				this->_size = 0;
			}
			
			void	pop_back(){
				if (this->_size == 0)
					return ;
				this->_data[this->_size - 1] = 0x0;
				this->_size -= 1;
			}
			
			////////////////////////////////////////////////////////////////////////////////

			iterator erase(iterator position){
				if (position >= this->end() || position < this->begin())
					return (position);
				else if (this->_size == 1){
					this->pop_back();
					return (this->begin());
				}
				iterator		it = position;
				iterator		swp = it;
				swp++;
				for (iterator ite = this->end(); it != ite; it++){
					*it = *swp;
					swp++;
				}
				this->_size -= 1;
				return (position);
			}
			
			iterator erase (iterator first, iterator last){
				if (first == last || last < first || first < this->begin() || last > this->end())
					return (first);
				iterator		it = first;
				int				count = 0;
				for (; first != last; first++){
					count++;
				}
				while (count > 0){
					it = this->erase(it);
					count--;
				}
				return (first);
			}
			
			////////////////////////////////////////////////////////////////////////////////

			/* Change the size and the content of the vector to the new range */
			template <class InputIterator>
			void assign (typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last){
				this->clear();
				InputIterator		tmp_it = first;
				InputIterator		tmp_ite = last;
				for (; tmp_it != tmp_ite; tmp_it++){
					this->push_back(*tmp_it);
				}
			}
			
			/* Destroy old content and size and a create a new one of size n of value */
			void assign (size_type n, const value_type& val){
				this->clear();
				for (size_t i = 0; i < n; i++){
					this->push_back(val);
				}
			}

			////////////////////////////////////////////////////////////////////////////////
			
			iterator 		insert (iterator position, const value_type& val){
				int		pos = 0;
				for (iterator it = this->begin(), ite = this->end(); it != ite && it != position; it++){
					pos++;
					if ((it + 1 == ite) && (it != position) && (it + 1 != position))
						return (position);
				}
				while (this->_size + 1 > this->_capacity)
					this->reserve(this->_capacity * 2);
				position = this->begin() + pos;
				if (position == this->end()){
					this->push_back(val);
					return (position);
				}
				vector<T>			tab(*this);
				this->clear();
				for (iterator start = tab.begin(), end = tab.end(), cmp = this->begin();
					start != end;
					start++){
					if (cmp == position){
						this->push_back(val);}
					this->push_back(*start);
					cmp++;
				}
				return (position);
			}
			
			template <class InputIterator>
			void 			insert (iterator position, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last){
				size_t 		size = 0;
				size_t		pos = 0;
				for (iterator it = this->begin(), ite = this->end(); it != ite && it != position; it++){
					pos++;
				}
				for (InputIterator it = first, ite = last; it != ite; it++){
					size++;
				}
				while (this->_size + size > this->_capacity)
					this->reserve(this->_capacity * 2);
				for (; first != last; first++){
					position = this->insert(this->begin() + pos, *first);
				}
			}
			
			void 			insert (iterator position, size_type n, const value_type& val){
				if (position > this->end() || position < this->begin())
					return ;
				while (this->_size + n > this->_capacity)	
					this->reserve(this->_capacity * 2);
				for (size_t i = 0; i <= n; i++){
					position = this->insert(position, val);
				}
			}
			
			////////////////////////////////////////////////////////////////////////////////
		
			void			swap(vector<T>& x){
				pointer		tmp_data = this->_data;
				size_t		tmp_cap = this->_capacity;
				size_t		tmp_size = this->_size;
				Allocator	tmp_alloc = this->_alloc;
				
				this->_data = x._data;
				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_alloc = x._alloc;
				x._data = tmp_data;
				x._capacity = tmp_cap;
				x._size = tmp_size;
				x._alloc = tmp_alloc;
			}
			
			////////////////////////////////////////////////////////////////////////////////
			/*                              Allocator                                     */
			////////////////////////////////////////////////////////////////////////////////

			allocator_type 	get_allocator() const{
				return (this->_alloc);
			}
			
			////////////////////////////////////////////////////////////////////////////////
			/*                              Operators                                     */
			////////////////////////////////////////////////////////////////////////////////


			vector<T>&		operator=(const vector<T>& old){
				if (old._data == this->_data)
					return (*this);
				if (this->_data != 0x0)
					this->_alloc.deallocate(this->_data, this->_capacity);
				this->_capacity = old._capacity;
				this->_data = this->_alloc.allocate(this->_capacity);
				for (size_t i = 0; i < old._size; i++){
					this->_data[i] = old._data[i];
				}
				this->_size = old._size;
				return (*this);
			}
			
			bool			operator==(const vector<T>& old){
				for (size_t i = 0; i < this->_size && i < old._size; i++){
					if (this->_data[i] != old._data[i])
						return (false);
				}
				return (true);
			}

			bool			operator<(const vector<T>& old){
				for (size_t i = 0; i < this->_size && i < old._size; i++){
					if (this->_data[i] >= old._data[i])
						return (false);
				}
				return (true);
			}		

			bool			operator>(const vector<T>& old){
				for (size_t i = 0; i < this->_size && i < old._size; i++){
					if (this->_data[i] <= old._data[i])
						return (false);
				}
				return true;
			}

			bool			operator<=(const vector<T>& old){
				for (size_t i = 0; i < this->_size && i < old._size; i++){
					if (this->_data[i] > old._data[i])
						return (false);
				}
				return (true);
			}
			
			bool			operator>=(const vector<T>& old){
				for (size_t i = 0; i < this->_size && i < old._size; i++){
					if (this->_data[i] <= old._data[i])
						return (false);
				}
				return (true);
			}

			bool			operator!=(const vector<T>& old){
				for (size_t i = 0; i < this->_size && i < old._size; i++){
					if (this->_data[i] == old._data[i])
						return (false);
				}
				return (true);
			}
			
		private:
			allocator_type	_alloc;
			T*				_data;
			size_type		_size;
			size_type		_capacity;

	};
}

#endif