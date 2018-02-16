#pragma once

namespace MPI
{
	class Timer
	{
		double _startTime;

	public:
		Timer();
		double Seconds() const;
	};
}