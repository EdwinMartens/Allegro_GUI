//      Copyright (C) 2016   E.J.M. Martens
//
//      This program is free software; you can redistribute it and/or
//      modify it under the terms of the GNU General Public License
//      as published by the Free Software Foundation; either version 2
//      of the License, or (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.


#ifndef _MATH_VECTORS
#define _MATH_VECTORS

#include <math.h>
#include <stdlib.h>
#include <time.h>


using namespace std;

class Vector2D
{
    public:

    // Constructors
    Vector2D();
    Vector2D(double a_dX, double a_dY);

    // Copy constructor
    Vector2D(const Vector2D & a_rVector);

    // destructor
    ~Vector2D();

    // Functions
    void rotate(double angle);
    double magnitude();
    void normalise();
    double crossproduct(const Vector2D & a_rVector);
    double dotproduct(const Vector2D & a_rVector);
    void Limit(double a_dMaxMagnitude);

    // Operators
    Vector2D operator*(double a_dScalar);
    Vector2D operator/(double a_dScalar);
    Vector2D operator+(const Vector2D & a_rVector);
    Vector2D operator-(const Vector2D & a_rVector);

    Vector2D & operator+=(const Vector2D & a_Vector);
    Vector2D & operator-=(const Vector2D & a_Vector);
    Vector2D & operator*=(double a_dScalar);
    Vector2D & operator/=(double a_dScalar);

    Vector2D & operator=(const Vector2D & a_rVector);

    double GetX();
    double GetY();

    void SetX(double a_dX);
    void SetY(double a_dY);

protected:



private:
    double m_dX;
    double m_dY;
};



double Random(int a_nMin, int a_nMax);









#endif
