#include "Math.h"
#include "Unreal.h" // Rotator_ToQuat()






SDK::FVector Math::Vector_Add(const SDK::FVector& A, const SDK::FVector& B)
{
    return SDK::FVector
    {
        A.X + B.X,
        A.Y + B.Y,
        A.Z + B.Z
    };
}

SDK::FVector Math::Vector_Multiply(const SDK::FVector& A, float B)
{
    return SDK::FVector
    {
        A.X * B,
        A.Y * B,
        A.Z * B
    };
}

SDK::FVector Math::Vector_Normal(const SDK::FVector& vector, float tolerance)
{
    float vectorLengthSquared = (vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z);
    if (vectorLengthSquared < tolerance)
        return SDK::FVector();

    float vectorLengthInverted = 1.0f / sqrt(vectorLengthSquared);
    return vector * vectorLengthInverted;
}

SDK::FVector Math::Vector_Rotate(const SDK::FVector& vector, const SDK::FQuat& quat)
{
    SDK::FVector quatVector;
    quatVector.X = quat.X;
    quatVector.Y = quat.Y;
    quatVector.Z = quat.Z;

    SDK::FVector qXv = Vector_Cross(quatVector, vector); // q * v
    SDK::FVector qXqXv = Vector_Cross(quatVector, qXv);  // q * (q * v)

    SDK::FVector outVector;
    outVector.X = vector.X + 2.0f * ((quat.W * qXv.X) + qXqXv.X);
    outVector.Y = vector.Y + 2.0f * ((quat.W * qXv.Y) + qXqXv.Y);
    outVector.Z = vector.Z + 2.0f * ((quat.W * qXv.Z) + qXqXv.Z);

    return outVector;
}

float Math::Vector_Distance(const SDK::FVector& A, const SDK::FVector& B)
{
    const float X_Distance = A.X - B.X;
    const float Y_Distance = A.Y - B.Y;
    const float Z_Distance = A.Z - B.Z;

    return std::sqrtf((X_Distance * X_Distance) + (Y_Distance * Y_Distance) + (Z_Distance * Z_Distance));
}

float Math::Vector_Dot(const SDK::FVector& A, const SDK::FVector& B)
{
    return A.X * B.X + A.Y * B.Y + A.Z * B.Z;
}

SDK::FVector Math::Vector_Cross(const SDK::FVector& A, const SDK::FVector& B)
{
    SDK::FVector outVector;
    outVector.X = (A.Y * B.Z) - (A.Z * B.Y);
    outVector.Y = (A.Z * B.X) - (A.X * B.Z);
    outVector.Z = (A.X * B.Y) - (A.Y * B.X);

    return outVector;
}




SDK::FRotator Math::Quat_ToRotator(const SDK::FQuat& quat)
{
    /* Ensure quaternion is normalized before conversion. */
    SDK::FQuat q = quat;
    const float normSq = (q.X * q.X) + (q.Y * q.Y) + (q.Z * q.Z) + (q.W * q.W);
    if (normSq > TINY) // Check for nonsense input.
    {
        const float invLen = 1.0f / std::sqrt(normSq);
        q.X *= invLen;
        q.Y *= invLen;
        q.Z *= invLen;
        q.W *= invLen;
    }
    else
    {
        /* Fall back to identity quaternion. */
        q = SDK::FQuat{ 0.0f, 0.0f, 0.0f, 1.0f };
    }

    /* Convert quaternion to Euler angles (in Z(Yaw)->Y(Pitch)->X(Roll) order). */
    SDK::FRotator rotator;

    /* Compute roll (X) using standard quaternion-to-Euler formulas. */
    const float sinr_cosp = 2.0f * ((q.W * q.X) + (q.Y * q.Z));
    const float cosr_cosp = 1.0f - 2.0f * ((q.X * q.X) + (q.Y * q.Y));
    rotator.Roll = std::atan2(sinr_cosp, cosr_cosp);

    /* Compute sin(pitch) value; clamp to [-1,1] to avoid invalid asin() results due to precision errors. */
    const float sinp = 2.0f * ((q.W * q.Y) - (q.Z * q.X));
    if (std::fabs(sinp) >= 1.0f)
    {
        /* Use 90 degrees if out of range (gimbal lock). */
        rotator.Pitch = std::copysign(PI / 2.0f, sinp);
    }
    else
    {
        rotator.Pitch = std::asin(sinp);
    }

    /* Compute yaw (Z) using standard quaternion-to-Euler formulas. */
    const float siny_cosp = 2.0f * ((q.W * q.Z) + (q.X * q.Y));
    const float cosy_cosp = 1.0f - 2.0f * ((q.Y * q.Y) + (q.Z * q.Z));
    rotator.Yaw = std::atan2(siny_cosp, cosy_cosp);

    /* Convert radians back to degrees. */
    rotator.Roll  = rotator.Roll * RTD * -1.0f; // X
    rotator.Pitch = rotator.Pitch * RTD * -1.0f; // Y
    rotator.Yaw   *= RTD; // Z

    return rotator;
}

