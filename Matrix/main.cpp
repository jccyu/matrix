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
	const size_t ratio = 1.5;
	const size_t width = 80;
	const size_t height = 30;
	const double cdist = 10;
	TextCamera tc{ ratio, width, height, cdist, {0, 0, 0}, 0 };

	tc.AddPoint({ 0,0,10 });
	tc.Render();

	string cmd;
	while (true) {
		cin >> cmd;
		if (cmd == "f") {
			tc.Move({ 0, 0, 1 });
		}
		else if (cmd == "b") {
			tc.Move({ 0, 0, -1 });
		}
		else if (cmd == "a") {
			tc.Turn(0, PI / 8);
		}
		else if (cmd == "d") {
			tc.Turn(0, -PI / 8);
		}
		else if (cmd == "w") {
			tc.Turn(PI / 8, 0);
		}
		else if (cmd == "s") {
			tc.Turn(-PI / 8, 0);
		}
		tc.Render();
	}
}
