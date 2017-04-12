// Assumption that nodes are singly connected with each other
#include <iostream>	// Almost always included
#include <iomanip>	// 
#include <cstdlib>		// for rand() function which returns a number from 0 to RAND_MAX
#include <stdio.h>		// dunno what for lec 2b
#include <cstring>		// char str1[6] = "Hello" probably don't need
#include <string>
#include <fstream>		//for reading and writing files
#include <utility>		// for pair template?
#include <map>
#include <set>
#include <vector>

using namespace std;

// declare prototypes here;
void routing(string, int &, string [], int []);
string lowercase(string);
string uppercase(string);


int main(int argc, char *argv[])
{

string all[6] = {"A", "B", "C", "D", "E", "F"};
string final[6];
string hold, hold2;
map<string, pair<string, int>*> nodes;		//data table number 2
string source;
string initialsource;
pair<string, int> shortest;	//string indicates the neighbor that is closest to the source node and int is the total distance
set<string> explored;


int cost[6];
string neighbor[6];	//all neighbors from routing are given as uppercase
int i;
int totalcost = 0;

cout << "Enter the source node" << endl;

cin >> source;

initialsource = uppercase(source);

if( (lowercase(source) == "NULL") ){
	cout << "Invalid source node. Input must be one of the following: A, a, B, b, C, c, D, d, E, e, F, f" << endl;
}

else
{
	explored.insert(uppercase(source));		//stored source as explored

	pair<string, int> *input1 = new pair<string, int>;			// store source in paths		
	input1->first = uppercase(source);
	input1->second = 0;			
	nodes[uppercase(source)] = input1;	


	routing(lowercase(source), i, neighbor, cost);	// neighbors and their costs of source node are now stored in global variables
	//cout << "i equals " << i << endl;
	//cout << "flag routing1" << endl;
	shortest.second = cost[i];		// assume that the last neighbor explored has the shortest route
	//cout << "shortest.second equals " << shortest.second << endl;
	for(int j = 0; j <= i; j++)			// iterates through all neighbors and their costs
	{
		if(neighbor[j] == uppercase(source))			//checks to see if source node is connect to itself
		{
			// do nothing
		}
		else
		{
			if(cost[j] <= shortest.second){			//stores neighbor with the shortest distance from the source node
				shortest.first = neighbor[j];
				shortest.second = cost[j];
				//cout << "shortest.second equals " << shortest.second << " and shortest.first equals " << shortest.first << endl;
			}
			pair<string, int> *input = new pair<string, int>;			// pair stores parent node and total cost			
			input->first = uppercase(source);
			input->second = cost[j];			//make sure we're using j not i;
			nodes[neighbor[j]] = input;			//BE CAREFUL SEGMENTATION FAULT CAN RESULT FROM CALLING MAP THAT DOESN'T EXIST node["node A"]
			//cout << "flag first for loop" << endl;
		}
	}

// neighbors and their costs of source node are now stored in map nodes
// find the node with the shortest route from the source node and go explore his neighbors until all the nodes have been explored


while ( (explored.find("A") == explored.end()) || (explored.find("B") == explored.end()) || (explored.find("C") == explored.end()) || (explored.find("D") == explored.end()) || (explored.find("E") == explored.end()) || (explored.find("F") == explored.end()) )
{
	//cout << "flag while loop" << endl;

	source = shortest.first;		//new source
	//cout << "flag1" << endl;
	//cout << "source equals " << source << endl;
	explored.insert(uppercase(source));		//stored source in explored
	//cout << "flag2" << endl;
	i = 0;
	routing(lowercase(source), i , neighbor, cost);
	//cout << "flag3" << endl;
	shortest.second = 1000000000;	//puts a really high number and hope its the highest
	//cout << "this is the nodes[uppercase(source)]->second " << nodes[uppercase(source)]->second << endl;
	//cout << "this is the shortest.second " << shortest.second << endl;
	//cout << "flag still in while loop" << endl;
	int count = -1;
	//cout << "this is i " << i << endl;
	for(int y = 0; y <= i; y++)
	{
		//cout << "y equals " << y << endl;
		//cout << "flag 2nd for loop" << "\n" << endl;
		totalcost = cost[y] + nodes[source]->second;		//totalcost equals total cost of new source + cost of neighbor
		//cout << "past total " << nodes[source]->second << endl;
		//cout << "total cost for " << neighbor[y] << " is " << totalcost << endl;
		/*if(explored.find(neighbor[y]) == explored.end())		//if not explored, this also checks to see if source is connected to itself
		{
			cout << "flag if not HELLO explored" << endl;*/
			//cout << "neighbor[y] is " << neighbor[y] << endl;
			if(nodes.find(neighbor[y]) != nodes.end())		// if path was already found, they trump paths that have been found
			{

				//cout << "flag if path was already found" << endl;
				if ( nodes[neighbor[y]]->second > totalcost )		//new shorter path is found for node and is updated in existing value in nodes
				{
					//cout << "shorter new path found" << endl;
					//cout << "old path equals " << nodes[neighbor[y]]->second << endl;
					nodes[neighbor[y]]->first = source;		//new parent
					nodes[neighbor[y]]->second = totalcost;		//new cost        updates the shorter path
				}
				else
				{
					//cout << "old path is shorter and equals " << nodes[neighbor[y]]->second << endl;
				}
			}
			else if(nodes.find(neighbor[y]) == nodes.end())		//if path was not found yet
			{
				//cout << "flag if path was not found yet" << endl;
				pair<string, int> *input = new pair<string, int>;		// pair stores parent node and total cost				
				input->first = source;
				input->second = totalcost;			//make sure we're using j not i;
				nodes[neighbor[y]] = input;			//BE CAREFUL SEGMENTATION FAULT CAN RESULT FROM CALLING MAP THAT DOESN'T EXIST node["node A"]
			}
			/*if ( nodes[neighbor[y]]->second < shortest.second )  //checking for overall shortest path, if a node has two paths it uses the shorter one as updated
			{
				shortest.first = neighbor[y];
				shortest.second = nodes[neighbor[y]]->second;
				//cout << "winning at shortest path" << endl;
				//cout << "neighbor[y] equals " << neighbor[y] << " and short path equals " << nodes[neighbor[y]]->second << endl;
			}*/

		/*}*/
		/*else if(explored.find(neighbor[y]) != explored.end())		//if explored
		{
			//cout << "flag if OMG explored" << endl;
			//cout << "neighbor[y] is " << neighbor[y] << endl;
			count++;
			//cout << "what is the count and i " << count << "   :   " << i << endl;
		}
		if(count == i)		//if all the neighbors have been explored
		{*/
			//cout << "flag if all neighbors have been explored" << endl;
			map<string,pair<string, int>*>::iterator it; 
			for(it = nodes.begin(); it!= nodes.end(); it++)
			{
				if( explored.find((it->first)) == explored.end())	//if not explored but listed as neighbor
				{
					if ( nodes[(it->first)]->second < shortest.second )  //checking for overall shortest path, if a node has two paths it uses the shorter one as updated
						{
							shortest.first = it->first;
							shortest.second = nodes[(it->first)]->second;
							//cout << "winning at shortest path" << endl;
							//cout << "neighbor[y] equals " << it->first << " and short path equals " << nodes[(it->first)]->second << endl;
						}
				}
			}
				//iterates over map of neighbors NOT EXPLORED and find shortest one
		/*}*/ //else explored loop

	}   //for second y for loop

}	//for while loop until all the nodes are discovered

	// utilize pair template, map has a find function to check visited nodes, use map of pairs to store total cost and parent node, use deque to store backtracked route, map<string, pair*>, replace pairs if updated

}		// bracket for first else loop



for(int w=0; w < 6; w++)
{

	if(all[w] == initialsource)
	{
		//do nothing			sequence ABCD
	}
	else
	{

		
		hold2 = nodes[all[w]]->first;		//hold2 the parent node	      hold2 = C
		hold = all[w];					// hold = current node	hold = D
		while(hold2 != initialsource)		// while parent node does not equal the source node
		{
			hold = hold2 + hold;		// hold = grandpa node + current string of grandchildren       hold = B + C + D
			hold2 = nodes[hold2]->first;		// parent of the parent grandpa!                hold2 = A
		}
		hold = initialsource + hold;
		final[w] = hold;


	}


}

cout << endl;
cout << endl;
cout << endl;

cout << "The Shortest Path from " << initialsource << " to x" << "   " << "Total Cost" << endl;

for(int d=0; d < 6; d++)
{
	if(all[d] == initialsource)
	{
		//do nothing
	}
	else
	{
	cout << setw(6) << initialsource << " to " << all[d] << ":" << setw(9) << final[d] << setw(17) << nodes[all[d]]->second << endl;
	}
}


map<string,pair<string, int>*>::iterator it2; 
	for(it2 = nodes.begin(); it2!= nodes.end(); it2++)
	{
		delete it2->second;
	}



// when writing routing tables use setw(8) between items
// make sure to delete new pairs
return 0;
}		// bracket for int main

