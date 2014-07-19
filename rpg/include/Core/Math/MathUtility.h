#pragma once
#include "Core.h"
/*-----------------------------------------------------------------------------
	Definitions.
-----------------------------------------------------------------------------*/

// Forward declarations.
// class  FVector;
// class  FVector4;
// class  FPlane;
// class  FBox;
// class  FRotator;
// class  FMatrix;
// class  FQuat;
// class  FTwoVectors;
// class  FTransform;
// class  FSphere;
struct Vector2D;
/*struct FLinearColor;*/

/*-----------------------------------------------------------------------------
	Floating point constants.
-----------------------------------------------------------------------------*/

#undef  PI
#define PI 					(3.1415926535897932f)
#define SMALL_NUMBER		(1.e-8f)
#define KINDA_SMALL_NUMBER	(1.e-4f)
#define BIG_NUMBER			(3.4e+38f)
#define EULERS_NUMBER       (2.71828182845904523536f)

// Copied from float.h
#define MAX_FLT 3.402823466e+38F

// Aux constants.
#define INV_PI			(0.31830988618f)
#define HALF_PI			(1.57079632679f)

// Magic numbers for numerical precision.
#define DELTA			(0.00001f)

/**
 * Lengths of normalized vectors (These are half their maximum values
 * to assure that dot products with normalized vectors don't overflow).
 */
#define FLOAT_NORMAL_THRESH				(0.0001f)

//
// Magic numbers for numerical precision.
//
#define THRESH_POINT_ON_PLANE			(0.10f)		/* Thickness of plane for front/back/inside test */
#define THRESH_POINT_ON_SIDE			(0.20f)		/* Thickness of polygon side's side-plane for point-inside/outside/on side test */
#define THRESH_POINTS_ARE_SAME			(0.00002f)	/* Two points are same if within this distance */
#define THRESH_POINTS_ARE_NEAR			(0.015f)	/* Two points are near if within this distance and can be combined if imprecise math is ok */
#define THRESH_NORMALS_ARE_SAME			(0.00002f)	/* Two normal points are same if within this distance */
													/* Making this too large results in incorrect CSG classification and disaster */
#define THRESH_VECTORS_ARE_NEAR			(0.0004f)	/* Two vectors are near if within this distance and can be combined if imprecise math is ok */
													/* Making this too large results in lighting problems due to inaccurate texture coordinates */
#define THRESH_SPLIT_POLY_WITH_PLANE	(0.25f)		/* A plane splits a polygon in half */
#define THRESH_SPLIT_POLY_PRECISELY		(0.01f)		/* A plane exactly splits a polygon */
#define THRESH_ZERO_NORM_SQUARED		(0.0001f)	/* Size of a unit normal that is considered "zero", squared */
#define THRESH_VECTORS_ARE_PARALLEL		(0.02f)		/* Vectors are parallel if dot product varies less than this */

/*-----------------------------------------------------------------------------
	Global functions.
-----------------------------------------------------------------------------*/

/**
 * Structure for all math helper functions, inherits from platform math to pick up platform-specific implementations
 * Check GenericPlatformMath.h for additional math functions
 */
struct MathUtil : public PlatformMath
{
	// Random Number Functions

	/** Helper function for rand implementations. Returns a random number in [0..A) */
	static FORCEINLINE int32 RandHelper(int32 A)
	{
		// RAND_MAX+1 give interval [0..A) with even distribution.
		return A>0 ? TruncToInt(Rand()/(float)((uint32)RAND_MAX+1) * A) : 0;
	}

	/** Helper function for rand implementations. Returns a random number >= Min and <= Max */
	static FORCEINLINE int32 RandRange(int32 Min, int32 Max)
	{
		const int32 Range = (Max - Min) + 1;
		return Min + RandHelper(Range);
	}

	/** Util to generate a random number in a range. */
	static FORCEINLINE float FRandRange(float InMin, float InMax)
	{
		return InMin + (InMax - InMin) * FRand();
	}

	// Predicates

	/** Checks if value is within a range, exclusive on MaxValue) */
	template< class U > 
	static FORCEINLINE bool IsWithin(const U& TestValue, const U& MinValue, const U& MaxValue)
	{
		return ((TestValue>=MinValue) && (TestValue < MaxValue));
	}

	/** Checks if value is within a range, inclusive on MaxValue) */
	template< class U > 
	static FORCEINLINE bool IsWithinInclusive(const U& TestValue, const U& MinValue, const U& MaxValue)
	{
		return ((TestValue>=MinValue) && (TestValue <= MaxValue));
	}
	
