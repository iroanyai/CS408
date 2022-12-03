//
//  HeightMap.cpp
//

#include <fstream>
#include <iostream>
#include <iomanip>

#include "GetGlut.h"
#include "Random.h"
#include "ObjLibrary/Vector3.h"
#include "ObjLibrary/TextureManager.h"


#include "Constants.h"
#include "HeightMap.h"

using namespace std;

HeightMap :: HeightMap () :
	rows(1),
	columns(1)
{
	grid[0][0] = 0.0;
}


HeightMap :: HeightMap (string filename)
{
	ifstream input;
	input.open(filename.c_str());
	if (!input)
	{
		cout << "Can\'t open file " << filename << endl;
		exit(1);
	}

	input >> rows;
	input >> columns;
	if (rows > HEIGHT_MAP_MAX || columns > HEIGHT_MAP_MAX)
	{
		cout << "Dimensions of heightmap too big for program " << rows << " " << columns << endl;
		exit(1);
	}
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < columns; j++)
		{
			input >> grid[i][j];
			// cout << setw(8) << grid[i][j];
			if (!input)
			{
				cout << "Not enough data in heightmap at row " << i << " column " << j << endl;
				exit(1);
			}
		}
		// cout << endl;
	}
}

HeightMap :: HeightMap (const HeightMap& original) : 
	rows(original.rows),
	columns(original.columns)
{
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < columns; j++)
		{
			grid[i][j] = original.grid[i][j];
		}
	}
}

HeightMap :: ~HeightMap ()
{
}

HeightMap& HeightMap :: operator= (const HeightMap& original)
{
	if(&original != this)
	{
		rows = original.rows;
		columns = original.columns;
		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < columns; j++)
			{
				grid[i][j] = original.grid[i][j];
			}
		}
	}
	return *this;
}


void HeightMap :: draw () const
{
	glPushMatrix();
		glScaled(WORLD_SIZE / (columns - 1), VERTICAL_CONVERSION, WORLD_SIZE / (rows - 1));
	
		glColor3d(1.0, 1.0, 1.0);
		glEnable(GL_TEXTURE_2D);
		TextureManager::activate("sand.bmp");
		for(unsigned int k = 0; k < rows - 1; k++)
		{
			glBegin(GL_TRIANGLE_STRIP);
				for(unsigned int i = 0; i < columns; i++)
				{
					glTexCoord2d(i, 1);   glVertex3d(i, grid[k  ][i], k    );
					glTexCoord2d(i, 0);   glVertex3d(i, grid[k+1][i], k + 1);
				}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
