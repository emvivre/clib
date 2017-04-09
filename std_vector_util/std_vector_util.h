/*
  ===========================================================================

  Copyright (C) 2015 Emvivre

  This file is part of STD_VECTOR_UTIL.

  STD_VECTOR_UTIL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  STD_VECTOR_UTIL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with STD_VECTOR_UTIL.  If not, see <http://www.gnu.org/licenses/>.

  ===========================================================================
*/

#ifndef _STD_VECTOR_UTIL_H_
#define _STD_VECTOR_UTIL_H_

#include <vector>
#include <algorithm>

namespace StdVectorUtil {
	template <class T>
	inline std::vector<std::pair<T,T> > couples(const std::vector<T>& v) {
		unsigned int sz = v.size();
		std::vector<std::pair<T, T> > r;
		for ( unsigned int i = 0; i < sz; i++ ) {
			for ( unsigned int j = i+1; j < sz; j++ ) {
				r.push_back(std::make_pair(v[i], v[j]));
			}
		}
		return r;
	}
	
	template <class T>
	inline std::vector<std::pair<T,T> > cartesian_product(const std::vector<T>& v0, const std::vector<T>& v1) {
		std::vector<std::pair<T, T> > r;
		for ( const auto& e0 : v0 ) { 
			for ( const auto& e1 : v1 ) { 
				r.push_back(std::make_pair(e0, e1));
			}
		}
		return r;
	}

	template <class T>
	inline std::vector<T> random_selection( const std::vector<T>& v, unsigned int nb ) {
		std::vector<unsigned int> idx;
		idx.reserve( v.size() );
		for ( unsigned int i = 0; i < v.size(); i++ ) idx.push_back(i);
		std::random_shuffle( idx.begin(), idx.end() );
		std::vector<T> vv;
		vv.reserve( nb ); 
		for ( unsigned int i = 0; i < nb; i++ ) vv.push_back( v[ idx[i] ] );
		return vv;
	}

	template <class T>
	inline bool is_in( const T& e, const std::vector<T>& v ) {
		return std::find( v.begin(), v.end(), e ) != v.end();
	}

	template <class T>
	inline void remove( std::vector<T>& v, const T& e ) { 		
	        v.erase( std::remove( v.begin(), v.end(), e ), v.end() );
	}
}
#endif /* !_STD_VECTOR_UTIL_H_ */