	/**
	 *	Checks if two floating point numbers are nearly equal.
	 *	@param A				First number to compare
	 *	@param B				Second number to compare
	 *	@param ErrorTolerance	Maximum allowed difference for considering them as 'nearly equal'
	 *	@return					true if A and B are nearly equal
	 */
	static FORCEINLINE bool IsNearlyEqual(float A, float B, float ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<float>( A - B ) < ErrorTolerance;
	}

	/**
	 *	Checks if two floating point numbers are nearly equal.
	 *	@param A				First number to compare
	 *	@param B				Second number to compare
	 *	@param ErrorTolerance	Maximum allowed difference for considering them as 'nearly equal'
	 *	@return					true if A and B are nearly equal
	 */
	static FORCEINLINE bool IsNearlyEqual(double A, double B, double ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<double>( A - B ) < ErrorTolerance;
	}

	/**
	 *	Checks if a floating point number is nearly zero.
	 *	@param Value			Number to compare
	 *	@param ErrorTolerance	Maximum allowed difference for considering Value as 'nearly zero'
	 *	@return					true if Value is nearly zero
	 */
	static FORCEINLINE bool IsNearlyZero(float Value, float ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<float>( Value ) < ErrorTolerance;
	}

	/**
	 *	Checks if a floating point number is nearly zero.
	 *	@param Value			Number to compare
	 *	@param ErrorTolerance	Maximum allowed difference for considering Value as 'nearly zero'
	 *	@return					true if Value is nearly zero
	 */
	static FORCEINLINE bool IsNearlyZero(double Value, double ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<double>( Value ) < ErrorTolerance;
	}

	/**
	 *	Checks whether a number is a power of two.
	 *	@param Value	Number to check
	 *	@return			true if Value is a power of two
	 */
	static FORCEINLINE bool IsPowerOfTwo( uint32 Value )
	{
		return ((Value & (Value - 1)) == 0);
	}


	// Math Operations

	/** Returns highest of 3 values */
	template< class T > 
	static FORCEINLINE T Max3( const T A, const T B, const T C )
	{
		return Max ( Max( A, B ), C );
	}

	/** Returns lowest of 3 values */
	template< class T > 
	static FORCEINLINE T Min3( const T A, const T B, const T C )
	{
		return Min ( Min( A, B ), C );
	}

	/** Multiples value by itself */
	template< class T > 
	static FORCEINLINE T Square( const T A )
	{
		return A*A;
	}

	/** Clamps X to be between Min and Max, inclusive */
	template< class T > 
	static FORCEINLINE T Clamp( const T X, const T Min, const T Max )
	{
		return X<Min ? Min : X<Max ? X : Max;
	}

	/** Snaps a value to the nearest grid multiple */
	static FORCEINLINE float GridSnap( float Location, float Grid )
	{
		if( Grid==0.f )	return Location;
		else			
		{
			return FloorToFloat((Location + 0.5*Grid)/Grid)*Grid;
		}
	}

	/** Snaps a value to the nearest grid multiple */
	static FORCEINLINE double GridSnap( double Location, double Grid )
	{
		if( Grid==0.0 )	return Location;
		else			
		{
			return FloorToDouble((Location + 0.5*Grid)/Grid)*Grid;
		}
	}

	/** Divides two integers and rounds up */
	template <class T>
	static FORCEINLINE T DivideAndRoundUp(T Dividend,T Divisor)
	{
		return (Dividend + Divisor - 1) / Divisor;
	}

	/**
	 * Computes the base 2 logarithm of the specified value
	 *
	 * @param Value the value to perform the log on
	 *
	 * @return the base 2 log of the value
	 */
	static FORCEINLINE float Log2(float Value)
	{
		// Cached value for fast conversions
		static const float LogToLog2 = 1.f / Loge(2.f);
		// Do the platform specific log and convert using the cached value
		return Loge(Value) * LogToLog2;
	}


	// Conversion Functions

	/** 
	 * Converts radians to degrees.
	 * @param	RadVal			Value in radians.
	 * @return					Value in degrees.
	 */
	template<class T>
	static FORCEINLINE T RadiansToDegrees(T const& RadVal)
	{
		return RadVal * (180.f / PI);
	}

	/** 
	 * Converts degrees to radians.
	 * @param	DegVal			Value in degrees.
	 * @return					Value in radians.
	 */
	template<class T>
	static FORCEINLINE T DegreesToRadians(T const& DegVal)
	{
		return DegVal * (PI / 180.f);
	}

