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
#include "FGengine/structures/frametime.hpp"
using namespace FGengine;

Frametime::Frametime(): frametime(0) {}
Frametime::Frametime(const DataType& frametime): frametime(frametime) {}
Frametime::Frametime(const FPS& fps): frametime(double(ratio::num) * fps.toDataType()/ratio::den) {}
Frametime::Frametime(const std::chrono::duration<DataType, ratio>& duration): frametime(duration.count()) {}
const Frametime::DataType& Frametime::toDataType() const { return frametime; }

void Frametime::operator=(const std::chrono::duration<DataType, ratio>& duration){
	frametime = duration.count();
}

bool Frametime::operator==(const Frametime& frametime) const{
	return this->frametime == frametime.frametime;
}
bool Frametime::operator!=(const Frametime& frametime) const{
	return this->frametime != frametime.frametime;
}
bool Frametime::operator>(const Frametime& frametime) const{
	return this->frametime > frametime.frametime;
}
bool Frametime::operator<(const Frametime& frametime) const{
	return this->frametime < frametime.frametime;
}
bool Frametime::operator>=(const Frametime& frametime) const{
	return this->frametime >= frametime.frametime;
}
bool Frametime::operator<=(const Frametime& frametime) const{
	return this->frametime <= frametime.frametime;
}

Frametime Frametime::operator+(const Frametime& frametime) const{
	return this->frametime + frametime.frametime;
}
Frametime Frametime::operator-(const Frametime& frametime) const{
	return this->frametime - frametime.frametime;
}
Frametime Frametime::operator*(const Frametime& frametime) const{
	return this->frametime * frametime.frametime;
}
Frametime Frametime::operator/(const Frametime& frametime) const{
	return this->frametime / frametime.frametime;
}
Frametime Frametime::operator+=(const Frametime& frametime){
	return this->frametime += frametime.frametime;
}
Frametime Frametime::operator-=(const Frametime& frametime){
	return this->frametime -= frametime.frametime;
}
Frametime Frametime::operator*=(const Frametime& frametime){
	return this->frametime *= frametime.frametime;
}
Frametime Frametime::operator/=(const Frametime& frametime){
	return this->frametime /= frametime.frametime;
}