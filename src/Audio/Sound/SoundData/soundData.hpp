#pragma once

namespace ph {

struct SoundData
{
	float mVolumeMultiplier;
	float mMaximalFullVolumeDistance;
	float mMaximalHearableDistance;	
	bool mLoop;

	SoundData(const float volumeMultiplier = 1.f, const bool loop = false,
			const float maximalFullVolumeDistance = 0.f, const float maximalHearableDistance = 1000.f);
};

}