	/** Find the smallest angle between two headings (in radians) */
	static float FindDeltaAngle(float A1, float A2)
	{
		// Find the difference
		float Delta = A2 - A1;

		// If change is larger than PI
		if(Delta > PI)
		{
			// Flip to negative equivalent
			Delta = Delta - (PI * 2.0f);
		}
		else if(Delta < -PI)
		{
			// Otherwise, if change is smaller than -PI
			// Flip to positive equivalent
			Delta = Delta + (PI * 2.0f);
		}

		// Return delta in [-PI,PI] range
		return Delta;
	}

	/** Given a heading which may be outside the +/- PI range, 'unwind' it back into that range. */
	static float UnwindRadians(float A)
	{
		while(A > PI)
		{
			A -= ((float)PI * 2.0f);
		}

		while(A < -PI)
		{
			A += ((float)PI * 2.0f);
		}

		return A;
	}

	/** Utility to ensure angle is between +/- 180 degrees by unwinding. */
	static float UnwindDegrees(float A)
	{
		while(A > 180.f)
		{
			A -= 360.f;
		}

		while(A < -180.f)
		{
			A += 360.f;
		}

		return A;
	}

	/** Converts given Cartesian coordinate pair to Polar coordinate system. */
	static FORCEINLINE void CartesianToPolar(float X, float Y, float& OutRad, float& OutAng)
	{
		OutRad = Sqrt(Square(X) + Square(Y));
		OutAng = Atan2(Y, X);
	}
	/** Converts given Polar coordinate pair to Cartesian coordinate system. */
	static FORCEINLINE void PolarToCartesian(float Rad, float Ang, float& OutX, float& OutY)
	{
		OutX = Rad * Cos(Ang);
		OutY = Rad * Sin(Ang);
	}

	// Interpolation Functions

	/** Calculates the percentage along a line from MinValue to MaxValue that Value is. */
	static FORCEINLINE float GetRangePct(float MinValue, float MaxValue, float Value)
	{
		return (Value - MinValue) / (MaxValue - MinValue);
	}

	/** Same as above, but taking a 2d vector as the range. */
	static float GetRangePct(Vector2D const& Range, float Value);
	
	/** Basically a Vector2d version of Lerp. */
	static float GetRangeValue(Vector2D const& Range, float Pct);

	/**
	 * For the given value in the input range, returns the corresponding value in the output range.
	 * Useful for mapping one value range to another value range.  Output is clamped to the OutputRange.
	 * e.g. given that velocities [50..100] correspond to a sound volume of [0.2..1.4], this makes it easy to 
	 *      find the volume for a velocity of 77.
	 */
	static FORCEINLINE float GetMappedRangeValue(Vector2D const& InputRange, Vector2D const& OutputRange, float Value)
	{
		float const ClampedPct = Clamp<float>(GetRangePct(InputRange, Value), 0.f, 1.f);
		return GetRangeValue(OutputRange, ClampedPct);
	}

	/** Performs a linear interpolation between two values, Alpha ranges from 0-1 */
	template< class T, class U > 
	static FORCEINLINE T Lerp(const T& A, const T& B, const U& Alpha)
	{
		return (T)(A + Alpha * (B-A));
	}

	/** Performs a linear interpolation between two values, Alpha ranges from 0-1. Handles full numeric range of T */
	template< class T > 
	static FORCEINLINE T LerpStable(const T& A, const T& B, double Alpha)
	{
		return (T)((A * (1.0 - Alpha)) + (B * Alpha));
	}

	/** Performs a 2D linear interpolation between four values values, FracX, FracY ranges from 0-1 */
	template< class T, class U > 
	static FORCEINLINE T BiLerp(const T& P00,const T& P10,const T& P01,const T& P11, const U& FracX, const U& FracY)
	{
		return Lerp(
			Lerp(P00,P10,FracX),
			Lerp(P01,P11,FracX),
			FracY
			);
	}

	/**
	 * Performs a cubic interpolation
	 *
	 * @param  P - end points
	 * @param  T - tangent directions at end points
	 * @param  Alpha - distance along spline
	 *
	 * @return  Interpolated value
	 */
	template< class T, class U > 
	static FORCEINLINE T CubicInterp( const T& P0, const T& T0, const T& P1, const T& T1, const U& A )
	{
		const float A2 = A  * A;
		const float A3 = A2 * A;

		return (T)(((2*A3)-(3*A2)+1) * P0) + ((A3-(2*A2)+A) * T0) + ((A3-A2) * T1) + (((-2*A3)+(3*A2)) * P1);
	}

