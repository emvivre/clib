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

#include "image.h"
#include "string_util.h"
#include <map>

typedef gdImagePtr (*GdImageCreatePtrFct)(FILE*);
static std::map<std::string, GdImageCreatePtrFct> img_init = { 
	{ "png", gdImageCreateFromPng   },
	{ "gif", gdImageCreateFromGif   },
	{ "wbmp", gdImageCreateFromWBMP },
	{ "jpeg", gdImageCreateFromJpeg },
	{ "jpg", gdImageCreateFromJpeg  },
	{ "webp", gdImageCreateFromWebp },
	{ "tiff", gdImageCreateFromTiff },
	{ "tga", gdImageCreateFromTga   },
	{ "bmp", gdImageCreateFromBmp   },
};

typedef gdImagePtr (*GdImageCreateFromMemPtrFct)(int sz, void* ptr);
std::map<std::string, GdImageCreateFromMemPtrFct> img_init_from_mem = {
	{ "png", gdImageCreateFromPngPtr   },
	{ "gif", gdImageCreateFromGifPtr   },
	{ "wbmp", gdImageCreateFromWBMPPtr },
	{ "jpeg", gdImageCreateFromJpegPtr },
	{ "jpg", gdImageCreateFromJpegPtr  },
	{ "webp", gdImageCreateFromWebpPtr },
	{ "tiff", gdImageCreateFromTiffPtr },
	{ "tga", gdImageCreateFromTgaPtr   },
	{ "bmp", gdImageCreateFromBmpPtr   },
};

typedef void (*GdImageSavePtrFct)(gdImagePtr im, FILE * outFile);
static std::map<std::string, GdImageSavePtrFct> img_save = {
	{ "png", gdImagePng   },
	{ "gif", gdImageGif   },
	{ "wbmp", [](gdImagePtr im, FILE *out) { gdImageWBMP(im, 0, out); } },
	{ "jpeg", [](gdImagePtr im, FILE *out) { gdImageJpeg(im, out, 10); } },
	{ "jpg", [](gdImagePtr im, FILE *out) { gdImageJpeg(im, out, 10); } },
	{ "webp", gdImageWebp },
	{ "tiff", gdImageTiff },
	{ "bmp", [](gdImagePtr im, FILE *out) { gdImageBmp(im, out, 0); } },
};

void Image::save( const std::string& img_dst ) const {
	std::string img_dst_ext = StringUtil::extension(img_dst);
	if ( img_save.count( img_dst_ext ) == 0 ) {
		throw UnknownExtension();
	}
	gdImagePtr gd = gdImageCreateTrueColor( this->width(), this->height() );
	for ( int y = 0; y < h; y++ ) {
		for ( int x = 0; x < w; x++ ) {
			gdImageSetPixel( gd, x, y, gdTrueColor( this->red(x,y), this->green(x,y), this->blue(x,y) ) );
		}
	}
	FILE* fd = fopen( img_dst.c_str(), "w+");
	if ( fd == NULL ) {
		throw UnableToOpenFile();
	}	
	img_save[img_dst_ext]( gd, fd );
	fclose(fd);
}

void Image::init_from_gd_ptr( gdImagePtr gd )
{
	this->w = gdImageSX(gd);
	this->h = gdImageSY(gd);
	this->img = new uint32_t[this->w * this->h];
	for ( int y = 0; y < h; y++ ) {
		for ( int x = 0; x < w; x++ ) {
			this->img[y * w + x] = gdImageGetTrueColorPixel(gd, x, y);
		}
	}	
}

Image::Image( const Image& im ) : img(new std::uint32_t[ im.w*im.h ]), w(im.w), h(im.h) {
	for ( int y = 0; y < this->h; y++ ) {
		for ( int x = 0; x < this->w; x++ ) {
			this->img[ y*this->w + x ] = im.img[ y*this->w + x ];
		}
	}
}

Image::Image(int width, int height ) : img(new std::uint32_t[ width*height ]), w(width), h(height) { }

Image::Image(int* data, int width, int height ) : Image( width, height )
{	
	for ( int i = 0; i < this->w * this->h; i++ ) {
		this->img[ i ] = data[ i ];
	}	
}

Image::Image(void* data, size_t sz, std::string ext )
{
	ext = StringUtil::lower( ext );
	if ( img_init_from_mem.find(ext) == img_init_from_mem.end() ) throw UnknownExtension();
	gdImagePtr gd = img_init_from_mem[ext](sz, data);	
	this->init_from_gd_ptr( gd );
	gdImageDestroy(gd);
}

Image::Image(std::string file)
{
	std::string ext = StringUtil::lower( StringUtil::extension(file) );
	if ( img_init.find(ext) == img_init.end() ) throw UnknownExtension();
	FILE* f = fopen(file.c_str(), "r");
	if ( f == NULL ) throw UnableToOpenFile();
	gdImagePtr gd = img_init[ext](f);
	fclose(f);
	this->init_from_gd_ptr( gd );	
	gdImageDestroy(gd);
}
