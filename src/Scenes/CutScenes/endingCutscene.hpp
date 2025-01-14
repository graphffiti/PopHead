#pragma once

#include "Scenes/cutScene.hpp"

namespace ph {

class GUI;
class MusicPlayer;
class Camera;
class AIManager;
class SceneManager;

class EndingCutScene : public CutScene
{
public:
	EndingCutScene(GameObject& root, GUI&, MusicPlayer&, Camera&, AIManager&, SceneManager&);

	void update(const sf::Time delta) override;

private:
	void initGui();
	void leaveCutScene();

private:
	GUI& mGui;
	MusicPlayer& mMusicPlayer;
	Camera& mCamera;
	AIManager& mAIManager;
	SceneManager& mSceneManager;
	sf::Clock mTimeSinceLastSkipPress;
	int mTimesPressedSkip;
};

}