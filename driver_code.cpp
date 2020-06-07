#include<iostream>
#include"include/game_components.h"
using namespace std;

int main()
{

	graph *G = new graph();
	item_set *I = new item_set();

	look(I,G);
	std::string inp;

	while(true)
	{
		cout<<"\nEnter command: ";
		getline(cin,inp);
		transform(inp.begin(), inp.end(), inp.begin(), ::tolower);

		if(inp=="stop")
			break;

		doCommand(I,G,inp);	
	}
	
	return 0;

}