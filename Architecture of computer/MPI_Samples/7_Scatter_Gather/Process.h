#pragma once

namespace MPI
{
	const int MasterRank = 0;

	class Process
	{
		int _processCount;
		int _rank;

	public:
		Process();
		~Process();

		int ProcessCount() const;
		int Rank() const;
		bool IsMaster() const;
	};
}