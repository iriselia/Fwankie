// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	MulticastDelegateBase.h: Declares the FMulticastDelegateBase class.
=============================================================================*/

#pragma once


/**
 * Abstract base class for multicast delegates.
 */
template<typename ObjectPtrType = FWeakObjectPtr>
class FMulticastDelegateBase
{
public:

	/**
	 * Removes all functions from this delegate's invocation list
	 */
	void Clear( )
	{
		for (IDelegateInstance*& DelegateInstanceRef : InvocationList)
		{
			delete DelegateInstanceRef;
			DelegateInstanceRef = nullptr;
		}
	}

	/**
	 * Checks to see if any functions are bound to this multi-cast delegate.
	 *
	 * @return true if any functions are bound, false otherwise.
	 */
	inline bool IsBound( ) const
	{
		return (InvocationList.Num() > 0);
	}

	/** 
	 * Checks to see if any functions are bound to the given user object.
	 *
	 * @return	True if any functions are bound to InUserObject, false otherwise.
	 */
	inline bool IsBoundToObject( void const* InUserObject ) const
	{
		for (IDelegateInstance* DelegateInstance : InvocationList)
		{
			if ((DelegateInstance != nullptr) && DelegateInstance->HasSameObject(InUserObject))
			{
				return true;
			}
		}

		return false;
	}

	/**
	 * Removes all functions from this multi-cast delegate's invocation list that are bound to the specified UserObject.
	 * Note that the order of the delegates may not be preserved!
	 *
	 * @param InUserObject The object to remove all delegates for.
	 */
	void RemoveAll( const void* InUserObject )
	{
		for (int32 InvocationListIndex = InvocationList.Num() - 1; InvocationListIndex >= 0; --InvocationListIndex)
		{
			IDelegateInstance*& DelegateInstanceRef = InvocationList[InvocationListIndex];

			if ((DelegateInstanceRef != nullptr) && DelegateInstanceRef->HasSameObject(InUserObject))
			{
				delete DelegateInstanceRef;
				DelegateInstanceRef = nullptr;
			}
		}
	}

protected:

	/**
	 * Hidden default constructor.
	 */
	inline FMulticastDelegateBase( )
		: InvocationListLockCount(0)
		, NeedsCompaction(false)
	{ }

protected:

	/**
	 * Adds the given delegate instance to the invocation list.
	 *
	 * @param DelegateInstance The delegate instance to add.
	 */
	inline void AddInternal( IDelegateInstance* DelegateInstance )
	{
		InvocationList.Add(DelegateInstance);
	}

	/**
	 * Removes any expired or deleted functions from the invocation list.
	 *
	 * @see RequestCompaction
	 */
	void CompactInvocationList( )
	{
		if (!NeedsCompaction || (InvocationListLockCount != 0))
		{
			return;
		}

		for (int32 InvocationListIndex = InvocationList.Num() - 1; InvocationListIndex >= 0; --InvocationListIndex)
		{
			IDelegateInstance* DelegateInstance = InvocationList[InvocationListIndex];

			if ((DelegateInstance == nullptr) || DelegateInstance->IsCompactable())
			{
				InvocationList.RemoveAtSwap(InvocationListIndex);

				if (DelegateInstance != nullptr)
				{
					delete DelegateInstance;
				}
			}
		}

		NeedsCompaction = false;
	}

	/**
	 * Gets a read-only reference to the invocation list.
	 *
	 * @return The invocation list.
	 */
	inline const TArray<IDelegateInstance*>& GetInvocationList( ) const
	{
		return InvocationList;
	}

	/**
	 * Requests that the invocation list be compacted.
	 *
	 * @see CompactInvocationList
	 */
	inline void RequestCompaction( )
	{
		NeedsCompaction = true;
	}

	/**
	 * Increments the lock counter for the invocation list.
	 */
	inline void LockInvocationList( ) const
	{
		++InvocationListLockCount;
	}

	/**
	 * Decrements the lock counter for the invocation list.
	 */
	inline void UnlockInvocationList( ) const
	{
		--InvocationListLockCount;
	}

private:

	// Holds the collection of delegate instances to invoke.
	TArray<IDelegateInstance*> InvocationList;

	// Holds a lock counter for the invocation list.
	mutable int32 InvocationListLockCount;

	// Holds a flag indicating whether the invocation list needs to be compacted.
	bool NeedsCompaction;
};
