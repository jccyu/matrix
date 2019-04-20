#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

#include "camera.h"
using namespace std;

int main(int argc, char **argv) {
	if (argc > 1 && strcmp(argv[1], "-help") == 0) {
		cout << "Usage: matrix [OPTION...]" << endl;
		cout << endl;
		//cout << "  -o  <options>" << endl;
		return 0;
	}

	// init
	const double PI = M_PI;
	const double ratio = 1.5;
	const size_t width = 80;
	const size_t height = 30;
	const double cdist = 10;
	TextCamera tc{ ratio, width, height, cdist, {0, 0, 0}, 0 };

	tc.AddPoly({ { 0, 0, 10 }, { 0, 5, 10 }, { 5, 5, 10 } });
	tc.Render();

	char cmd;
	while (true) {
		cin >> cmd;
		switch (cmd)
		{
		case 'w': tc.Move({ 0, 0, 1 }); break;
		case 'a': tc.Move({ -1, 0, 0 }); break;
		case 's': tc.Move({ 0, 0, -1 }); break;
		case 'd': tc.Move({ 1, 0, 0 }); break;
		case 'i': tc.Turn(-PI / 8, 0); break;
		case 'j': tc.Turn(0, PI / 8); break;
		case 'k': tc.Turn(PI / 8, 0); break;
		case 'l': tc.Turn(0, -PI / 8); break;
		default: break;
		}
		tc.Render();
	}
}
