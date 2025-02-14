#pragma once

#include <SFML/Graphics.hpp>
#include "Audio/Sound/SoundData/SoundData.hpp"

namespace ph {

class SpatializationManager
{
public:
	void setListenerPosition(const sf::Vector2f listenerPosition) { mListenerPosition = listenerPosition; }
	float getSpatialVolume(const SoundData, const sf::Vector2f soundPosition, const float volume);
private:
	void init(const SoundData, const sf::Vector2f soundPosition, const float volume);
	float getDistanceBetweenListenerAndSoundSource();
	bool isListenerOutOfHearableArea();
	bool isListenerVeryCloseToSoundSource();
	float getMaximalVolume();
	float getVolumeForListenerInDistanceScope();
	float getSpatializationFactor();

private:
	SoundData mSoundData;
	sf::Vector2f mListenerPosition;
	sf::Vector2f mSoundPosition;
	float mVolume;
	float mDistanceBetweenListenerAndSoundSource;
};

}
