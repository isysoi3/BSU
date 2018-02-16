__kernel void TestKernel(__global int* counters)
{
	__private int counterPrivate;
	__local int counterLocal1;
	__local int counterLocal2;

	int indexGlobal = get_global_id(0);
	int indexLocal = get_local_id(0);
	int sizeLocal = get_local_size(0);

	counterPrivate = 0;
	counterLocal1 = 0;
	counterLocal2 = 0;

	counterPrivate += sizeLocal;
	++counterLocal1;
	atomic_inc(&counterLocal2);

	counters[3 * indexGlobal] = counterPrivate;
	counters[3 * indexGlobal + 1] = counterLocal1;
	counters[3 * indexGlobal + 2] = counterLocal2;
}