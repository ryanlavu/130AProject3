#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
	GraphGenerator graphs(argv[1]
			//insert into heaps
			ifstream insertFile(argv[1]);
			while(getline(insertFile, query))
			{
				if(query.empty())
					break;
			}	
			insertFile.close();

}
