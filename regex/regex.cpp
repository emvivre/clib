/*
  ===========================================================================

  Copyright (C) 2013 Emvivre

  This file is part of REGEXP.

  REGEXP is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  REGEXP is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with REGEXP.  If not, see <http://www.gnu.org/licenses/>.

  ===========================================================================
*/

#include "regex.hpp"
#include <regex.h>
#include <sstream>

std::vector<Regex::Result> Regex::search_idx(std::string pattern, std::string buffer) {
	std::vector<Regex::Result> match_res;	
	regex_t r;
	int nb_matches = 128;
	regmatch_t* matches = new regmatch_t[nb_matches];		
	if ( regcomp(&r, pattern.c_str(), REG_EXTENDED) != 0 ) {
		throw ExceptionRegexpCompilationError();
	}
	int beg = 0;
	while ( regexec(&r, buffer.c_str() + beg, nb_matches, matches, 0) != REG_NOMATCH ) {
		int i = (matches[1].rm_so == -1) ? 0 : 1;
		for (; i < nb_matches; i++ ) {
			if ( matches[i].rm_so == -1 ) {
				break ;
			}
			int l = matches[i].rm_eo - matches[i].rm_so;
			unsigned int idx = beg + matches[i].rm_so;
			std::string str(&buffer[idx], l);			
			match_res.push_back( Result(idx, str) );
		}
		beg += matches[0].rm_eo;
	}
	regfree(&r);
	delete[] matches;
	return match_res;	       
}

std::vector<std::string> Regex::search(std::string pattern, std::string buffer) {
	std::vector<Regex::Result> res = search_idx( pattern, buffer );
	std::vector<std::string> match_str;
	for ( const auto& r : res ) { 
		match_str.push_back( r.str );
	}
	return match_str;
}

std::string Regex::strip( const std::string& s_orig, const std::string& ch) {
	std::string s = s_orig;
	std::stringstream ss;
	ss << "([";
	for ( unsigned int i = 0; i < ch.size(); i++ ) { 
		char c = ch[i];
		if ( c == '(' || c == ')' || c == ']' || c == '[' || c == '\\' ) {
			ss << '\\';
		}
		ss << c;		
	}
	ss << "]+)";
	std::string pattern = ss.str();
	std::vector<Regex::Result> res;	
	res = Regex::search_idx( std::string("^") + pattern, s );
	if ( res.size() > 0 ) { 
		s.replace(res[0].idx, res[0].str.size(), "");
	}
	res = Regex::search_idx( pattern + "$", s );
	if ( res.size() > 0 ) { 
		s.replace(res[0].idx, res[0].str.size(), "");
	}
	return s;
}
