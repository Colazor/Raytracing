#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "..\..\Math\src\Vector2.h"
#include "..\..\Math\src\Vector3.h"
#include "..\..\Math\src\Vector4.h"
#include "..\..\Math\src\Matrix3.h"
#include "..\..\Math\src\Matrix4.h"
#include "..\..\RaytracerApp\src\Ray.cpp"
#include "..\..\RaytracerApp\src\Box.cpp"
#include "..\..\RaytracerApp\src\Shape.cpp"
#include "..\..\RaytracerApp\src\Plane.cpp"
#include "..\..\RaytracerApp\src\Sphere.cpp"
#include "..\..\RaytracerApp\src\Material.h"
#include "..\..\RaytracerApp\src\Texture.h"








TEST_CASE("Testing Vector2 functionality")
{
	SUBCASE("Construction")
	{
		/// Default constructor
		const Vector2 v0;
		CHECK(v0.x == 0.0f);
		CHECK(v0.y == 0.0f);
		/// Constructor from components
		const Vector2 v1(9.1f, -3.0f);
		CHECK(v1.x == 9.1f);
		CHECK(v1.y == -3.0f);

		/// Constructor from components
		const Vector2 v2(4.3f);
		CHECK(v2.x == 4.3f);
		CHECK(v2.y == 4.3f);

		/// Copy construction
		Vector2 v3(v2);
		CHECK(v2.x == v3.x);
		CHECK(v2.y == v3.y);

		/// Zero all the components of the vector
		v3.Clear();
		CHECK(v0.x == v3.x);
		CHECK(v0.y == v3.y);
	}

	SUBCASE("Mathematical operators")
	{
		const Vector2 v0(2.3f, 3.7f);
		const Vector2 v1(-6.6f, 1.2f);
		const float factor = 3.5f;
		Vector2 v2;

		/// Returns the value of the given vector added to this.
		v2 = v0 + v1;
		CHECK(v2.x == v0.x + v1.x);
		CHECK(v2.y == v0.y + v1.y);

		/// Returns the value of the given vector subtracted from this.
		v2 = v0 - v1;
		CHECK(v2.x == v0.x - v1.x);
		CHECK(v2.y == v0.y - v1.y);

		SUBCASE("Vector and scalar multiplication.")
		{
			/// Returns a copy of this vector scaled the given value.
			v2 = v1 * factor;
			CHECK(v2.x == v1.x * factor);
			CHECK(v2.y == v1.y * factor);

			/// Returns a new vector being the result of a float value multiplied on right hand side with a vector
			v2 = factor * v0;
			CHECK(v2.x == v0.x * factor);
			CHECK(v2.y == v0.y * factor);
		}

		/// Returns a copy of this vector scaled the given value.
		v2 = v0 / factor;
		CHECK(v2.x == v0.x / factor);
		CHECK(v2.y == v0.y / factor);

		SUBCASE("Dot product calculation.")
		{
			/// Calculates and returns the dot product of this vector with the given vector.
			const float dot = v0 * v1;
			CHECK(-10.74f == dot);

			const float calculatedDot = v0.Dot(v1);
			CHECK(dot == calculatedDot);
		}

		/// Adds the given vector to this.
		SUBCASE("Adds the given vector to this.")
		{
			Vector2 v3(3.0f, -4.0f);
			v3 += v0;
			CHECK(v3.x == v0.x + 3.0f);
			CHECK(v3.y == v0.y + -4.0f);
		}

		/// Subtracts the given vector from this
		SUBCASE("Subtracts the given vector from this.")
		{
			Vector2 v3(3.0f, -4.0f);
			v3 -= v1;
			CHECK(v3.x == 3.0f - v1.x);
			CHECK(v3.y == -4.0f - v1.y);
		}

		/// Multiplies this vector by the given scalar
		SUBCASE("Multiplies this vector by the given scalar.")
		{
			Vector2 v3(3.0f, -4.0f);
			v3 *= factor;
			CHECK(v3.x == 3.0f * factor);
			CHECK(v3.y == -4.0f * factor);
		}
	}

	SUBCASE("Logical operators")
	{
		/// Checks if the two vectors have identical components
		const float x = 2.93f;
		const float y = 4.39f;
		Vector2 v0(x, y);
		Vector2 v1(x, y);
		Vector2 v2(y, x);

		CHECK(v0 == v1);
		CHECK(v2 != v0);
	}

	SUBCASE("Length operations")
	{
		Vector2 v0(3.0f, 4.0f);

		/// Gets the magnitude of this vector
		const float vectorLenght = v0.Magnitude();
		CHECK(vectorLenght == 5.0f);

		/// Gets the squared magnitude of this vector
		const float vectorLenghtSq = v0.SquareMagnitude();
		CHECK(vectorLenghtSq == 25.0f);

		/// Limits the size of the vector to the given maximum
		v0.Trim(2.5f);
		CHECK(2.5f == v0.Magnitude());

		/// Returns the normalised version of a vector
		Vector2 v1 = v0;
		Vector2 v2 = v1.Unit();
		CHECK(v1 == v0);
		CHECK(1.0f == v2.Magnitude());
			
		/// Turns a non-zero vector into a vector of unit length
		v0.Normalize();
		CHECK(1.0f == v0.Magnitude());
	}
}

