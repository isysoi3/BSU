float Calculate(float a, float b)
{
	return a + b;
}

__kernel void TestKernel(
	__global const float* v1,
	__global const float* v2,
	__global float* result,
	int size)
{
	int index = get_global_id(0);
	if (index >= size) return;
	result[index] = Calculate(v1[index], v2[index]);
}