	/**
	 * Performs a first derivative cubic interpolation
	 *
	 * @param  P - end points
	 * @param  T - tangent directions at end points
	 * @param  Alpha - distance along spline
	 *
	 * @return  Interpolated value
	 */
	template< class T, class U > 
	static FORCEINLINE T CubicInterpDerivative( const T& P0, const T& T0, const T& P1, const T& T1, const U& A )
	{
		T a = 6.f*P0 + 3.f*T0 + 3.f*T1 - 6.f*P1;
		T b = -6.f*P0 - 4.f*T0 - 2.f*T1 + 6.f*P1;
		T c = T0;

		const float A2 = A  * A;

		return (a * A2) + (b * A) + c;
	}

	/**
	 * Performs a second derivative cubic interpolation
	 *
	 * @param  P - end points
	 * @param  T - tangent directions at end points
	 * @param  Alpha - distance along spline
	 *
	 * @return  Interpolated value
	 */
	template< class T, class U > 
	static FORCEINLINE T CubicInterpSecondDerivative( const T& P0, const T& T0, const T& P1, const T& T1, const U& A )
	{
		T a = 12.f*P0 + 6.f*T0 + 6.f*T1 - 12.f*P1;
		T b = -6.f*P0 - 4.f*T0 - 2.f*T1 + 6.f*P1;

		return (a * A) + b;
	}

	/** Interpolate between A and B, applying an ease in/out function.  Exp controls the degree of the curve. */
	template< class T > 
	static FORCEINLINE T InterpEaseInOut( const T& A, const T& B, float Alpha, float Exp )
	{
		float const ModifiedAlpha = ( Alpha < 0.5f ) ?
			0.5f * Pow(2.f * Alpha, Exp) :
		1.f - 0.5f * Pow(2.f * (1.f - Alpha), Exp);

		return Lerp<T>(A, B, ModifiedAlpha);
	}

	/**
	 * In the case of quaternions, we use a bezier like approach.
	 * T - Actual 'control' orientations.
	 */
	template< class U > static FQuat CubicInterp( const FQuat& P0, const FQuat& T0, const FQuat& P1, const FQuat& T1, const U& A);

	/*
	 *	Cubic Catmull-Rom Spline interpolation. Based on http://www.cemyuksel.com/research/catmullrom_param/catmullrom.pdf 
	 *	Curves are guaranteed to pass through the control points and are easily chained together.
	 *	Equation supports abitrary parameterization. eg. Uniform=0,1,2,3 ; chordal= |Pn - Pn-1| ; centripetal = |Pn - Pn-1|^0.5
	 *	P0 - The control point preceding the interpolation range.
	 *	P1 - The control point starting the interpolation range.
	 *	P2 - The control point ending the interpolation range.
	 *	P3 - The control point following the interpolation range.
	 *	T0-3 - The interpolation parameters for the corresponding control points.		
	 *	T - The interpolation factor in the range 0 to 1. 0 returns P1. 1 returns P2.
	 */
	template< class U > static U CubicCRSplineInterp(const U& P0, const U& P1, const U& P2, const U& P3, const float T0, const float T1, const float T2, const float T3, const float T);

	/* Same as CubicCRSplineInterp but with additional saftey checks. If the checks fail P1 is returned. **/
	template< class U > static U CubicCRSplineInterpSafe(const U& P0, const U& P1, const U& P2, const U& P3, const float T0, const float T1, const float T2, const float T3, const float T);
	
	// Special-case interpolation

	/** Interpolate vector2D from Current to Target with constant step */
	static Vector2D Vector2DInterpConstantTo( const Vector2D& Current, const Vector2D& Target, float DeltaTime, float InterpSpeed );

	/** Interpolate vector2D from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. */
	static Vector2D Vector2DInterpTo( const Vector2D& Current, const Vector2D& Target, float DeltaTime, float InterpSpeed );

	/** Interpolate float from Current to Target with constant step */
	static float FInterpConstantTo( float Current, float Target, float DeltaTime, float InterpSpeed );

	/** Interpolate float from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. */
	static float FInterpTo( float Current, float Target, float DeltaTime, float InterpSpeed );