TEST_CASE("Testing Vector3 functionality")
{
	SUBCASE("Construction")
	{
		/// The default constructor creates a zero vector.
		const Vector3 v0;
		CHECK(v0.x == 0.0f);
		CHECK(v0.y == 0.0f);
		CHECK(v0.z == 0.0f);
		/// Creates a vector with the given components
		const Vector3 v1(9.1f, -3.0f, 2.0f);
		CHECK(v1.x == 9.1f);
		CHECK(v1.y == -3.0f);
		CHECK(v1.z == 2);
		/// Zero all the components of the vector
		Vector3 v2 = v1;
		v2.Clear();
		CHECK(v2.x == v0.x);
		CHECK(v2.y == v0.y);
		CHECK(v2.z == v0.z);

	}

	SUBCASE("Mathematical operators")
	{
		const Vector3 v0(2.3f, 3.7f, 3.5f);
		const Vector3 v1(-6.6f, 1.2f, 2.7f);
		const Vector3 v2(1, 2, 3);
		const Vector3 v4(3, 2, 1);
		const float factor = 3.5f;
		Vector3 v3;
		Vector3 temp;

		/// Returns the value of the given vector added to this.
		v3 = v0 + v1;
		CHECK(v3.x == v0.x + v1.x);
		CHECK(v3.y == v0.y + v1.y);
		CHECK(v3.z == v0.z + v1.z);
		/// Returns the value of the given vector subtracted from this
		v3 = v0 - v1;
		CHECK(v3.x == v0.x - v1.x);
		CHECK(v3.y == v0.y - v1.y);
		CHECK(v3.z == v0.z - v1.z);
		/// Returns a copy of this vector scaled the given value
		temp = v3;
		v3 = v3 * factor;
		CHECK(v3.x == temp.x * factor);
		CHECK(v3.y == temp.y * factor);
		CHECK(v3.z == temp.z * factor);
		temp.Clear();
		/// Returns a copy of this vector scaled the inverse of the value
		temp = v3;
		float tempfactor = 1 / factor;
		v3 = v3 * tempfactor;
		CHECK(v3.x == temp.x * tempfactor);
		CHECK(v3.y == temp.y * tempfactor);
		CHECK(v3.z == temp.z * tempfactor);
		tempfactor = NULL;
		temp.Clear();
		/// Returns the negative this vector
		temp = v3;
		v3 = -1.f * v3;
		CHECK(v3.x == temp.x * -1);
		CHECK(v3.y == temp.y * -1);
		CHECK(v3.z == temp.z * -1);
		temp.Clear();

		/// Adds the given vector to this
		temp = v3;
		v3 += v2;
		CHECK(v3.x == temp.x + v2.x);
		CHECK(v3.y == temp.y + v2.y);
		CHECK(v3.z == temp.z + v2.z);
		temp.Clear();

		/// Subtracts the given vector from this
		temp = v3;
		v3 -= v2;
		CHECK(v3.x == temp.x - v2.x);
		CHECK(v3.y == temp.y - v2.y);
		CHECK(v3.z == temp.z - v2.z);
		temp.Clear();
		/// Multiplies this vector by the given scalar
		temp = v3;
		v3 *= 5;
		CHECK(v3.x == temp.x * 5);
		CHECK(v3.y == temp.y * 5);
		CHECK(v3.z == temp.z * 5);
		temp.Clear();
		SUBCASE("Vector products")
		{
			/// Calculates and returns the dot product of this with the given vector
			float result = v4.Dot(v2);
			CHECK(result == v4.x * v2.x + v4.y * v2.y + v4.z * v2.z);

			/// Calculates and returns the cross product of this vector with the given vector
			v3 = v4.Cross(v2);
			CHECK(v3.x == 4.0f);
			CHECK(v3.y == -8.0f);
			CHECK(v3.z == 4.0f);
		}

		SUBCASE("Length operations")
		{
			///  Gets the magnitude of this vector
			CHECK(v4.Magnitude() == sqrtf(14));
			///  Gets the squared magnitude of this vector
			CHECK(v4.SquareMagnitude() == 14);
			/// Turns a non-zero vector into a vector of unit length
			v3 = v3.Unit();
			CHECK(v3.Magnitude() == 1);
			/// Returns the normalised version of a vector
			v3.Normalize();
			CHECK(v3.Magnitude() == 1);
		}
	}

	SUBCASE("Logical operations")
	{
		const Vector3 vec(0, 0, 0);
		const Vector3 vec1(0, 0, 0);
		const Vector3 vec2(0, 0, 1);
		/// Checks if the two vectors have identical components
		CHECK(vec == vec1);

		/// Checks if the two vectors have non-identical components
		CHECK(vec != vec2);

	}
}

