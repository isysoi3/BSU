__kernel void TestKernel(
	__global unsigned int * Matrix,
	unsigned short int V,
	unsigned short int H,
	const unsigned int color)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
	if (x >= V) return;
	if (y >= H) return;
	unsigned char A, R, G, B, cR, cG, cB, outA, outR, outG, outB;
	unsigned int answer = 0;
	A = Matrix[x*H + y] >> 24;
	R = (Matrix[x*H + y] >> 16) & 255;
	G = (Matrix[x*H + y] >> 8) & 255;
	B = (Matrix[x*H + y]) & 255;
	cR = (color >> 16) & 255;
	cG = (color >> 8) & 255;
	cB = (color)& 255;
	outA = 255;
	outR = (R * A + cR * (255 - A)) / 255;
	outG = (G * A + cG * (255 - A)) / 255;
	outB = (B * A + cB * (255 - A)) / 255;
	answer = answer + outA;
	answer = answer << 8;
	answer = answer + outR;
	answer = answer << 8;
	answer = answer + outG;
	answer = answer << 8;
	answer = answer + outB;
	Matrix[x*H + y] = answer;
}