#pragma once

namespace Running
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: _time(time)
		{
		}

		operator float() const { return _time; }
		
		inline float GetSeconds() const { return _time; }
		inline float GetMilliseconds() const { return _time * 1000.0f; }
		// todo: override +=
	private:
		float _time;
	};
}