TEST_CASE("Testing Matrix44 functionality")
{
	SUBCASE("Construction")
	{	
		Matrix4 Test(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 4);
		CHECK(Test.z4 == 2);
		/// Construct a new matrix from explicit values
		/// Construct a new identity matrix
		Matrix4 I(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		Matrix4 Test2;
		CHECK(I == Test2);

		/// Creates an identity matrix
		Test2 = Test2.Identity();
		CHECK(Test2 == I);

		/// Creates a translation matrix
		Matrix4 T = Matrix4::Translate(2);
		CHECK(T.w2 == 2);

		/// Creates a scale matrix
		Matrix4 S = Matrix4::Scale(Vector3(2, 3, 4));
		CHECK(S.x1 == 2);
		CHECK(S.y2 == 3);
		CHECK(S.z3 == 4);

		/// Creates a uniform scale matrix
		Matrix4 S2 = Matrix4::Scale(2);
		CHECK(S2.x1 == 2);
		CHECK(S2.y2 == 2);
		CHECK(S2.z3 == 2);

		/// Creates a rotation matrix around an arbitrary axis (angle in radians)
		/// Creates a rotation matrix around the x axis (angle in radians)
		/// Creates a rotation matrix around the y axis (angle in radians)
		/// Creates a rotation matrix around the z axis (angle in radians)
		/// Creates an orthographic projection matrix
		/// Creates a frustum projection matrix
		/// Creates a perspective projection matrix from camera settings
		/// Creates a look at matrix, usually a view matrix  
	}

	SUBCASE("Mathematical operations")
	{
		/// Matrix addition
		/// Matrix subtraction
		/// Matrix multiplication

		SUBCASE("Inversion")
		{
			/// Get the determinant of this matrix
			/// Inverts this matrix
			/// Transposes this matrix
		}
	}

	SUBCASE("Transformation")
	{
		/// Transform the given vector by this matrix.
		/// Transform the direction vector of this matrix
	}

	/// Retrieve translation part of the matrix
	/// Set the translation of the matrix
	/// Get the x orientation axis 
	/// Get the y orientation axis 
	/// Get the z orientation axis 

	/// Sets the orientation of the matrix to the orthogonal basis vector
}
TEST_CASE("Ray Checks")
{
	SUBCASE("Reflection")
	{
		Ray Tester(Vector3(0.f, 0.f, 0.f), Vector3(0.0f, 0.0f, 1.0f));
		// A situation in which a ray going directly onwards hits a box straight onwards - this should bounce back
		// As such the reflection direction should be the same as the normal of the surface
		Vector3 ReflectionDir = Vector3::Reflect(Tester.get_Direction(), Vector3(0.f, 0.f, -1.f));
		Vector3 ExpectedResult = Vector3(0.0f, 0.0f, -1.0f);
		CHECK(ReflectionDir == ExpectedResult);
	}
}

TEST_CASE("Simple Raytracing Objects")
{
	SUBCASE("Box")
	{
		Ray Tester(Vector3(2.f, 2.f, 0.f), Vector3(0.0f, 0.0f, 1.0f));
		Box MyTestBox(Vector3(0.f, 0.f, 10.0f), Vector3(4.0f, 4.0f, 14.0f), nullptr, nullptr, nullptr);
		float t = 150.0f;
		bool Hit = MyTestBox.RayIntersect(Tester, t);
		CHECK(Hit);
		CHECK(t == 10.0f);
	}

	SUBCASE("Sphere")
	{
		Ray Tester(Vector3(0.f, 0.f, 0.f), Vector3(0.0f, 0.0f, 1.0f));
		Sphere MyTestSphere(Vector3(0.f, 0.f, 10.0f), nullptr, nullptr, nullptr, 4.0f);
		float t = 150.0f;
		bool Hit = MyTestSphere.RayIntersect(Tester, t);
		CHECK(Hit);
		CHECK(t == 6.0f);
	}

	SUBCASE("Plane")
	{
		Ray Tester(Vector3(0.f, -5.f, 0.f), Vector3(0.0f, 1.0f, 1.0f));
		Plane MyTestPlane(Vector3(0.f, 0.f, 0.f), Vector3(0.0f, -1.0f, 0.0f), nullptr, nullptr, nullptr);
		float t = 150.0f;
		bool Hit = MyTestPlane.RayIntersect(Tester, t);
		CHECK(Hit);
		CHECK(t == 5.0f);
	}


}
