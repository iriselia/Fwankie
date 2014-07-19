#pragma once
#include "WindowsPlatform.h"

/**
 * Structure for integer vectors in 2-d space.
 */
struct IntVector
{
	int32 X;
	int32 Y;

public:

	/** An int point with zeroed values. */
	static const IntVector ZeroValue;

	/** An int point with INDEX_NONE values. */
	static const IntVector NoneValue;


public:

	/**
	 * Default constructor.
	 */
	IntVector();

	/**
	 * Creates and initializes a new instance with the specified coordinates.
	 *
	 * @param InX - The x-coordinate.
	 * @param InY - The y-coordinate.
	 * @param InZ - The z-coordinate.
	 */
	IntVector( int32 InX, int32 InY);

	/**
	 * Constructor
	 *
	 * @param InValue replicated to all components
	 */
	explicit IntVector( int32 InValue );


public:

	/**
	 * Gets specific component of a point.
	 *
	 * @param i Index of point component
	 *
	 * @return const reference to component.
	 */
	const int32& operator()( int32 i ) const;

	/**
	 * Gets specific component of a point.
	 *
	 * @param i Index of point component
	 *
	 * @return reference to component.
	 */
	int32& operator()( int32 i );

	/**
	 * Compares points for equality.
	 *
	 * @param Other The other int point being compared.
	 *
	 * @return true if the points are equal otherwise false.
	 */
	bool operator==( const IntVector& Other ) const;

	/**
	 * Compares points for inequality.
	 *
	 * @param Other The other int point being compared.
	 *
	 * @return true if the points are not equal otherwise false.
	 */
	bool operator!=( const IntVector& Other ) const;

	/**
	 * Scales this point.
	 *
	 * @param Scale What to multiply the point by.
	 *
	 * @return Reference to this point after multiplication.
	 */
	IntVector& operator*=( int32 Scale );

	/**
	 * Divides this point.
	 *
	 * @param Divisor What to divide the point by.
	 *
	 * @return Reference to this point after division.
	 */
	IntVector& operator/=( int32 Divisor );

	/**
	 * Adds to this point.
	 *
	 * @param Other The point to add to this point.
	 *
	 * @return Reference to this point after addition.
	 */
	IntVector& operator+=( const IntVector& Other );

	/**
	 * Subtracts from this point.
	 *
	 * @param Other The point to subtract from this point.
	 *
	 * @return Reference to this point after subtraction.
	 */
	IntVector& operator-=( const IntVector& Other );

	/**
	 * Assigns another point to this one.
	 *
	 * @param Other The point to assign this point from.
	 *
	 * @return Reference to this point after assignment.
	 */
	IntVector& operator=( const IntVector& Other );

	/**
	 * Gets the result of scaling on this point.
	 *
	 * @param Scale What to multiply the point by.
	 *
	 * @return A new scaled int point.
	 */
	IntVector operator*( int32 Scale ) const;

	/**
	 * Gets the result of division on this point.
	 *
	 * @param Divisor What to divide the point by.
	 *
	 * @return A new divided int point.
	 */
	IntVector operator/( int32 Divisor ) const;

	/**
	 * Gets the result of addition on this point.
	 *
	 * @param Other The other point to add to this.
	 *
	 * @return A new combined int point.
	 */
	IntVector operator+( const IntVector& Other ) const;

	/**
	 * Gets the result of subtraction from this point.
	 *
	 * @param Other The other point to subtract from this.
	 *
	 * @return A new subtracted int point.
	 */
	IntVector operator-( const IntVector& Other ) const;


public:

	/**
	 * Gets the maximum value in the point.
	 *
	 * @return The maximum value in the point.
	 */
	float GetMax( ) const;

	/**
	 * Gets the minimum value in the point.
	 *
	 * @return The minimum value in the point.
	 */
	float GetMin( ) const;

	/**
	 * Gets the distance of this point from (0,0).
	 *
	 * @return The distance of this point from (0,0).
	 */
	int32 Size( ) const;

	/**
	 * Get a textual representation of this vector.
	 *
	 * @return A string describing the vector.
	 */
	FString ToString( ) const;


public:

	/**
	 * Divide an int point and round up the result.
	 *
	 * @param lhs The int point being divided.
	 * @param Divisor What to divide the int point by.
	 *
	 * @return A new divided int point.
	 */
	static IntVector DivideAndRoundUp( IntVector lhs, int32 Divisor );

