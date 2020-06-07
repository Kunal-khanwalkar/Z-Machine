#ifndef GAMECOMPONENTS_H_
#define GAMECOMPONENTS_H_

#include<sstream>
#include"graph-parser-utilities.h"
#include"item-utilities.h"


//Helper Functions
bool isItemAtPlace(item_set* I, graph* G, std::string itm)
{

	std::vector<item> is(I->getItemset());

	for(int i=0; i<is.size(); i++)	
		if(itm.compare(is[i].name) == 0)		
			if(is[i].place == G->getCurrent()->location)
				return true;
	
	return false;
}


bool isItemInInventory(item_set* I, graph* G, std::string itm)
{

	std::vector<item> is(I->getItemset());

	for(int i=0; i<is.size(); i++)	
		if(itm.compare(is[i].name) == 0)		
			if(is[i].place == G->getInventory()->location)
				return true;
	
	return false;
}



//Action Functions
void look(item_set* I, graph* G)
{
	G->getCurrent()->printAll();

	std::vector<item> is(I->getItemset());
	int cnt=0;

	for(int i=0;i<is.size();i++)	
		if(is[i].place == G->getCurrent()->location)
		{
			printf("%s\n", is[i].name.c_str());			
			cnt++;
		}

	if(cnt==0)
		printf("\nI don't see anything useful\n");		
}


void checkInventory(item_set* I, graph* G)
{
	std::vector<item> is(I->getItemset());
	int cnt = 0;
	
	printf("\n%s\n",G->getInventory()->prompt.c_str());
	for(int i=0;i<is.size();i++)	
		if(is[i].place == G->getInventory()->location)		
		{
			printf("- %s\n",is[i].name.c_str());			
			cnt++;
		}

	if(cnt==0)
		printf("\n-- Inventory empty\n");
}



void examine(item_set* I, graph* G, std::string itm)
{
	if(!isItemAtPlace(I,G,itm) && !isItemInInventory(I,G,itm))
	{
		printf("\nNo %s to examine\n", itm.c_str());		
		return;		
	}

	item* theitm = I->getItem(itm);
	theitm->printAll();
}


void goTo(item_set* I, graph* G, std::string inp)
{
	G->moveTo(inp);
	look(I,G);
}


void moveToInventory(item_set* I, graph* G, std::string itm)
{
	if(!isItemAtPlace(I,G,itm))
	{		
		printf("\nI don't see any %s\n", itm.c_str());
		return;
	}

	item* theitm = I->getItem(itm);

	if(theitm->portable == false)
	{
		printf("\nI cannot pick that up\n");
		return;
	}

	theitm->place = G->getInventory()->location;

	printf("\nPicked up: %s\n",itm.c_str());	
}


void dropFromInventory(item_set* I, graph* G, std::string itm)
{
	if(!isItemInInventory(I,G,itm))
	{		
		printf("\nI don't have %s\n", itm.c_str());
		return;
	}

	item* theitm = I->getItem(itm);
	theitm->place = G->getCurrent()->location;

	printf("\nDropped item: %s\n", itm.c_str());	
}



//Commands Input, Array of verbs with respective Function Pointers
struct verb_t {
	std::string verb;\
	void (*fun1)(item_set *I, graph *G);
	void (*fun2)(item_set *I, graph* G, std::string inp);	
};

struct verb_t verb[] = {
	{ "go", nullptr, goTo},
	{ "look", look, nullptr},
	{ "examine", nullptr, examine},
	{ "inventory", checkInventory, nullptr},
	{ "take", nullptr, moveToInventory},
	{ "drop", nullptr, dropFromInventory}
};


void doCommand(item_set* I, graph* G, std::string inp)
{		
	std::vector<std::string> words;
	std::stringstream tokenizer(inp);
	std::string word;

	while(getline(tokenizer,word,' '))	
		words.push_back(word);		
	
	int flag=0, i;
	for(i=0; i<sizeof(verb)/sizeof(verb_t); i++)
		if(words[0].compare(verb[i].verb) == 0)
		{
			flag = 1;
			break;
		}

	if(flag==0)
	{
		printf("\nI don't know what that means\n");
		return;
	}

	if(words.size()==1)
		verb[i].fun1(I,G);
	else
		verb[i].fun2(I,G,words[1]);

}



#endif