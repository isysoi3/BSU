__kernel void TestKernel1(__global int* m1, __global int* m2, __global int* m3, int n, int m, int l)
{
	int i = get_global_id(0);
	int j = get_global_id(1);

	for (int k = 0; k < m; ++k) 
	{
		int r = (m1[i * m + k] % 2 == 0) ^ (m2[k * l + j] % 2 == 0);
		m3[i * l + j] += r;
	}
}

__kernel void TestKernel2(__global int* m1, __global int* m2, __global int* m3, int n, int m, int l)
{
	int i = get_global_id(0);
	int j = get_global_id(1);

	int sum = 0;
	for (int k = 0; k < m; ++k)
	{
		int r = (m1[i * m + k] % 2 == 0) ^ (m2[k * l + j] % 2 == 0);
		sum += r;
	}
	m3[i * l + j] = sum;
}

__kernel void TestKernel3(__global int* m1, __global int* m2, __global int* m3, int n, int m, int l)
{
	int i = get_global_id(0);
	int j = get_global_id(1);

	int sum = 0;
	int m1Base = i * m;
	int m2Base = j * m;
	for (int k = 0; k < m; ++k)
	{
		int r = (m1[m1Base + k] % 2 == 0) ^ (m2[m2Base + k] % 2 == 0);
		sum += r;
	}
	m3[i * l + j] = sum;
}