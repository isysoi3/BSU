#pragma once

namespace MPI
{
	class Process
	{
		int _processCount;
		int _rank;

	public:
		Process();
		~Process();

		int Rank() const;
		int ProcessCount() const;
	};
}