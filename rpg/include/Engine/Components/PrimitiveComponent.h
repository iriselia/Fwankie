#pragma once
#include "SceneComponent.h"
#include "hgeanim.h"

class IPrimitiveComponent : public ISceneComponent {
public:
	virtual ~IPrimitiveComponent();


// 	void IPrimitiveComponent::CreateRenderState_Concurrent()
// 	{
// 		Super::CreateRenderState_Concurrent();
// 
// 		UpdateBounds();
// 
// 		// If the primitive isn't hidden and the detail mode setting allows it, add it to the scene.
// 		if (ShouldComponentAddToScene())
// 		{
// 			World->Scene->AddPrimitive(this);
// 		}
// 	}

protected:

private:

};