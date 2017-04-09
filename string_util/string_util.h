/*
  ===========================================================================

  Copyright (C) 2014 Emvivre

  This file is part of STRING_UTIL.

  STRING_UTIL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  STRING_UTIL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with STRING_UTIL.  If not, see <http://www.gnu.org/licenses/>.

  ===========================================================================
*/

#ifndef _STRING_UTIL_H_
#define _STRING_UTIL_H_

#include <algorithm>
#include <vector>
#include <sstream>

namespace StringUtil
{
	inline std::string upper(const std::string& s_orig)
	{
		std::string s = s_orig;
		std::transform(s.begin(), s.end(), s.begin(), ::toupper);
		return s;
	}
	inline std::string lower(const std::string& s_orig) 
	{
		std::string s = s_orig;
		std::transform(s.begin(), s.end(), s.begin(), ::tolower);
		return s;
	}
	inline bool contains(const std::string& s, const std::string& pattern)
	{
		return s.find(pattern) != std::string::npos;
	}
	inline bool startswith(const std::string& s, const std::string& pattern) 
	{
		return std::equal(pattern.begin(), pattern.end(), s.begin());
	}
	inline bool endswith(const std::string& s, const std::string& pattern) 
	{
		return std::equal(pattern.begin(), pattern.end(), s.end()-pattern.size());
	}
	inline std::vector<std::string> split(const std::string& s, char c)
        {
		std::vector<std::string> v;
                unsigned int beg = 0;
                for ( unsigned int i = 0; i < s.size(); i++ ) {
                        if ( s[i] == c ) {
				std::string e = s.substr(beg, i - beg);
                                v.push_back(e);
                                beg = i+1;
                        }
                }
                if ( beg < s.size() ) {
			std::string e = s.substr(beg, s.size() - beg);
                        v.push_back(e);
                }
                return v;
        }
	inline std::string extension(const std::string& file)
	{
		int i = file.size();
		while (i-- && file[i] != '.');
		i++;
		return file.substr(i, file.size() - i);
	}	
	inline std::string remove_extension(const std::string& file) 
	{
		int i = file.size();
		while (i-- && file[i] != '.');
		if ( i == 0 ) return "";		
		return file.substr(0, i);	
	}
	inline unsigned int extract_hexa(const std::string& s)
	{
		std::stringstream ss;
		if ( s[0] != '0' || ( s[1] != 'x' && s[1] != 'X' ) ) {
			ss << "0x";
		}
		ss << s;
		unsigned int v;
		ss >> std::hex >> v;
		return v;
	}
	inline std::string replace(const std::string& s, const std::string& before, const std::string& after) {
		std::string ss = s;
                while ( 1 ) { 
                        unsigned long long idx = ss.find( before );
                        if ( idx == std::string::npos ) break;
                        ss.replace( idx, before.size(), after );
                }
                return ss;
        }
	inline std::string strip( const std::string& s ) {
		if ( s.size() == 0 ) return s;
		unsigned int idx_beg = 0;
		unsigned int idx_end = s.size()-1;
		while ( true ) {
			bool changed = false;
			if ( (s[idx_beg] == '\r' || s[idx_beg] == '\n' || s[idx_beg] == ' ') && idx_beg < idx_end ) {
				idx_beg++;
				changed = true;
			}
			if ( (s[idx_end] == '\r' || s[idx_end] == '\n' || s[idx_end] == ' ') && idx_beg < idx_end ) {
				idx_end--;
				changed = true;
			}
			if ( changed == false ) {
				break;
			}
		}
		return s.substr( idx_beg, idx_end - idx_beg + 1 );
	}
	inline std::string strip( const std::string& s, const std::string& pattern ) {
		unsigned int idx_beg = 0;
		unsigned int idx_end = s.size() - 1;
		while ( idx_beg + pattern.size() <= idx_end && s.substr( idx_beg, pattern.size() ) == pattern ) { idx_beg += pattern.size(); }
		while ( idx_end >= pattern.size() && idx_beg <= idx_end - pattern.size() && s.substr( idx_end-pattern.size() + 1, pattern.size() ) == pattern ) { idx_end -= pattern.size(); }
		return s.substr( idx_beg, idx_end - idx_beg + 1 );
	}	
	template <class FROM, class TO=std::string>
	inline TO conv(const FROM& input)
	{
		std::stringstream ss;
		ss << input;
		TO output;
		ss >> output;
		return output;
	}
}

#endif /* !_STRING_UTIL_H_ */
