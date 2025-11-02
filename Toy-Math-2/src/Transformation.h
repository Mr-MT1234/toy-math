#pragma once

#include "VectorOperations.h"
#include "MatrixOperations.h"
#include "QuatronionOperations.h"

namespace Toy::Math
{
	constexpr inline Matrix4f TranslationMatrix(const Vector3f& translation)
	{
		Matrix4f matrix(1.f);

		matrix[0][3] = translation.x;
		matrix[1][3] = translation.y;
		matrix[2][3] = translation.z;

		return matrix;
	}
	constexpr inline Matrix4f TranslationMatrix(float x,float y,float z)
	{
		Matrix4f matrix(1);

		matrix[0][3] = x;
		matrix[1][3] = y;
		matrix[2][3] = z;

		return matrix;
	}

	inline Quatronionf RotationQuat(const Vector3f& axis,float angle)
	{
		float cos = cosf(angle / 2);
		float sin = sinf(angle / 2);
		return { cos,sin * axis };
	}
	inline Quatronionf RotationEuler(const Vector3f& rotation)
	{
		return RotationQuat({0,0,1},rotation.z) * RotationQuat({ 0,1,0 }, rotation.y) * RotationQuat({ 1,0,0 }, rotation.x);
	}
	constexpr inline Matrix4f RotationMatrix(const Quatronionf& r)
	{
		Matrix4f matrix;

		float s = LenghtSq(r);

		matrix[0][0] = 1 - 2 * s * (r.y * r.y + r.z * r.z);	matrix[0][1] = 2 * s * (r.x * r.y - r.z * r.s)    ;	matrix[0][2] = 2 * s * (r.x * r.z + r.y * r.s);
		matrix[1][0] = 2 * s * (r.x * r.y + r.z * r.s)    ;	matrix[1][1] = 1 - 2 * s * (r.x * r.x + r.z * r.z);	matrix[1][2] = 2 * s * (r.y * r.z - r.x * r.s);
		matrix[2][0] = 2 * s * (r.x * r.z - r.y * r.s)    ;	matrix[2][1] = 2 * s * (r.y * r.z + r.x * r.s)    ;	matrix[2][2] = 1 - 2 * s * (r.x * r.x + r.y * r.y);

		return matrix;
	}
	inline Matrix4f RotationMatrix(const Vector3f& r)
	{
		float cosZ = cosf(r.z),
			  cosY = cosf(r.y),
			  cosX = cosf(r.x),
			  sinZ = sinf(r.z),
			  sinY = sinf(r.y),
			  sinX = sinf(r.x);
		
		Matrix4f rotZ(
			{cosZ,-sinZ,0,0},
			{sinZ, cosZ,0,0},
			{0   , 0   ,1,0},
			{0   ,0    ,0,1}
		);
		Matrix4f rotY(
			{ cosY,0,-sinY,0 },
			{ 0   ,1, 0   ,0 },
			{ sinY,0, cosY,0 },
			{ 0   ,0, 0   ,1 }
		);
		Matrix4f rotX(
			{ 1   ,0    ,0    ,0 },
			{ 0   ,cosX ,-sinX,0 },
			{ 0   ,sinX , cosX,0 },
			{ 0   ,0    ,0    ,1 }
		);

		return rotZ * rotY * rotX;
	}

	constexpr inline Matrix4f ScaleMatrix(const Vector3f scale)
	{
		return	{
					{scale.x,   0   ,   0   ,   0   },
					{   0   ,scale.y,   0   ,   0   },
					{   0   ,   0   ,scale.z,   0   },
					{   0   ,   0   ,   0   ,   1   }
				};
	}
	constexpr inline Matrix4f ScaleMatrix(const float scale)
	{
		return	{
					{scale  ,   0   ,   0   ,   0   },
					{   0   ,scale  ,   0   ,   0   },
					{   0   ,   0   ,scale  ,   0   },
					{   0   ,   0   ,   0   ,   1   }
				};
	}

	inline Matrix4f PrespectiveMatrix(float fov, float aspectRatio, float near, float far)
	{
		float tan = tanf(fov / 2.f);
		float dz = far - near;

		return	{
					{1 / (aspectRatio * tan),0      ,0                 ,0                   },
					{0                      ,1 / tan,0                 ,0                   },
					{0                      ,0      ,-(far + near) / dz,-2 * far * near / dz},
					{0                      ,0      ,-1                ,0                   }
				};
	}
	constexpr inline Matrix4f OrthographicMatrix(float width, float height, float near, float far)
	{
		return	{
					{2 / width,0         ,0                ,0},
					{0        ,2 / height,0                ,0},
					{0        ,0         ,-2 / (far - near),0},
					{0        ,0         ,0                ,1}
		};
	}

	constexpr inline Vector3f Rotate(const Vector3f& v, const Quatronionf& rotation)
	{
		return (rotation * Quatronionf(0, v) * Conjugate(rotation)).v;
	}
}