// C++ program to convert a decimal 
// number to binary number 

#include <iostream> 
using namespace std; 

// function to convert decimal to binary 
int *decToBinary(int n) 
{ 
	// array to store binary number 
	static int binaryNum[10]; 

	// counter for binary array 
	int i = 0; 
	while (n > 0) { 

		// storing remainder in binary array 
		binaryNum[i] = n % 2; 
		n = n / 2; 
		i++; 
	} 

	// printing binary array in reverse order 
	for (int j = i - 1; j >= 0; j--) 
		cout << binaryNum[j]<<endl; 

return binaryNum ;
} 

// Driver program to test above function 
int main() 
{ 
	int *k;
	int n = 17; 
	k=decToBinary(n); 
cout<<k<<endl;
	return 0; 
} 
