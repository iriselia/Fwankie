#pragma once


/**
 * Structure for integer points in 2-d space.
 */
struct IntPoint
{
	/**
	 * Holds the point's x-coordinate.
	 */
	int32 X;
	
	/**
	 * Holds the point's y-coordinate.
	 */
	int32 Y;


public:

	/** An int point with zeroed values. */
	static const IntPoint ZeroValue;

	/** An int point with INDEX_NONE values. */
	static const IntPoint NoneValue;


public:

	/**
	 * Default constructor.
	 */
	IntPoint( );

	/**
	 * Creates and initializes a new instance with the specified coordinates.
	 *
	 * @param InX - The x-coordinate.
	 * @param InY - The y-coordinate.
	 */
	IntPoint( int32 InX, int32 InY );

public:

	/**
	 * Gets specific component of a point.
	 *
	 * @param PointIndex - Index of point component
	 *
	 * @return const reference to component.
	 */
	const int32& operator()( int32 PointIndex ) const;

	/**
	 * Gets specific component of a point.
	 *
	 * @param PointIndex - Index of point component
	 *
	 * @return reference to component.
	 */
	int32& operator()( int32 PointIndex );

	/**
	 * Compares points for equality.
	 *
	 * @param Other The other int point being compared.
	 *
	 * @return true if the points are equal otherwise false.
	 */
	bool operator==( const IntPoint& Other ) const;

	/**
	 * Compares points for inequality.
	 *
	 * @param Other The other int point being compared.
	 *
	 * @return true if the points are not equal otherwise false.
	 */
	bool operator!=( const IntPoint& Other ) const;

	/**
	 * Scales this point.
	 *
	 * @param Scale What to multiply the point by.
	 *
	 * @return Reference to this point after multiplication.
	 */
	IntPoint& operator*=( int32 Scale );

	/**
	 * Divides this point.
	 *
	 * @param Divisor What to divide the point by.
	 *
	 * @return Reference to this point after division.
	 */
	IntPoint& operator/=( int32 Divisor );

	/**
	 * Adds to this point.
	 *
	 * @param Other The point to add to this point.
	 *
	 * @return Reference to this point after addition.
	 */
	IntPoint& operator+=( const IntPoint& Other );
	
	/**
	 * Subtracts from this point.
	 *
	 * @param Other The point to subtract from this point.
	 *
	 * @return Reference to this point after subtraction.
	 */
	IntPoint& operator-=( const IntPoint& Other );

	IntPoint& operator/=( const IntPoint& Other );

	/**
	 * Assigns another point to this one.
	 *
	 * @param Other The point to assign this point from.
	 *
	 * @return Reference to this point after assignment.
	 */
	IntPoint& operator=( const IntPoint& Other );

	/**
	 * Gets the result of scaling on this point.
	 *
	 * @param Scale What to multiply the point by.
	 *
	 * @return A new scaled int point.
	 */
	IntPoint operator*( int32 Scale ) const;

	/**
	 * Gets the result of division on this point.
	 *
	 * @param Divisor What to divide the point by.
	 *
	 * @return A new divided int point.
	 */
	IntPoint operator/( int32 Divisor ) const;

	/**
	 * Gets the result of addition on this point.
	 *
	 * @param Other The other point to add to this.
	 *
	 * @return A new combined int point.
	 */
	IntPoint operator+( const IntPoint& Other ) const;

	/**
	 * Gets the result of subtraction from this point.
	 *
	 * @param Other The other point to subtract from this.
	 *
	 * @return A new subtracted int point.
	 */
	IntPoint operator-( const IntPoint& Other ) const;

	IntPoint operator/( const IntPoint& Other ) const;


public:

	/**
	 * Gets the maximum value in the point.
	 *
	 * @return The maximum value in the point.
	 */
	int32 GetMax( ) const;

	/**
	 * Gets the minimum value in the point.
	 *
	 * @return The minimum value in the point.
	 */
	int32 GetMin( ) const;

	/**
	 * Gets the distance of this point from (0,0).
	 *
	 * @return The distance of this point from (0,0).
	 */
	int32 Size( ) const;

	/**
	 * Gets the squared distance of this point from (0,0).
	 *
	 * @return The squared distance of this point from (0,0).
	 */
	int32 SizeSquared( ) const;
	
	/**
	 * Get a textual representation of this point.
	 *
	 * @return A string describing the point.
	 */
	//FString ToString( ) const;


public:

