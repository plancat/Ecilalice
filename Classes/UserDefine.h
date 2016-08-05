#pragma once

#define D_DESIGN_WIDTH 768
#define D_DESIGN_HEIGHT 1280

#define D_WINDOWS_SHOW 0.55

#define D_GAME_NAME "Alice"


//Lerp ÇÔ¼ö
template<typename T>
inline T Lerp(T value1, T value2, float amount)
{
	return T(value1 + ((T)(value2 - value1) * amount));
}