void routing(string node, int &i, string neighbor[], int cost [])  // string node will be given as an lowercase letter
{
	string nlow = "Node " + node;
	string nup = "Node " + uppercase(node);
	char filename[11];
	string str1, str2, str3, str4;
	string trash;
	i = 0; 		//initiallizing

	strcpy (filename, "node_");
	strcat (filename, node.c_str());
	strcat (filename, ".txt");

	ifstream ifile(filename);

	ifile >> str1;
	ifile >> str2;
	str3 = str1 + " " + str2;

	

	if( (str3 != nlow) && (str3 != nup) ){
		cout << "1st Line of Routing Table not formatted as " << nlow << " or " << nup << endl;
	}
	else {
		while (ifile.good()){
			ifile >> str4;
			neighbor[i] = uppercase(str4);
			ifile >> cost[i];
			//cout << "neighbor[i] equals " << neighbor[i] << " and cost[i] equals " << cost[i] << endl;
			ifile >> trash;
			i++;
		}
		//cout << "neighbor[3] equals " << neighbor[3] << " and cost[3] equals " << cost[3] << endl;
		i--;					// decrements once
		/*
		neighbor[i] = "NULL";
		cost[i] = 0;
		*/

	
	}
	ifile.close();

}

string lowercase(string alpha)
{
	if( (alpha == "A") || (alpha == "a") )
		alpha = "a";
	else if( (alpha == "B") || (alpha == "b") )
		alpha = "b";
	else if ( (alpha == "C") || (alpha == "c") )
		alpha = "c";
	else if ( (alpha == "D") || (alpha == "d") )
		alpha = "d";
	else if ( (alpha == "E") || (alpha == "e") )
		alpha = "e";
	else if ( (alpha == "F") || (alpha == "f") )
		alpha = "f";
	else
		alpha = "NULL";

	return alpha;
}

string uppercase(string omega)
{
	if( (omega == "a") || (omega == "A") )
		omega = "A";
	else if( (omega == "b") || (omega == "B") )
		omega = "B";
	else if ( (omega == "c") || (omega == "C") )
		omega = "C";
	else if ( (omega == "d") || (omega == "D") )
		omega = "D";
	else if ( (omega == "e") || (omega == "E") )
		omega = "E";
	else if ( (omega == "f") || (omega == "F") )
		omega = "F";
	else
		omega = "NULL";

	return omega;
}
