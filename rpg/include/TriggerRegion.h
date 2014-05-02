
#ifndef TRIGGERREGION_H
#define TRIGGERREGION_H

class TriggerRegion {
public:

	virtual ~TriggerRegion() {}

	virtual bool isTouching(float _x, float _y, float _entityRadius)const = 0;
	
};

#endif