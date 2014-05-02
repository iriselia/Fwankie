#include "TriggerRegion.h"
#include <math.h>

#ifndef TRIGGERREGION_CIRCLE_H
#define TRIGGERREGION_CIRCLE_H

class TriggerRegion_Circle : public TriggerRegion {
private:
	float m_x;
	float m_y;
	float m_fRadius;
public:
	TriggerRegion_Circle(float _x, float _y, float _radius) :
		m_fRadius(_radius),
		m_x(_x),
		m_y(_y) {
	}

	bool isTouching(float _x, float _y, float _entityRadius)const {
		float distanceSq = pow(m_x - _x, 2) + pow(m_y - _y, 2);
		float requirementSq = pow(m_fRadius + _entityRadius, 2);
		return distanceSq < requirementSq;
	}
	 
};

#endif