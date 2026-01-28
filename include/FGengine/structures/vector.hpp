// FGengine - a free and open-source library for game development
// Copyright (C) 2025, 2026 Gmunamax <https://github.com/Gmunamax/FGengine>

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, see <https://www.gnu.org/licenses/>.
#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace _Vector{


	enum class VectorType{
		Point,
		Color,
		Size,
		Indice,
	};

	using length_t = char;
	constexpr char qualifier = glm::packed;

	template<typename DataType>
	struct VectorDataType{
		static constexpr GLenum gldatatype();
	};

	template<>
	inline constexpr GLenum VectorDataType<short>::gldatatype() {return GL_SHORT;}

	template<>
	inline constexpr GLenum VectorDataType<int>::gldatatype() {return GL_INT;}

	template<>
	inline constexpr GLenum VectorDataType<float>::gldatatype() {return GL_FLOAT;}

	template<>
	inline constexpr GLenum VectorDataType<double>::gldatatype() {return GL_DOUBLE;}

	template<>
	inline constexpr GLenum VectorDataType<unsigned int>::gldatatype() {return GL_UNSIGNED_INT;}

	template<>
	inline constexpr GLenum VectorDataType<unsigned short>::gldatatype() {return GL_UNSIGNED_SHORT;}

	template<>
	inline constexpr GLenum VectorDataType<unsigned char>::gldatatype() {return GL_UNSIGNED_BYTE;}

	template<length_t Length, typename DataType, VectorType VectorPurpose>
	struct VectorData{
		DataType value[Length];
	};

	template<typename DataType>
	struct VectorData<1, DataType, VectorType::Point>{
		union{
			DataType value;
			DataType x;
		};
	};

	template<typename DataType>
	struct VectorData<2, DataType, VectorType::Point>{
		union{
			DataType value[2];
			struct{
				DataType x;
				DataType y;
			};
		};
	};

	template<typename DataType>
	struct VectorData<3, DataType, VectorType::Point>{
		union{
			DataType value[3];
			struct{
				DataType x;
				DataType y;
				DataType z;
			};
		};
	};

	template<typename DataType>
	struct VectorData<4, DataType, VectorType::Point>{
		union{
			DataType value[4];
			struct{
				DataType x;
				DataType y;
				DataType z;
				DataType w;
			};
		};
	};

	template<typename DataType>
	struct VectorData<3, DataType, VectorType::Color>{
		union{
			DataType value[3];
			struct{
				DataType r;
				DataType g;
				DataType b;
			};
		};
	};

	template<typename DataType>
	struct VectorData<4, DataType, VectorType::Color>{
		union{
			DataType value[4];
			struct{
				DataType r;
				DataType g;
				DataType b;
				DataType a;
			};
		};
	};

	template<typename DataType>
	struct VectorData<1, DataType, VectorType::Size>{
		union{
			DataType value;
			DataType w;
		};
	};

	template<typename DataType>
	struct VectorData<2, DataType, VectorType::Size>{
		union{
			DataType value[2];
			struct{
				DataType w;
				DataType h;
			};
		};
	};

	template<typename DataType>
	struct VectorData<3, DataType, VectorType::Size>{
		union{
			DataType value[3];
			struct{
				DataType w;
				DataType h;
				DataType d;
			};
		};
	};

	template<length_t Length, typename DataType, VectorType VectorPurpose>
	struct VectorMethods: VectorData<Length, DataType, VectorPurpose>{
		const DataType& operator[](unsigned index) const{
			return VectorMethods::value[index];
		}
		DataType& operator[](const unsigned index){
			return VectorMethods::value[index];
		}
	};

	template<length_t Length, typename DataType, VectorType VectorPurpose>
	struct Vector: VectorDataType<DataType>, VectorMethods<Length, DataType, VectorPurpose>{

	};

	template<typename DataType, VectorType VectorPurpose>
	struct Vector<1, DataType, VectorPurpose>: VectorDataType<DataType>, VectorMethods<1, DataType, VectorPurpose>{

		Vector() = default;
		Vector(DataType value) {
			Vector::value = value;
		}
		
		static inline constexpr length_t length() {return 1;}
		glm::vec<1, DataType> toGlm() {return {this->value};}

		bool operator==(Vector<1, DataType, VectorPurpose> value){
			return Vector::value == value.value;
		}
		bool operator!=(Vector<1, DataType, VectorPurpose> value){
			return Vector::value == value.value;
		}
		bool operator==(DataType value){
			return Vector::value == value.value;
		}
		bool operator!=(DataType value){
			return Vector::value != value.value;
		}
		Vector operator+(Vector value){
			return Vector::value + value;
		}
	};

	template<typename DataType, VectorType VectorPurpose>
	struct Vector<2, DataType, VectorPurpose>: VectorDataType<DataType>, VectorMethods<2, DataType, VectorPurpose>{

		Vector() = default;
		Vector(DataType value){
			Vector::value[0] = value;
			Vector::value[1] = value;
		}
		Vector(DataType v1, DataType v2){
			Vector::value[0] = v1;
			Vector::value[1] = v2;
		}

		static inline constexpr length_t length() {return 2;}
		glm::vec<2, DataType> toGlm() {return {this->value[0], this->value[1]};}

		bool operator==(Vector<2, DataType, VectorPurpose> value){
			return 
				Vector::value[0] == value.value[0] and 
				Vector::value[1] == value.value[1];
		}
		bool operator!=(Vector<2, DataType, VectorPurpose> value){
			return 
				Vector::value[0] != value.value[0] or
				Vector::value[1] != value.value[1];
		}
		Vector operator+(Vector value){
			return {Vector::value[0] + value.value[0], 
					Vector::value[1] + value.value[1]};
		}
	};

	template<typename DataType, VectorType VectorPurpose>
	struct Vector<3, DataType, VectorPurpose>: VectorDataType<DataType>, VectorMethods<3, DataType, VectorPurpose>{

		Vector() = default;
		Vector(DataType value){
			Vector::value[0] = value;
			Vector::value[1] = value;
			Vector::value[2] = value;
		}
		Vector(DataType v1, DataType v2, DataType v3){
			Vector::value[0] = v1;
			Vector::value[1] = v2;
			Vector::value[2] = v3;
		}

		static inline constexpr length_t length() {return 3;}
		glm::vec<3, DataType> toGlm() {return {this->value[0], this->value[1], this->value[2]};}

		bool operator==(Vector<3, DataType, VectorPurpose> value){
			return
				Vector::value[0] == value.value[0] and
				Vector::value[1] == value.value[1] and
				Vector::value[2] == value.value[2];
		}
		bool operator!=(Vector<3, DataType, VectorPurpose> value){
			return
				Vector::value[0] != value.value[0] or
				Vector::value[1] != value.value[1] or
				Vector::value[2] != value.value[2];
		}
		Vector operator+(Vector value){
			return {Vector::value[0] + value.value[0], 
					Vector::value[1] + value.value[1], 
					Vector::value[2] + value.value[2]};
		}
		Vector operator*(Vector value){
			return {Vector::value[0] * value.value[0], 
					Vector::value[1] * value.value[1], 
					Vector::value[2] * value.value[2]};
		}
	};

	template<typename DataType, VectorType VectorPurpose>
	struct Vector<4, DataType, VectorPurpose>: VectorDataType<DataType>, VectorMethods<4, DataType, VectorPurpose>{
		
		Vector() = default;
		Vector(DataType value){
			Vector::value[0] = value;
			Vector::value[1] = value;
			Vector::value[2] = value;
			Vector::value[3] = value;
		}
		Vector(DataType v1, DataType v2, DataType v3, DataType v4){
			Vector::value[0] = v1;
			Vector::value[1] = v2;
			Vector::value[2] = v3;
			Vector::value[3] = v4;
		}

		static inline constexpr length_t length() {return 4;}
		glm::vec<4, DataType> toGlm() {return {this->value[0], this->value[1], this->value[2], this->value[3]};}

		bool operator==(Vector<4, DataType, VectorPurpose> value){
			return
				Vector::value[0] == value.value[0] and
				Vector::value[1] == value.value[1] and
				Vector::value[2] == value.value[2] and
				Vector::value[3] == value.value[3];
		}
		bool operator!=(Vector<4, DataType, VectorPurpose> value){
			return
				Vector::value[0] != value.value[0] or
				Vector::value[1] != value.value[1] or
				Vector::value[2] != value.value[2] or
				Vector::value[3] != value.value[3];
		}
		Vector operator+(Vector value){
			return {Vector::value[0] + value.value[0], 
					Vector::value[1] + value.value[1], 
					Vector::value[2] + value.value[2], 
					Vector::value[3] + value.value[3]};
		}
	};
}