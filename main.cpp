/**
* Title : Balanced Search Trees , Hashing and Graphs
* Author : Balaj Saleem
* ID: 21701041
* Section : 2
* Assignment : 4
* Description : Provides various operations for a graph.
*/
/**
 * CS 202 - HW 4
 * A main file
 * Please make sure that your code compiles and runs with this main file
 */
#include "graph.h"
#include <string>
#include <iostream>
//added for file operations
#include <fstream>
#include <sstream>
/*You can add additional libraries here to read and process the dataset*/

using namespace std;

int main() {
    /*YOUR IMPLEMENTATION*/
	

	string line;
	ifstream readFile;
	readFile.open("flightDataset.txt");

	string airport1;
	string airport2;
	string passengers;
	int psngrs = 0;
	Graph g;


	if (readFile.is_open()) {
		while (getline(readFile, line)) {
			//cout << line << endl;
			int mark1 = line.find_first_of(';');
			int mark2 = line.find_last_of(';');
			int airport2len = (mark2 - mark1) - 1;
			airport1 = line.substr(0, mark1); //parse the first airport
			airport2 = line.substr(mark1 + 1, airport2len);//parse the second airport
			passengers = line.substr(mark2 + 1, line.size());//parse the passengers
			stringstream parser(passengers);
			parser >> psngrs;					//convert the passenger string to an int

			//cout << "--------- " << endl;
			//cout << airport1 << endl;
			//cout << airport2 << endl;																//DEBUGGING LINES
			//cout << to_string(psngrs) << endl;

			//add the collected data to the graph
			g.addAirport(airport1);
			g.addAirport(airport2);
			g.addConnection(airport1, airport2, psngrs);

			//cout << "--------- " << endl;
		}
	}

	cout << "============================================================== " << endl;
	cout << "The graph has been populated using data from flightDataset.txt" << endl;
	cout << "============================================================== " << endl;


	//please note that all queries are case sensitive

	string query = "KIRKWALL";

	cout << "Getting adjacent airports for : " + query << endl;
	list<string> airports = g.getAdjacentAirports(query);
	for (list<string>::iterator lstitr = airports.begin(); lstitr != airports.end(); lstitr++) {
		cout << *lstitr << endl;
	}
	cout << "" << endl;
	cout << "Getting total passengers for : " + query << endl;
	cout << to_string( g.getTotalPassengers(query) ) << endl;
	
	cout << "" << endl;
	cout << "Getting shortest path for : HEATHROW , KIRKWALL"  << endl;

	airports = g.findShortestPath("HEATHROW", "KIRKWALL");
	for (list<string>::iterator lstitr = airports.begin(); lstitr != airports.end(); lstitr++) {
		cout << *lstitr << endl;
	}
	cout << "" << endl;
	cout << "Getting the edges for Minimum Spanning Tree (MST) :" << endl;
	list< pair<string, string> > mstlist = g.findMST();
	mstlist.reverse();
	for (list<pair<string, string>>::iterator lstitr = mstlist.begin(); lstitr != mstlist.end(); lstitr++) {
		cout << lstitr->first + " -> " + lstitr->second << endl;
	}
	cout << "" << endl;
	cout << "+++++++++++++++++++++++++++++++" << endl;
	cout << "Deleting ABERDEEEN :" << endl;
	g.deleteAirport("ABERDEEN");
	cout << "+++++++++++++++++++++++++++++++" << endl;
	cout << "" << endl;
	cout << "Getting the NEW edges for Minimum Spanning Tree (MST) :" << endl;
	list< pair<string, string> > mstlist2 = g.findMST();
	mstlist2.reverse();
	for (list<pair<string, string>>::iterator lstitr = mstlist2.begin(); lstitr != mstlist2.end(); lstitr++) {
		cout << lstitr->first + " -> " + lstitr->second << endl;
	}

	int a;			//just to keep the console open.
	cin >> a;
	return 0;
}
// End of main file
