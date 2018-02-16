#pragma once

class Matrix
{
public:
	int Rows;
	int Columns;
	int* Data;

	Matrix(int rows, int columns, int* data) : Rows(rows), Columns(columns), Data(data) { }

	void Dispose()
	{
		delete[] Data;
		Data = nullptr;
	}

	int Get(int i, int j) const
	{
		return Data[i * Columns + j];
	}

	Matrix Transpose() const
	{
		auto data = new int[Rows * Columns];
		for (auto i = 0; i < Rows; ++i)
		{
			for (auto j = 0; j < Columns; ++j)
			{
				data[j * Rows + i] = Get(i, j);
			}
		}
		return Matrix(Columns, Rows, data);
	}
};