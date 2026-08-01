#pragma once
#include "SDK/Engine_classes.hpp"

/* Forward declaration of Unreal.h struct. */
namespace Unreal { struct Transform; }






class Math
{
public:
	static SDK::FVector Vector_Add(const SDK::FVector& A, const SDK::FVector& B);
	static SDK::FVector Vector_Multiply(const SDK::FVector& A, float B);
	static SDK::FVector Vector_Normal(const SDK::FVector& vector, float tolerance = 1.0E-8F); // sqrt(1e-8) = 1e-4 = 0.0001f.
	static SDK::FVector Vector_Rotate(const SDK::FVector& vector, const SDK::FQuat& quat);
	static float Vector_Distance(const SDK::FVector& A, const SDK::FVector& B);
	static float Vector_Dot(const SDK::FVector& A, const SDK::FVector& B);
	static SDK::FVector Vector_Cross(const SDK::FVector& A, const SDK::FVector& B);
	static SDK::FVector Vector_LocalToWorld(const Unreal::Transform& unrealTransform, const SDK::FVector& vector);


	static SDK::FRotator Quat_ToRotator(const SDK::FQuat& quat);
	static SDK::FQuat Rotator_ToQuat(const SDK::FRotator& rotator);
	static SDK::FVector Rotator_ForwardVector(const SDK::FRotator& rotator);
	static SDK::FVector Rotator_RightVector(const SDK::FRotator& rotator);
	static SDK::FVector Rotator_UpVector(const SDK::FRotator& rotator);


	static Unreal::Transform F_ToUnrealTransform(const SDK::FTransform& fTransform);
	static SDK::FTransform Unreal_ToFTransform(const Unreal::Transform& unrealTransform);


	static uint32_t ColorFloat4_ToU32(float color[4]);


	static uint32_t Seconds_ToMilliseconds(double seconds);


	static float Unit_ToMetre(float units);
	static float Unit_ToInch(float units);

	static float Metre_ToUnit(float metres);
	static float Metre_ToInch(float metres);

	static float Inch_ToUnit(float inches);
	static float Inch_ToMetre(float inches);


	static constexpr float PI   = 3.1415927f;
	static constexpr float DTR  = PI / 180.0f; // Degrees-to-radians factor.
	static constexpr float RTD  = 180.0f / PI; // Radians-to-degrees factor.
	static constexpr float TINY = std::numeric_limits<float>::epsilon();


	static const int8_t int8MAX = INT8_MAX;
	static const int8_t int8MIN = INT8_MIN;

	static const uint8_t uint8MAX = UINT8_MAX;
	static const uint8_t uint8MIN = 0;

	static const int16_t int16MAX = INT16_MAX;
	static const int16_t int16MIN = INT16_MIN;

	static const uint16_t uint16MAX = UINT16_MAX;
	static const uint16_t uint16MIN = 0;

	static const int32_t int32MAX = INT32_MAX;
	static const int32_t int32MIN = INT32_MIN;

	static const uint32_t uint32MAX = UINT32_MAX;
	static const uint32_t uint32MIN = 0;

	static const int32_t int64MAX = INT64_MAX;
	static const int32_t int64MIN = INT64_MIN;

	static const int64_t uint64MAX = UINT64_MAX;
	static const int64_t uint64MIN = 0;

	static constexpr float floatMAX = 3.402823466e+38F;
	static constexpr float floatMIN = -3.402823466e+38F;

	static constexpr double doubleMAX = 1.7976931348623158e+308;
	static constexpr double doubleMIN = -1.7976931348623158e+308;
};