	/**
	 * Simple function to create a pulsating scalar value
	 *
	 * @param  InCurrentTime  Current absolute time
	 * @param  InPulsesPerSecond  How many full pulses per second?
	 * @param  InPhase  Optional phase amount, between 0.0 and 1.0 (to synchronize pulses)
	 *
	 * @return  Pulsating value (0.0-1.0)
	 */
	static float MakePulsatingValue( const double InCurrentTime, const float InPulsesPerSecond, const float InPhase = 0.0f )
	{
		return 0.5f + 0.5f * (float)sin( ( ( 0.25f + InPhase ) * PI * 2.0 ) + ( InCurrentTime * PI * 2.0 ) * InPulsesPerSecond );
	}

	// Utilities

	/**
	 * Tests a memory region to see that it's working properly.
	 *
	 * @param BaseAddress	Starting address
	 * @param NumBytes		Number of bytes to test (will be rounded down to a multiple of 4)
	 * @return				true if the memory region passed the test
	 */
	static bool MemoryTest(void* BaseAddress, uint32 NumBytes) {
		volatile uint32* Ptr;
		uint32 NumDwords = NumBytes / 4;
		uint32 TestWords[2] = { 0xdeadbeef, 0x1337c0de };
		bool bSucceeded = true;

		for (int32 TestIndex = 0; TestIndex < 2; ++TestIndex)
		{
			// Fill the memory with a pattern.
			Ptr = (uint32*)BaseAddress;
			for (uint32 Index = 0; Index < NumDwords; ++Index)
			{
				*Ptr = TestWords[TestIndex];
				Ptr++;
			}

			// Check that each uint32 is still ok and overwrite it with the complement.
			Ptr = (uint32*)BaseAddress;
			for (uint32 Index = 0; Index < NumDwords; ++Index)
			{
				if (*Ptr != TestWords[TestIndex])
				{
					//FPlatformMisc::LowLevelOutputDebugStringf(TEXT("Failed memory test at 0x%08x, wrote: 0x%08x, read: 0x%08x\n"), Ptr, TestWords[TestIndex], *Ptr);
					bSucceeded = false;
				}
				*Ptr = ~TestWords[TestIndex];
				Ptr++;
			}

			// Check again, now going backwards in memory.
			Ptr = ((uint32*)BaseAddress) + NumDwords;
			for (uint32 Index = 0; Index < NumDwords; ++Index)
			{
				Ptr--;
				if (*Ptr != ~TestWords[TestIndex])
				{
					//FPlatformMisc::LowLevelOutputDebugStringf(TEXT("Failed memory test at 0x%08x, wrote: 0x%08x, read: 0x%08x\n"), Ptr, ~TestWords[TestIndex], *Ptr);
					bSucceeded = false;
				}
				*Ptr = TestWords[TestIndex];
			}
		}

		return bSucceeded;
	}

	/** 32 bit values where BitFlag[x] == (1<<x) */
	static const uint32 BitFlag[32];

	/** 
	 * Returns a smooth Hermite interpolation between 0 and 1 for the value X (where X ranges between A and B)
	 * Clamped to 0 for X <= A and 1 for X >= B.
	 *
	 * @param A Minimum value of X
	 * @param B Maximum value of X
	 * @param X Parameter
	 *
	 * @return Smoothed value between 0 and 1
	 */
	static float SmoothStep(float A, float B, float X)
	{
		if (X < A)
		{
			return 0.0f;
		}
		else if (X >= B)
		{
			return 1.0f;
		}
		const float InterpFraction = (X - A) / (B - A);
		return InterpFraction * InterpFraction * (3.0f - 2.0f * InterpFraction);
	}
	
	/**
	 * Get a bit in memory created from bit flags (uint32 Value:1), used for EngineShowFlags,
	 * TestBitFieldFunctions() tests the implementation
	 */
	static inline bool ExtractBoolFromBitfield(uint8* Ptr, uint32 Index)
	{
		uint8* BytePtr = Ptr + Index / 8;
		uint8 Mask = 1 << (Index & 0x7);

		return (*BytePtr & Mask) != 0;
	}

	/**
	 * Set a bit in memory created from bit flags (uint32 Value:1), used for EngineShowFlags,
	 * TestBitFieldFunctions() tests the implementation
	 */
	static inline void SetBoolInBitField(uint8* Ptr, uint32 Index, bool bSet)
	{
		uint8* BytePtr = Ptr + Index / 8;
		uint8 Mask = 1 << (Index & 0x7);

		if(bSet)
		{
			*BytePtr |= Mask;
		}
		else
		{
			*BytePtr &= ~Mask;
		}
	}

};