#pragma once
#include "Vec.h"
#include "Shapes.h"
class Cell {
public:
	Color color;
	float mass;
	float v;
	float density;
};

class Gas {

	const int rows = 500;
	const int cols = 500;

	Cell*** cells;

	float totalMass = 0;

public:
	Gas() {
		cells = new Cell** [rows];
		for (int i = 0; i < rows; i++) {
			cells[i] = new Cell*[cols];
		}

		init();
	}


	void init() {
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				Cell* cell = new Cell();
				cell->color.r = (float)232 / 255;
				cell->color.g = (float)232 / 255;
				cell->color.b = (float)232 / 255;
				cell->color.a = 1;

				int i = rand() % 20;

				if (i > 18) {
					cell->density = 0;
				}
				else {
					cell->density = Utils::randomFloat(-3, 3);
				}

				float density = cell->density;
				totalMass += cell->density;

				

				cell->color.r = density;
				cell->color.g = density * density * 0.005;
				cell->color.b = density * density * density * 0.1;

				cells[row][col] = cell;
			}
		}
	}

	void display(float dt) {


		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				Cell* cell = cells[row][col];

				cell->density = ((1 - 3 * dt) * cell->density) * 1;
				if (cell->density <=  0.1 && cell->density >= -0.1 && cell->density != 0) {
					cell->density = Utils::randomFloat(-3, 3);
				}

				float density = cell->density;
				//cell->color.r = density  * density * 0.8;
				//cell->color.g = density  * density * 0.8;
				//cell->color.b = density  * density * 0.8;
				cell->color.r = density;
				cell->color.g = density * density * 0.005;
				cell->color.b = density * density * density * 0.1;
				cell->color.a = 1 - exp(-2 * col * cell->density / (3 * 3.14 * 40 * 40));
				cell->color.a = density * 0.02;
				int r = 1 + row;
				int c = 1 + col;
				

				if (r < 0 || r > rows - 1 || c < 0 || c > col - 1) {
					continue;
				}
	/*			Cell* tmp = cells[row][col];
				cells[row][col] = cells[r][c];
				cells[r][c] = tmp;*/

				/*if (cell->density != 0) {
					float k = 0.1;
					int r = (sqrt(3 * dt * k) / (float)totalMass);
					int c = (sqrt(3 * dt * k) / (float)totalMass);
					cell->density = (sqrt(3 * dt * k) / (float)totalMass);
					if (r > 0) {
						r = 20;
						printf("%d %d \n", r, c);
					}
					
				}*/
				
			}
		}

		//glColor4f(0,1,0,1);
		glBegin(GL_POINTS);
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				Cell* cell = cells[row][col];
				glColor4f(cell->color.r, cell->color.g, cell->color.b, cell->color.a);
				glVertex3f(col,row,0);

			}
		}
		glEnd();
	}

};