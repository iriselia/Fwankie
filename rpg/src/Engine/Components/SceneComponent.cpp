#include "SceneComponent.h"

void FSceneComponentTickFunc::run(ISceneComponent* _sceneComponent, float _deltaTime) {
	if (m_bResetX) _sceneComponent->x = m_xReset;
	if (m_bResetY) _sceneComponent->y = m_yReset;
}