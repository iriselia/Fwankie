struct FTickFunction
{
public:
	//FTickFunction();
	virtual ~FTickFunction();

private:
	/** If true, means that this tick function is in the master array of tick functions **/
	bool bRegistered : 1;

	/**
	* If false, this tick will not fire, nor will any other tick that has this tick function as an EnableParent
	* CAUTION: Do not set this directly
	**/
	bool bTickEnabled : 1;

public:
	/**
	* If the "EnableParent" is not enabled, then this tick function is implicitly disabled as well.
	* Caution, there is no protection on this strong pointer. It is assumed your enable parent will not be destroyed before you are.
	**/
	FTickFunction*								EnableParent;
	/** Back pointer to the FTickTaskLevel containing this tick function if it is registered **/
	class FTickTaskLevel*						TickTaskLevel;

	/** Default constructor, intitalizes to reasonable defaults **/
	FTickFunction();
	/** Destructor, unregisters the tick function **/
	virtual ~FTickFunction();

	/**
	* Adds the tick function to the master list of tick functions.
	* @param Level - level to place this tick function in
	**/
	void RegisterTickFunction(class ULevel* Level);
	/** Removes the tick function from the master list of tick functions. **/
	void UnRegisterTickFunction();
	/** See if the tick function is currently registered */
	bool IsTickFunctionRegistered() const { return bRegistered; }

	/** Enables or disables this tick function. **/
	void SetTickFunctionEnable(bool bInEnabled);
	/** Returns whether the tick function is currently enabled */
	bool IsTickFunctionEnabled() const { return bTickEnabled; }

};