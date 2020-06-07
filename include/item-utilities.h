#ifndef ITEMUTILITIES_H_
#define ITEMUTILITIES_H_

#include<vector>
#include"file-reading.h"


//Item Structure Definition
struct item 
{
	std::string name;
	std::string description;
	std::string place;
	bool portable;
	void printAll();	
};

void item::printAll()
{
	printf("\n%s",name.c_str());
	printf("\n%s",description.c_str());
	printf("\nLocation: %s",place.c_str());
	printf("\nPortable: %d",portable);
	printf("\n");
}






//Item_set Generation
void getItems(std::vector<item> &items)
{		

	std::string inpfilestr = ".\\world_components\\game_items.txt";
	std::vector<std::vector<std::string>> tags = parseFile(inpfilestr);

	items.resize(tags.size());

	for(int i=0;i<tags.size();i++)
	{		
		items[i].name = tags[i][0];
		items[i].description = tags[i][1];
		items[i].place = tags[i][2];
		items[i].portable = (tags[i][3].compare("true") == 0) ? true : false;
	}	

}







//Item_set class definition
class item_set
{
	std::vector<item> items;
public:
	item_set();
	~item_set();
	void print_items();	
	std::vector<item> getItemset();	

	item* getItem(std::string str);
};

item_set::item_set()
{
	getItems(items);	
}

item_set::~item_set()
{
	items.clear();
	items.shrink_to_fit();
}


void item_set::print_items()
{
	for(int i=0;i<items.size();i++)
		items[i].printAll();
}

std::vector<item> item_set::getItemset()
{
	return items;
}

item* item_set::getItem(std::string str)
{
	int i;
	for(i=0;i<items.size();i++)
		if(str.compare(items[i].name) == 0)	
			break;

	return &items[i];
}


#endif