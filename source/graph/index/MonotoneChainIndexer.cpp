/*
* $Log$
* Revision 1.8  2003/10/15 16:39:03  strk
* Made Edge::getCoordinates() return a 'const' value. Adapted code set.
*
*/
#include "../../headers/graphindex.h"

namespace geos {

vector<int>*
MonotoneChainIndexer::getChainStartIndices(const CoordinateList* pts)
{
	// find the startpoint (and endpoints) of all monotone chains in this edge
	int start=0;
	vector<int>* startIndexList=new vector<int>();
	startIndexList->push_back(start);
	do {
		int last=findChainEnd(pts,start);
		startIndexList->push_back(last);
		start=last;
	} while(start<(int)pts->getSize()-1);
	// copy list to an array of ints, for efficiency
	return startIndexList;
}

/**
* @return the index of the last point in the monotone chain
*/
int MonotoneChainIndexer::findChainEnd(const CoordinateList* pts,int start){
	// determine quadrant for chain
	int chainQuad=Quadrant::quadrant(pts->getAt(start),pts->getAt(start + 1));
	int last=start+1;
	while(last<(int)pts->getSize()) {
		// compute quadrant for next possible segment in chain
		int quad=Quadrant::quadrant(pts->getAt(last - 1),pts->getAt(last));
		if (quad!=chainQuad) break;
		last++;
	}
	return last-1;
}
}

