#ifndef GRAPHPARSERUTILITIES_H_
#define GRAPHPARSERUTILITIES_H_

#include<vector>
#include<algorithm>
#include<utility>
#include"file-reading.h"


//Node structure definition
struct node
{
	std::string location;
	std::string prompt;
	std::vector<std::pair<std::string,node*>> op;
	int visited;
	void insertNode(node &b);
	void printAll();
};

void node::insertNode(node &b)
{	
	op.push_back({b.location,&b});
}

void node::printAll()
{	
	printf("\n%s",location.c_str());	
	printf("\n%s",prompt.c_str());	
	for(int i=0;i<op.size();i++)
	{
		printf("\n%d. %s",i+1,op[i].first.c_str());		
	}
	printf("\nTimes visited: %i",visited);
	printf("\n");	
}








//Graph generation
void getGraph(std::vector<node> &nodes)
{
	std::string inpfilestr = ".\\world_components\\game_map.txt";
	std::vector<std::vector<std::string>> tags = parseFile(inpfilestr);
	nodes.resize(tags.size());

	for(int i=0;i<tags.size();i++)
	{		
		nodes[i].location = tags[i][0];
		nodes[i].prompt = tags[i][1];
		nodes[i].visited = 0;
	}	


	std::string nodeLocation;
	std::vector<node>::iterator itr;

	for(int i=0;i<nodes.size();i++)
	{
		for(int j=2;j<tags[i].size();j++)
		{
			nodeLocation = tags[i][j];
			auto pred = [=](const node &thenode)
			{
				return thenode.location == nodeLocation;
			};
			itr = std::find_if(nodes.begin(),nodes.end(),pred);
			nodes[i].insertNode(*itr);
		}
	}	
}








//Graph class definition
class graph
{	
	node *current;
	node inventory;
	std::vector<node> n;	
public:	
	graph();
	~graph();
	void printGraph();
	int countNodes() const;
	void getLocation();
	void moveTo(const std::string &str);
	node* getCurrent();
	node* getInventory();
};

graph::graph()
{		
	getGraph(n);
	current = &n[0];
	current->visited++;		

	inventory.location = "Inventory";
	inventory.prompt = "This is your inventory. All your items shall be stored here";
	inventory.visited = 0;	
}

graph::~graph()
{	
	delete current;
	n.clear();
	n.shrink_to_fit();
}

void graph::printGraph()
{
	for(int i=0;i<n.size();i++)
		n[i].printAll();
}

int graph::countNodes() const
{
	return n.size();
}

void graph::getLocation()
{
	printf("\n%s",current->location.c_str());	
}

void graph::moveTo(const std::string &str)
{
	int flag=0;
	for(int i=0;i<current->op.size();i++)	
		if(current->op[i].first == str)
		{
			current = current->op[i].second;	
			current->visited++;
			flag=1;
		}
	if(flag==0)
		printf("\nI dont know where %s is\n",str.c_str());	
}

node* graph::getCurrent()
{
	return current;
}

node* graph::getInventory()
{
	return &inventory;
}

#endif