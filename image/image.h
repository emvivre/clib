/*
  ===========================================================================

  Copyright (C) 2014 Emvivre

  This file is part of IMAGE.

  IMAGE is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  IMAGE is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with IMAGE.  If not, see <http://www.gnu.org/licenses/>.

  ===========================================================================
*/

#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <gd.h>
#include <string>
#include <glm/glm.hpp>
#include <cstdint>

class Image
{
	std::uint32_t* img;  // rgba buffer
	int w, h;

	void init_from_gd_ptr(gdImagePtr);
public:
	class UnknownExtension {};
	class UnableToOpenFile {};

	~Image() { delete[] img; }
	Image( const Image& im );
	Image(std::string file);
	Image(int width, int height);
	Image(int* data, int width, int height );
	Image( void* data, size_t sz, std::string ext );
	int width() const { return w; }
	int height() const { return h; }
	int size() const { return w * h * 4; }
	const std::uint32_t* ptr() const { return img; }
        std::uint32_t* ptr() { return img; }
	int at(int x, int y) const { return img[y * w + x]; }
	glm::vec3 operator()(int x, int y) const { return glm::vec3(red(x,y), green(x,y), blue(x,y)); }
	void set(int x, int y, glm::vec3 c) { this->img[y*this->width() + x] = gdTrueColor(int(c.r), int(c.g), int(c.b)); }
	void set(int x, int y, glm::ivec3 c) { this->img[y*this->width() + x] = gdTrueColor(int(c.r), int(c.g), int(c.b)); }
	unsigned char red(int x, int y) const { return gdTrueColorGetRed(this->at(x,y)); }
	unsigned char green(int x, int y) const { return gdTrueColorGetGreen(this->at(x,y)); }
	unsigned char blue(int x, int y) const { return gdTrueColorGetBlue(this->at(x,y)); }
	void save(const std::string& img_dst) const;
};

#endif /* !_IMAGE_H_ */
