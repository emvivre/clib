/*
  ===========================================================================

  Copyright (C) 2014 Emvivre

  This file is part of GLM_UTIL.

  GLM_UTIL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  GLM_UTIL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with GLM_UTIL.  If not, see <http://www.gnu.org/licenses/>.

  ===========================================================================
*/

#ifndef _GLM_UTIL_H_
#define _GLM_UTIL_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <iostream>
#define GLM_FORCE_RADIANS
#include <glm/gtx/rotate_vector.hpp>

namespace GLMUtil
{
	template <class T>
	class Compare
	{
	public:
		bool operator()(const T& v0, const T& v1) const;
	};
	
	template <> 
	class Compare<glm::vec3> {
	public:
		bool operator()(const glm::vec3& v0, const glm::vec3& v1) const {
			if ( v0.x < v1.x ) return true;
			if ( v0.x > v1.x ) return false;
			if ( v0.y < v1.y ) return true;
			if ( v0.y > v1.y ) return false;
			if ( v0.z < v1.z ) return true;
			if ( v0.z > v1.z ) return false;
			return false;
		}
	};
	
	template <> 
	class Compare<glm::ivec3> {
	public:
		bool operator()(const glm::ivec3& v0, const glm::ivec3& v1) const {
			if ( v0.x < v1.x ) return true;
			if ( v0.x > v1.x ) return false;
			if ( v0.y < v1.y ) return true;
			if ( v0.y > v1.y ) return false;
			if ( v0.z < v1.z ) return true;
			if ( v0.z > v1.z ) return false;
			return false;
		}
	};

	inline glm::vec3 vec3( const float* f ) {
		return glm::vec3( f[0], f[1], f[2] );
	}
	
	inline glm::vec4 vec4( const float* f ) {
		return glm::vec4( f[0], f[1], f[2], f[3] );
	}
	
	inline glm::mat4 mat4( const float* f ) {
		glm::mat4 m;
		for ( int x = 0; x < 4; x++ ) {
			for ( int y = 0; y < 4; y++ ) {
				m[x][y] = *f++;
			}
		}
		return m;
	}
	
	inline glm::mat4 mat4( const glm::mat3& m3 ) {
		glm::mat4 m4;
		for ( int y = 0; y < 3; y++ ) m4[y][0] = 0;
		for ( int x = 0; x < 3; x++ ) m4[0][x] = 0;
		m4[3][3] = 1;
		for ( int y = 0; y < 3; y++ ) {
			for ( int x = 0; x < 3; x++ ) { 
				m4[y][x] = m3[y][x];
			}
		}
		return m4;
	}
	
	inline void show(const glm::mat3& m) {
		for ( int y = 0; y < 3; y++ ) { 
			for ( int x = 0; x < 3; x++ ) { 
				std::cout << m[y][x] << " ";
			}
			std::cout << "\n";
		}
	}

	inline void show(const glm::mat4& m) {
		for ( int y = 0; y < 4; y++ ) { 
			for ( int x = 0; x < 4; x++ ) { 
				std::cout << m[y][x] << " ";
			}
			std::cout << "\n";
		}
	}

	inline void show( const glm::vec3& v) {
		std::cout << v.x << " " << v.y << " " << v.z << "\n";
	}

	inline void show( const glm::vec4& v) {
		std::cout << v.x << " " << v.y << " " << v.z << " " << v.w << "\n";
	}	
	
	inline glm::vec3 row(const glm::mat3& m, int c) {
		return glm::row(m, c);
	}
	
	inline glm::vec3 col(const glm::mat3& m, int c) {
		glm::vec3 v;
		for ( int i = 0; i < 3; i++ ) {
			v[i] = m[i][c];
		}
		return v;
	}
	inline glm::vec3 rot2angles( const glm::mat3& m ) {
		float rx = std::atan2( m[1][2], m[2][2] );
		float ry = std::atan2( -m[0][2], std::sqrt( m[1][2] * m[1][2] + m[2][2] * m[2][2] ) );
		float rz = std::atan2( m[0][1], m[0][0] );
		return glm::vec3( rx, ry, rz );		
	}
}

#endif /* !_GLM_UTIL_H_ */
