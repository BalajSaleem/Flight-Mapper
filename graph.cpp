/**
* Title : Balanced Search Trees , Hashing and Graphs
* Author : Balaj Saleem
* ID: 21701041
* Section : 2
* Assignment : 4
* Description : Provides various operations for a graph.
*/
/** @file graph.cpp
 * An adjacency list representation of an undirected weighted graph. 
*/

#include "graph.h"
/*Do not add new libraries or files*/

Graph::Graph()
{
}  // end constructor

void Graph::addAirport(const string& airportName)
{   /*YOUR IMPLEMENTATION*/


	list<node> lst;														//make an empty list
	//might or might not have to check if its already present.
	map< string, list<node> >::iterator itr = adjList.find(airportName);
	if (itr == adjList.end()) {											//check if its already present or not.
		adjList.insert(pair< string, list<node> >(airportName, lst));		//add the list and string to map
	}
	

}  // end addPerformer

void Graph::addConnection(const string& airport1, const string& airport2, int numOfPassengers)
{   /*YOUR IMPLEMENTATION*/

	//make the nodes to be added
	node nd1;	//node to be added to airport1's list
	nd1.airportName = airport2;
	nd1.numOfPassengers = numOfPassengers;

	node nd2;	//node to be added to airport2's list
	nd2.airportName = airport1;
	nd2.numOfPassengers = numOfPassengers;
	
	map< string, list<node> >::iterator itr;		//make an iterator to point to both airports

	itr = adjList.find(airport1);	//iterator now points to the first airport
	if (itr != adjList.end()) {		//the item is found
		itr->second.push_front(nd1);//add the new node to the list at the start
	}

	itr = adjList.find(airport2);	//iterator now points to the second airport
	if (itr != adjList.end()) {		//the item is found
		itr->second.push_front(nd2);//add the new node to the list at the start
	}


}  // end addConnection

list<string> Graph::getAdjacentAirports(const string& airportName)
{   /*YOUR IMPLEMENTATION*/

	list<string> airports;						//the string list to be returned
	map< string, list<node> >::iterator itr;	//make an iterator to point to the airport
	itr = adjList.find(airportName);			//iterator now points to the first airport
	if (itr != adjList.end()) {					//the item is found
		list<node> airportNodes = itr->second;

		list<node>::iterator lstItr; //make an iterator to point to the first node
		for (lstItr = airportNodes.begin(); lstItr != airportNodes.end(); ++lstItr) {//traverse the list
			airports.push_front(lstItr->airportName);//add the airport name to the list of adjecent airports
		}
	}
	return airports;

}  // end getAdjacentAirports

int Graph::getTotalPassengers(const string& airportName)
{   /*YOUR IMPLEMENTATION*/
	int totalPassengers = 0;
	map< string, list<node> >::iterator itr;	//make an iterator to point to the airport
	itr = adjList.find(airportName);			//iterator now points to the first airport
	if (itr != adjList.end()) {					//the item is found
		list<node> airportNodes = itr->second;

		list<node>::iterator lstItr;			//make an iterator to point to the first node
		for (lstItr = airportNodes.begin(); lstItr != airportNodes.end(); ++lstItr) {//traverse the list
			totalPassengers += lstItr->numOfPassengers;								//add the passengers to total
		}
	}
	return totalPassengers;
}  // end getTotalPassengers


