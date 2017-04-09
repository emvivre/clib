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

/**
 * ex pattern:
 *   coco([0-9]+)
 "   coco(.*)
 "   a[0-9]
 "   'a([0-9])
 "   a([0-9]) b(2)
 "   (.*)
 */

#ifndef _REGEX_HPP_
#define _REGEX_HPP_

#include <vector>
#include <string>

class Regex
{
public:
	class ExceptionRegexpCompilationError {};
	static std::vector<std::string> search(std::string pattern, std::string buffer);
	
	struct Result {
		unsigned int idx;
		std::string str;
		Result( unsigned int idx, std::string str ) : idx(idx), str(str) {}
	};
	static std::vector<Result> search_idx(std::string pattern, std::string buffer);
	static std::string strip( const std::string& s_orig, const std::string& ch = " \n\r");
};

#endif /* !_REGEX_HPP_ */