	/**
	 * Gets the number of components a point has.
	 *
	 * @return Number of components point has.
	 */
	static int32 Num( );


public:

	/**
	 * Serializes the Rectangle.
	 *
	 * @param Ar - The archive to serialize into.
	 * @param Vector - The vector to serialize.
	 *
	 * @return Reference to the Archive after serialization.
	 */
	friend FArchive& operator<<( FArchive& Ar, IntVector& Vector )
	{
		return Ar << Vector.X << Vector.Y << Vector.Z;
	}
};


FORCEINLINE IntVector::IntVector( )
{ }


FORCEINLINE IntVector::IntVector( int32 InX, int32 InY, int32 InZ )
	: X(InX)
	, Y(InY)
	, Z(InZ)
{ }


FORCEINLINE IntVector::IntVector( int32 InValue )
	: X(InValue)
	, Y(InValue)
	, Z(InValue)
{ }


FORCEINLINE IntVector::IntVector( EForceInit )
	: X(0)
	, Y(0)
	, Z(0)
{ }


FORCEINLINE const int32& IntVector::operator()( int32 i ) const
{
	return (&X)[i];
}


FORCEINLINE int32& IntVector::operator()( int32 i )
{
	return (&X)[i];
}


FORCEINLINE bool IntVector::operator==( const IntVector& Other ) const
{
	return X==Other.X && Y==Other.Y && Z==Other.Z;
}


FORCEINLINE bool IntVector::operator!=( const IntVector& Other ) const
{
	return X!=Other.X || Y!=Other.Y || Z!=Other.Z;
}


FORCEINLINE IntVector& IntVector::operator*=( int32 Scale )
{
	X *= Scale;
	Y *= Scale;
	Z *= Scale;

	return *this;
}


FORCEINLINE IntVector& IntVector::operator/=( int32 Divisor )
{
	X /= Divisor;
	Y /= Divisor;
	Z /= Divisor;

	return *this;
}


FORCEINLINE IntVector& IntVector::operator+=( const IntVector& Other )
{
	X += Other.X;
	Y += Other.Y;
	Z += Other.Z;

	return *this;
}


FORCEINLINE IntVector& IntVector::operator-=( const IntVector& Other )
{
	X -= Other.X;
	Y -= Other.Y;
	Z -= Other.Z;

	return *this;
}


FORCEINLINE IntVector& IntVector::operator=( const IntVector& Other )
{
	X = Other.X;
	Y = Other.Y;
	Z = Other.Z;

	return *this;
}


FORCEINLINE IntVector IntVector::operator*( int32 Scale ) const
{
	return IntVector(*this) *= Scale;
}


FORCEINLINE IntVector IntVector::operator/( int32 Divisor ) const
{
	return IntVector(*this) /= Divisor;
}


FORCEINLINE IntVector IntVector::operator+( const IntVector& Other ) const
{
	return IntVector(*this) += Other;
}

FORCEINLINE IntVector IntVector::operator-( const IntVector& Other ) const
{
	return IntVector(*this) -= Other;
}


FORCEINLINE IntVector IntVector::DivideAndRoundUp( IntVector lhs, int32 Divisor )
{
	return IntVector(FMath::DivideAndRoundUp(lhs.X, Divisor), FMath::DivideAndRoundUp(lhs.Y, Divisor), FMath::DivideAndRoundUp(lhs.Z, Divisor));
}


FORCEINLINE float IntVector::GetMax( ) const
{
	return FMath::Max(FMath::Max(X, Y), Z);
}


FORCEINLINE float IntVector::GetMin( ) const
{
	return FMath::Min(FMath::Min(X, Y), Z);
}


FORCEINLINE int32 IntVector::Num( )
{
	return 2;
}


FORCEINLINE int32 IntVector::Size( ) const
{
	return int32(FMath::Sqrt(float(X * X + Y * Y + Z * Z)));
}


FORCEINLINE FString IntVector::ToString( ) const
{
	return FString::Printf(TEXT("X=%3.3f Y=%3.3f Z=%3.3f"), X, Y, Z);
}

FORCEINLINE uint32 GetTypeHash(const IntVector& Vector)
{
	return FCrc::MemCrc_DEPRECATED(&Vector,sizeof(IntVector));
}