SDK::FQuat Math::Rotator_ToQuat(const SDK::FRotator& rotator)
{
    /* Convert degrees to radians and take half - angles, as quaternion uses half - angle trig. */
    const float halfRoll  = 0.5f * rotator.Roll * DTR * -1.0f;  // X
    const float halfPitch = 0.5f * rotator.Pitch * DTR * -1.0f; // Y
    const float halfYaw   = 0.5f * rotator.Yaw * DTR;   // Z

    /* Precompute sines / cosines of the half-angles. */
    const float sr = std::sin(halfRoll);
    const float cr = std::cos(halfRoll);

    const float sp = std::sin(halfPitch);
    const float cp = std::cos(halfPitch);

    const float sy = std::sin(halfYaw);
    const float cy = std::cos(halfYaw);

    /* Compose in Z(Yaw)->Y(Pitch)->X(Roll) order, matching Unreal's FRotator::Quaternion(). */
    SDK::FQuat quat;
    quat.W = cr * cp * cy + sr * sp * sy;
    quat.X = sr * cp * cy - cr * sp * sy; // X corresponds to Roll contribution.
    quat.Y = cr * sp * cy + sr * cp * sy; // Y corresponds to Pitch contribution.
    quat.Z = cr * cp * sy - sr * sp * cy; // Z corresponds to Yaw contribution.

    /* Normalize to ensure a unit quaternion (important for downstream use like rotation / matrix). */
    const float normSq = (quat.X * quat.X) + (quat.Y * quat.Y) + (quat.Z * quat.Z) + (quat.W * quat.W);
    if (normSq > TINY) // Check for nonsense input.
    {
        const float invLen = 1.0f / std::sqrt(normSq);
        quat.W *= invLen;
        quat.X *= invLen;
        quat.Y *= invLen;
        quat.Z *= invLen;
    }
    else
    {
        /* Fall back to identity quaternion. */
        quat = SDK::FQuat{ 0.0f, 0.0f, 0.0f, 1.0f };
    }

    return quat;
}

SDK::FVector Math::Rotator_ForwardVector(const SDK::FRotator& rotator)
{
    SDK::FQuat quat = Rotator_ToQuat(rotator);
    SDK::FVector vector;
    vector.X = 1.0f;

    return Vector_Rotate(vector, quat);
}

SDK::FVector Math::Rotator_RightVector(const SDK::FRotator& rotator)
{
    SDK::FQuat quat = Rotator_ToQuat(rotator);
    SDK::FVector vector;
    vector.Y = 1.0f;

    return Vector_Rotate(vector, quat);
}

SDK::FVector Math::Rotator_UpVector(const SDK::FRotator& rotator)
{
    SDK::FQuat quat = Rotator_ToQuat(rotator);
    SDK::FVector vector;
    vector.Z = 1.0f;

    return Vector_Rotate(vector, quat);
}




SDK::FVector Math::Vector_LocalToWorld(const Unreal::Transform& unrealTransform, const SDK::FVector& vector)
{
    SDK::FVector locationScaled;
    locationScaled.X = vector.X * unrealTransform.scale.X;
    locationScaled.Y = vector.Y * unrealTransform.scale.Y;
    locationScaled.Z = vector.Z * unrealTransform.scale.Z;

    SDK::FVector rotatedVector = Vector_Rotate(locationScaled, unrealTransform.Quat());
    
    SDK::FVector outVector;
    outVector.X = rotatedVector.X + unrealTransform.location.X;
    outVector.Y = rotatedVector.Y + unrealTransform.location.Y;
    outVector.Z = rotatedVector.Z + unrealTransform.location.Z;

    return outVector;
}

Unreal::Transform Math::F_ToUnrealTransform(const SDK::FTransform& fTransform)
{
    Unreal::Transform unrealTransform;
    unrealTransform.location = fTransform.Translation;
    unrealTransform.rotation = Math::Quat_ToRotator(fTransform.Rotation);
    unrealTransform.scale = fTransform.Scale3D;

    return unrealTransform;
}

SDK::FTransform Math::Unreal_ToFTransform(const Unreal::Transform& unrealTransform)
{
    SDK::FTransform fTransform;
    fTransform.Translation = unrealTransform.location;
    fTransform.Rotation = unrealTransform.Quat();
    fTransform.Scale3D = unrealTransform.scale;

    return fTransform;
}




uint32_t Math::ColorFloat4_ToU32(float color[4])
{
    uint8_t r = (uint8_t)(std::clamp(color[0], 0.0f, 1.0f) * 255.0f + 0.5f);
    uint8_t g = (uint8_t)(std::clamp(color[1], 0.0f, 1.0f) * 255.0f + 0.5f);
    uint8_t b = (uint8_t)(std::clamp(color[2], 0.0f, 1.0f) * 255.0f + 0.5f);
    uint8_t a = (uint8_t)(std::clamp(color[3], 0.0f, 1.0f) * 255.0f + 0.5f);
    return (uint32_t)((a << 24) | (b << 16) | (g << 8) | (r));
}




uint32_t Math::Seconds_ToMilliseconds(double seconds)
{
    return static_cast<uint32_t>(std::lround(seconds * 1000.0));
}




float Math::Unit_ToMetre(float centimetres)
{
    return centimetres / 100.0f;
}
float Math::Unit_ToInch(float centimetres)
{
    return centimetres / 2.54f;
}

float Math::Metre_ToUnit(float metres)
{
    return metres * 100.0f;
}
float Math::Metre_ToInch(float metres)
{
    return Unit_ToInch(Metre_ToUnit(metres));
}

float Math::Inch_ToUnit(float inches)
{
    return inches * 2.54f;
}
float Math::Inch_ToMetre(float inches)
{
    return Unit_ToMetre(Inch_ToUnit(inches));
}
