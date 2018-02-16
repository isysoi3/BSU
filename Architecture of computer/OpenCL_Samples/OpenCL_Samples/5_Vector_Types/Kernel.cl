__kernel void TestKernel3(__global int* m1, __global int* m2, __global int* m3, int n, int m, int l)
{
	int i = get_global_id(0);
	int j = get_global_id(1);

	int sum = 0;
	int m1Base = i * m;
	int m2Base = j * m;
	for (int k = 0; k < m; ++k)
	{
		int res = (m1[m1Base + k] % 2) + (m2[m2Base + k] % 2);
		sum += res;
	}
	m3[i * l + j] = sum;
}

__kernel void TestKernel4(__global int* m1, __global int* m2, __global int* m3, int n, int m, int l)
{
	int i = get_global_id(0);
	int j = get_global_id(1);

	int4 sum = (int4)(0, 0, 0, 0);
	int bound = m / 4;
	for (int k = 0; k < bound; ++k)
	{
		int m1Base = i * m + 4 * k;
		int m2Base = j * m + 4 * k;
		int4 v1 = (int4)(m1[m1Base], m1[m1Base + 1], m1[m1Base + 2], m1[m1Base + 3]);
		int4 v2 = (int4)(m2[m2Base], m2[m2Base + 1], m2[m2Base + 2], m2[m2Base + 3]);
		int4 res = (v1 % 2) + (v2 % 2);
		sum += res;
	}
	m3[i * l + j] = sum.s0 + sum.s1 + sum.s2 + sum.s3;
}