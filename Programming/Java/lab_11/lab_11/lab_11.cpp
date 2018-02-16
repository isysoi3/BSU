// lab_11.cpp: определяет точку входа для консольного приложения.
//


#include <iostream>


int main()
{
	int a ,b, gcd;
	std::cout << "Enter numerator: ";
	std::cin >> a;
	std::cout << "Enter denumerator: ";
	std::cin >> b;
	__asm
	{
		mov eax, a
		mov ebx, b
		beg :
			cmp eax, ebx
				je	end_
			jg gr
				sub ebx, eax
				jmp beg
			gr :
				sub eax, ebx
				jmp beg
		end_ :
			mov gcd, eax 
			mov eax, a
			mov edx, 0
			div gcd
			mov a, eax

			mov eax, b
			mov edx, 0
			div gcd
			mov b, eax
			jmp exit
			
	}
		std::cout << a << "/" << b;
	return 0;
}

