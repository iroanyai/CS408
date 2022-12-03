//
//  HeightMap.h
//

#ifndef HeightMap_H
#define HeightMap_H

#include <string>

using namespace std;

class HeightMap
{
public:
	static const unsigned int HEIGHT_MAP_MAX = 100;

public:
	HeightMap ();
	HeightMap (string filename);
	HeightMap (const HeightMap& original);
	~HeightMap ();
	HeightMap& operator= (const HeightMap& original);

	void draw () const;

private:
	unsigned int rows;
	unsigned int columns;
	float grid[HEIGHT_MAP_MAX][HEIGHT_MAP_MAX];
};

#endif
