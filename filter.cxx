#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int lineNumberReader(){
	int N = 0; // Number of lines
	string line;
	ifstream myfile ("noisy.txt");
	// Read number of lines
	
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			N++;
		}
		myfile.close();
		return N;
	}
	else {
		cout << "Unable to open file";
		return 0;
	}
}

int getData(double p[], const int N){
	// I need to declare the return Type of this function
	// to int, because if the text can't be read,
	// the function returns 0
	ifstream myfile ("noisy.txt");
	if (myfile.is_open()) {
		for( int i=0 ; i<N ; i++){
			// Save every line of the file in p[i]
			myfile >> p[i];
		}
		// Close the file
		myfile.close();
	}
	else {
		cout << "Unable to open file";
		return 0;
	}
}

void filterData(double p[], const int N){
	// Filters data
	double p_minus_one, p_temp;
	// Periodic boundary condition
	p_minus_one = p[N-1];
	
	for(int i=0 ; i<N-2 ; i++){
		p_temp = p[i];
		p[i] = (p_minus_one+p[i]+p[i+1])/3;
		p_minus_one = p_temp;
	}
	// Filter Equation, average over 3
	p[N-1] = (p[N-2] + p[N-1] + p[0])/3;
}

void saveData(double p[], const int N){
	ofstream out("filtered.txt");
	for( int i=0 ; i<N ; i++){
		out << p[i] << endl;
	}
	out.close();
}

int main () {
	// N = Number of lines
	int N;
	// Read out the number of lines in "noisy.txt"
	N = lineNumberReader();
	// Create dynamic Array p
	double* p = new double [N];
	// save the original lab data ("noisy.txt") in p
	getData(p,N);
	// filter the original data and overwrite the original array
	filterData(p,N);
	// Save filtered data to "fitlered.txt"
	saveData(p,N);
	// Delte dynamic Array p
	delete[] p;
	// Everthing worked fine
	return 0;
}

