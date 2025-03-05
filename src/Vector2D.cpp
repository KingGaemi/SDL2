#include "Vector2D.h"




Vector2D::Vector2D()

{
	x = 0.0f;
	y = 0.0f;


}


Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}


Vector2D::Vector2D(Dir dir)
{	
	if(dir == Dir::Left){

		this->x = -1;
		this->y = 0;

	}


	if(dir == Dir::Right){

		this->x = 1;
		this->y = 0;
		
	}

	if(dir == Dir::Up){

		this->x = 0;
		this->y = -1;
		
	}

	if(dir == Dir::Down){

		this->x = 0;
		this->y = 1;
		
	}


}


Vector2D& Vector2D::Add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}


Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}


Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Subtract(v2);
}


Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.Multiply(v2);
}


Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.Divide(v2);
}


Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->Divide(vec);
}


Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}

Vector2D& Vector2D::operator*(const float& f)
{
	this->x *= f;
	this->y *= f;

	return *this;
}


// Vector2D& Vector2D::operator*=(const int& i)
// {
// 	this->x *= i;
// 	this->y *= i;

// 	return *this;
// }

bool Vector2D::operator==(const Vector2D& other) const {
    return (x == other.x) && (y == other.y);
}

bool Vector2D::operator!=(const Vector2D& other) const {
    return !(*this == other);  // == 연산자를 활용
}



Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;

	return *this;
}



std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{

	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}

