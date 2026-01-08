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
#include "point.hpp"

template<typename PosType, class Base>
class VertexPosition{
protected:
	VertexPosition(PosType position){
		SetPosition(position);
	}
	VertexPosition(){}

public:
	using DataType = PosType;

protected:

	DataType position;
	static inline const short offset = offsetof(Base, position);

public:
	void SetPosition(PosType newposition){
		this->position = newposition;
	}
	PosType& GetPosition(){
		return this->position;
	}
	static short GetOffset(){
		return VertexPosition::offset;
	}
	static short GetLength(){
		return PosType::length();
	}
};

template<typename ColType, typename Base>
class VertexColor{
protected:
	VertexColor(ColType color){
		SetColor(color);
	}
	VertexColor(){}

public:
	using DataType = ColType;

protected:
	DataType color;
	static inline const short offset = offsetof(Base, color);

public:
	void SetColor(ColType newcolor){
		this->color = newcolor;
	}
	ColType& GetColor(){
		return this->color;
	}
	static short GetOffset(){
		return VertexColor::offset;
	}
	static short GetLength(){
		return ColType::length();
	}
};

template<typename NormalType, typename Base>
class VertexNormal{

protected:
	VertexNormal(NormalType normal){
		SetNormal(normal);
	}
	VertexNormal(){}

public:
	using DataType = NormalType;

protected:
	DataType normal;
	static inline const short offset = offsetof(Base, normal);

public:
	void SetNormal(NormalType newnormal){
		this->normal = newnormal;
	}
	NormalType& GetNormal(){
		return this->normal;
	}
	static short GetOffset(){
		return VertexNormal::offset;
	}
	static short GetLength(){
		return NormalType::length();
	}
};

template<typename Pos, typename Col, typename Normal = Point3d>
class Vertex: public VertexPosition<Pos,Vertex<Pos,Col,Normal>>, public VertexColor<Col, Vertex<Pos,Col,Normal>>, public VertexNormal<Normal, Vertex<Pos,Col,Normal>>{
public:
	Vertex(Pos pos, Col col, Normal normal):
		Vertex::VertexPosition(pos),
		Vertex::VertexColor(col),
		Vertex::VertexNormal(normal)
	{}
	Vertex(){}

	static int GetStride(){
		return stride;
	}

private:

	static const int stride = sizeof(Vertex);

	static inline GLuint vao;
	static inline bool ready;
};

using Vertex2d = Vertex<Point2d,Color3d,Point2d>; /* Note: Normals in 2d space are useless. They're still here, because I don't know exactly what to do with them, should they be here or not. */
using Vertex3d = Vertex<Point3d,Color3d,Point3d>;