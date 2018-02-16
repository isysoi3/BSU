#include <iostream>

using namespace std;

int func(int number) {
	int result = 0;
	_asm {
		mov eax, number;
		mov ebx, 10;
		cdq;
		div ebx;
		mov result, edx;
		mov ecx, eax;
	begin_:
		cdq;
		div ebx;
		cmp eax, 0;
		je end_;
		mov eax, ebx;
		mov ebx, 10;
		mul ebx;
		mov ebx, eax;
		mov eax, ecx;
		jmp begin_;
	end_:
		mov eax, result;
		mul ebx;
		mov result, eax;
		mov eax, ebx;
		mov ebx, 10;
		div ebx;
		mov ebx, eax;
		mov eax, ecx;
		div ebx;
		add result, eax;
		mov eax, edx;
		mov ebx, 10;
		mul ebx;
		add result, eax;
	}
	return result;
}

int main() {
	cout << "Enter number: ";
	int num;
	cin >> num;
	int result = func(num);
	cout << "Result: " << result << '\n';
	system("pause");
	return 0;
}