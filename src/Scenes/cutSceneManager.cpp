#include "cutSceneManager.hpp"

namespace ph {

CutSceneManager::CutSceneManager()
	:mActiveCutscene(nullptr)
{
}

void CutSceneManager::activateCutscene(std::unique_ptr<CutScene> startingCutScene)
{
	mActiveCutscene = std::move(startingCutScene);
}

void CutSceneManager::updateCutScene(const sf::Time delta)
{
	mActiveCutscene->update(delta);
}

bool CutSceneManager::isCutSceneActive()
{
	return mActiveCutscene != nullptr && mActiveCutscene->isActive();
}

}