list<string> Graph::findShortestPath(const string& airport1, const string& airport2)
{   /*YOUR IMPLEMENTATION*/
	
	//keep a list of string to mark visited airports
	list<string> visited;		//a list that stores every visited vertice
	list<string> path;			//a list that contains the output minumum path
	map< string, string > predecesors;	//a map of all predecesors of nodes (used to calculate minimum path)
	bool found = false;			//a flag that stops the BFT as soon as airport2 is found

	//make the que for bft
	queue<string> q;
	map< string, list<node> >::iterator itr;	//make an iterator to point to the starting airport
	itr = adjList.find(airport1);				//iterator now points to the first airport
	if (itr == adjList.end()) {
		return path;
	}
	visited.push_front(itr->first);				//add the airport name to the visited pile
	q.push(itr->first);							//add the starting airport to the queue
	while (!q.empty() && !found) {

		string w;								//deque w
		w = q.front();
		q.pop();

		itr = adjList.find(w);					//we need to find adjacent vertices
		bool check = false;						//used to check the visited property of an adjecent vertice
		for (list<node>::iterator lstItr = itr->second.begin(); lstItr != itr->second.end(); lstItr++) { //go through the list
			check = false;
			for (list<string>::iterator lstItr2 = visited.begin(); lstItr2 != visited.end(); ++lstItr2) { //go throught the visited list
				if (lstItr->airportName == *lstItr2) {		//checking in visited list
					check = true;							//the node was visted before
					break;
				}
			}
			//we now know whether it was visited or not
			if (!check) {
				visited.push_front(lstItr->airportName);	//make it visited
				predecesors.insert(pair<string, string>(lstItr->airportName,w)); //add its parent to the predeccesors
				q.push(lstItr->airportName);
				if (lstItr->airportName == airport2) {
					found = true;							//stop the BST if found is true
				}
			}
		}

	}
	//use the predecesors list to generate path
	map< string, string >::iterator itr2;
	string succesor = airport2;				//start from destination airport
	itr2 = predecesors.find(airport2);		//find its parent
	path.push_front(airport2);
	 do{
		itr2 = predecesors.find(succesor);		//find its parent
		path.push_front(itr2->second);			//add the parent to the path
		succesor = itr2->second;				//make parent the sucessor
	 } while (itr2 != predecesors.end() && itr2->second != airport1);
	

	return path;
}  // end findShortestPath

list< pair<string, string> > Graph::findMST()
{   /*YOUR IMPLEMENTATION*/
	list<string> visited;		//a list that stores every visited vertice
	list< pair<string, string> > lst;
	string lowCostEdge;
	string pred;
	int minCost;
	bool check = false;
	map< string, list<node> >::iterator itr = adjList.begin();
	visited.push_front(itr->first); //starting from the first node
	
	while (visited.size() < adjList.size()) { // go through the whole map
		minCost = INT_MAX;
		for (list<string>::iterator vstItr = visited.begin(); vstItr != visited.end(); vstItr++) {
			
			itr = adjList.find(*vstItr); //find the item in visited pile
			for (list<node>::iterator lstItr = itr->second.begin(); lstItr != itr->second.end(); lstItr++){ //go through the node list
				check = false;
				for (list<string>::iterator lstItr2 = visited.begin(); lstItr2 != visited.end(); lstItr2++) {
					if (lstItr->airportName == *lstItr2) {
						check = true;
						break;
					}
				}
				if (!check) {
					if (lstItr->numOfPassengers < minCost) {
						lowCostEdge = lstItr->airportName;
						pred = *vstItr;
						minCost = lstItr->numOfPassengers;
						//visited.push_front(lstItr->airportName);
					}
				}

			}
		}
		visited.push_front(lowCostEdge);
		lst.push_front(pair<string, string>(pred, lowCostEdge));
	}

	return lst;

}  // end findMST

void Graph::deleteAirport(const string& airportName)
{   /*YOUR IMPLEMENTATION*/
	map< string, list<node> >::iterator itr = adjList.find(airportName);
	
	//find all the airports in its nodelist, and delete this aiport from them
	for (list<node>::iterator lstItr = itr->second.begin(); lstItr != itr->second.end(); lstItr++) {//for each node in the list
		map< string, list<node> >::iterator itr2 = adjList.find(lstItr->airportName);		// go to that airports
		for(list<node>::iterator lstItr2 = itr2->second.begin(); lstItr2 != itr2->second.end(); lstItr2++) { //check their list
			if (lstItr2->airportName == airportName) {
				itr2->second.erase(lstItr2);	//remove this airport from their list
				break;
			}
		}
	}

	adjList.erase(airportName);	//erase the airport from the map

}  // end deleteAirport