	/**
	 * Divide an int point and round up the result.
	 *
	 * @param lhs The int point being divided.
	 * @param Divisor What to divide the int point by.
	 *
	 * @return A new divided int point.
	 */
	static IntPoint DivideAndRoundUp( IntPoint lhs, int32 Divisor );

	/**
	 * Gets number of components point has.
	 *
	 * @return number of components point has.
	 */
	static int32 Num( );


public:

	/**
	 * Serializes the point.
	 *
	 * @param Ar - The archive to serialize into.
	 * @param Point - The point to serialize.
	 *
	 * @return Reference to the Archive after serialization.
	 */
// 	friend FArchive& operator<<( FArchive& Ar, FIntPoint& Point )
// 	{
// 		return Ar << Point.X << Point.Y;
// 	}
};


FORCEINLINE IntPoint::IntPoint( ) { }


FORCEINLINE IntPoint::IntPoint( int32 InX, int32 InY )
	: X(InX)
	, Y(InY)
{ }

FORCEINLINE const int32& IntPoint::operator()( int32 PointIndex ) const
{
	return (&X)[PointIndex];
}


FORCEINLINE int32& IntPoint::operator()( int32 PointIndex )
{
	return (&X)[PointIndex];
}


FORCEINLINE int32 IntPoint::Num( )
{
	return 2;
}


FORCEINLINE bool IntPoint::operator==( const IntPoint& Other ) const
{
	return X==Other.X && Y==Other.Y;
}


FORCEINLINE bool IntPoint::operator!=( const IntPoint& Other ) const
{
	return (X != Other.X) || (Y != Other.Y);
}


FORCEINLINE IntPoint& IntPoint::operator*=( int32 Scale )
{
	X *= Scale;
	Y *= Scale;

	return *this;
}


FORCEINLINE IntPoint& IntPoint::operator/=( int32 Divisor )
{
	X /= Divisor;
	Y /= Divisor;

	return *this;
}


FORCEINLINE IntPoint& IntPoint::operator+=( const IntPoint& Other )
{
	X += Other.X;
	Y += Other.Y;

	return *this;
}


FORCEINLINE IntPoint& IntPoint::operator-=( const IntPoint& Other )
{
	X -= Other.X;
	Y -= Other.Y;

	return *this;
}


FORCEINLINE IntPoint& IntPoint::operator/=( const IntPoint& Other )
{
	X /= Other.X;
	Y /= Other.Y;

	return *this;
}


FORCEINLINE IntPoint& IntPoint::operator=( const IntPoint& Other )
{
	X = Other.X;
	Y = Other.Y;

	return *this;
}


FORCEINLINE IntPoint IntPoint::operator*( int32 Scale ) const
{
	return IntPoint(*this) *= Scale;
}


FORCEINLINE IntPoint IntPoint::operator/( int32 Divisor ) const
{
	return IntPoint(*this) /= Divisor;
}


FORCEINLINE IntPoint IntPoint::DivideAndRoundUp( IntPoint lhs, int32 Divisor )
{
	//return FIntPoint(FMath::DivideAndRoundUp(lhs.X, Divisor), FMath::DivideAndRoundUp(lhs.Y, Divisor));
}	


FORCEINLINE IntPoint IntPoint::operator+( const IntPoint& Other ) const
{
	return IntPoint(*this) += Other;
}


FORCEINLINE IntPoint IntPoint::operator-( const IntPoint& Other ) const
{
	return IntPoint(*this) -= Other;
}


FORCEINLINE IntPoint IntPoint::operator/( const IntPoint& Other ) const
{
	return IntPoint(*this) /= Other;
}


FORCEINLINE int32 IntPoint::GetMax( ) const
{
	//return FMath::Max(X, Y);
}


FORCEINLINE int32 IntPoint::GetMin( ) const
{
	//return FMath::Min(X,Y);
}

FORCEINLINE uint32 GetTypeHash( const IntPoint& InPoint )
{
	//return FCrc::MemCrc_DEPRECATED(&InPoint, sizeof(FIntPoint));
}


FORCEINLINE int32 IntPoint::Size( ) const
{
	//return int32(FMath::Sqrt( float(X*X + Y*Y)));
}

FORCEINLINE int32 IntPoint::SizeSquared() const
{
	return X*X + Y*Y;
}

//FORCEINLINE FString FIntPoint::ToString( ) const
//{
//	return FString::Printf(TEXT("X=%d Y=%d"), X, Y);
//}