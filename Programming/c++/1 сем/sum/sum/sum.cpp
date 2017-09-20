// sum.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>;

using namespace std;
 
int main()
{
    int n;
    int s=0;
 
    cout << "enter number= ";
    cin >> n;
 
    while (n!=0)
    {
        s += n%10;
        n /= 10;
    }
    cout << "sum= " << s << endl;

	system("pause");
    
    return 0;
}

