//============================================================================
// Name        : EEET2448 COMPUTING ENGINEERING 2017A - ASSIGNMENT 2
// Author      : - Bui Khac Phuong Uyen _ s3618720 : Enemies and Levels
//				 - Tran Thi Hong Phuong _ s3623386 : Shooter, Bullets, File Input, Documentation
// Copyright   : Your copyright notice
// Description : This is a shooting game. The player is supposed to shoot the enemies appearing on screen.
//				The shooter is controlled by the player through Region of Interest. There are 5 levels, each time the player shoots an enemy, they enter the next level.
//				Player's name and score are stored in scores.txt file when the game ends.
//
// During the process, we encountered some difficulties such as:
// 		- Due to camera low resolution, it was hard for us to control the ROI/shooter as we wished.
//		- We struggled to display the ending message on the playing window at first, it only appeared one frame and then disappeared.
//	 Fortunately, we found solutions to most difficulties and managed to finish the Assignment.
//============================================================================

#include <cv.h>
#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

using namespace std;
using namespace cv;

int main(  int argc, char** argv ) {

	srand (time(NULL));

		// DEFINE
	int frameCount;
		// Region of Interest
	int xROI = 175, yROI = 300;
	int wROI = 75, hROI = 75;
	    // Center of Mass and Shooter
	int x, y, sMass, xMass, xCOM, yCOM = yROI + hROI/2;
	    // The radius of the Shooter and the Shield
	int life = 5, shield = 25; // radius of inner and outer shooter
	    // Bullet
	int xBullet, yBullet;
	    // Enemy
	int i, dX = 3, dY = 1 + rand()%4;
		// Enemy's Bullet
	int xBE, yBE, rBE = 5, dxBE = 1, dyBE = 3;
	    // Score
	int score = 0;
	    // Condition if there's a shield
	bool available = true;

	Mat frame;
	Mat refFrame;
	Mat diffRef;
	Mat prevFrame;
	Mat diffPrev;
	Mat game = Mat (480, 640, CV_8UC3);

	    // Declare file to store name and score
	FILE *scores;
	char name[50];

	    // Take in player's name before starting
	do {
	    printf("Enter your name: \n");
	    scanf("%s", name);
	} while (name == NULL);

	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened()) {  // check if we succeeded
		return -1;
	}
	cap >> frame;
	frame.copyTo (refFrame);
	int width = frame.cols, height = frame.rows;
	cout <<"Frame dimension: "<< width <<"x"<< height <<endl;

		// Initialise random objects for 5 levels
	int xE[5], yE[5], b[5], g[5], r[5], radius[5];
	for (i = 0; i < 5; i++) {
		xE[i] = 50 + rand() % (width - 100);
		b[i] = 12 + rand() % 230;
		g[i] =  128 + rand() % 128;
		r[i] = 50 + rand() % 205;
		radius[i] = 5 + rand() % 46;
		yE[i] = radius[i] + rand() % 100;
	}
	i = 0;

	namedWindow ("Raw Image",CV_WINDOW_AUTOSIZE);
	//namedWindow ("Difference fr Reference", CV_WINDOW_AUTOSIZE);
	//namedWindow ("Difference fr Previous", CV_WINDOW_NORMAL);
	namedWindow ("Game", CV_WINDOW_AUTOSIZE);

	for(frameCount = 0; frameCount < 100000000; frameCount++) {
			// Set black background for every frame
		rectangle (game, Rect(0,0, width, height), Scalar (0,0,0), -1);

		frame.copyTo (prevFrame);

		cap >> frame; // get a new frame from camera
		absdiff (refFrame, frame, diffRef);
		cvtColor (diffRef, diffRef, CV_BGR2GRAY, 1);
		absdiff (prevFrame, frame, diffPrev);
		cvtColor (diffPrev, diffPrev, CV_BGR2GRAY, 1);

			// CENTER OF MASS
		sMass = 0, xMass = 0;
			for (y = yROI; y < yROI + hROI; y++) {
				for (x = xROI; x < xROI + wROI; x++) {
					sMass += diffPrev.at<unsigned char>(y,x);
					xMass += diffPrev.at<unsigned char>(y,x)*x;
				}
			}

		xCOM = xMass/sMass;
		xROI = xCOM - wROI/2;
		if (xROI < 0) {
			xROI = 0;
		}
		if (xROI + wROI > frame.cols) {
			xROI = frame.cols - wROI;
		}
		if (yROI < 0) {
			yROI = 0;
		}
		if (yROI + hROI > frame.rows) {
			yROI = frame.rows - hROI;
		}

			// BULLETS
			// Initiate bullet every 80 frames
		if (frameCount % 80 == 0) {
			xBullet = xCOM;
			yBullet = yCOM;
		}
			// Draw bullet
		circle (game, Point (xBullet, yBullet), 5, Scalar (255,255,255), -1);
			// Speed of bullet
		yBullet += -20;

			// ENEMIES
		circle (game, Point (xE[i], yE[i]), radius[i],
								Scalar (b[i], g[i], r[i]), 3);

			// LEVELS
			// LEVEL 1 - Static enemy
		if (i == 0) {
				// Display level
			putText (game, "Level 1", Point(10, height - 10), FONT_HERSHEY_PLAIN, 2, Scalar(0,128,255), 2);
			putText (game, "Shoot Target!", Point(200, height - 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,0,0), 2);
		}

			// LEVEL 2 - Enemy moves on X-axis and shoots straight downwards
		if (i == 1) {
				// Display level
			putText (game, "Level 2", Point(10, height - 10), FONT_HERSHEY_PLAIN, 2, Scalar(0,128,255), 2);

				// Keep the enemy move inside the window
			xE[i] += dX;
			if (xE[i] - radius[i] < 0 || xE[i] + radius[i] > width) {
				dX = -dX;
			}

				// Frequency of enemy shot
			if (frameCount % 120 == 0) {
				xBE = xE[i];
				yBE = yE[i];
			}

				// Draw enemy's bullet
			circle (game, Point (xBE, yBE), rBE, Scalar (b[i], g[i], r[i]), -1);

				// Distance between shooter and enemy's bullet
			int distE = round(sqrt(pow(xBE - xCOM, 2) + pow (yBE - yCOM, 2)));

				// If the enemy shoots us, we are damaged and lose shield
			if (distE < rBE + shield && available == true) {
				xBE = -3;
				available = false;
			}

				// If we are shot without shield, we lose
			if (available == false && distE < rBE + life) {
				printf("Game Over!! \n");
				i = -1;
			}

				// Speed of enemy's bullet
			yBE += 4;
		}

			// LEVEL 3 - Enemy bounces against walls and shoots in random direction
		if (i == 2) {
				// Display level
			putText (game, "Level 3", Point(10, height - 10), FONT_HERSHEY_PLAIN, 2, Scalar(0,128,255), 2);

				// Keep the enemy moving inside the window
			xE[i] += dX;
			yE[i] += -dY;
			if (xE[i] - radius[i] < 0) {
				xE[i] = radius[i];
				dX = -dX;
			}
			 if (xE[i] + radius[i] > width) {
				xE[i] = width - radius[i];
				dX = -dX;
			 }
			if (yE[i] - radius[i] < 0) {
				yE[i] = radius[i];
				dY = -dY;
			}
			if (yE[i] + radius[i] > height) {
				yE[i] = height - radius[i];
				dY = -dY;
			}
			if (xBE < 0 || xBE > width || yBE < 0 || yBE > height) {
				xBE = xE[i];
				yBE = yE[i];
				dxBE = (dxBE + 1) % 11 - 5;
				do {
					dyBE = -5 + rand()%11;
				} while (dyBE > -2 && dyBE < 3);
			}

				// Draw enemy's bullet
			circle (game, Point (xBE, yBE), rBE, Scalar (b[i], g[i], r[i]), -1);

				// Distance between shooter and enemy's bullet
			int distE = round(sqrt(pow(xBE - xCOM, 2) + pow (yBE - yCOM, 2)));

				// If the enemy shoots us, we are damaged and lose shield
			if (distE < rBE + shield && available == true) {
				xBE = -3;
				available = false;
			}

				// If we are shot without shield, we lose
			if (available == false && distE < rBE + life) {
				printf("Game Over!! \n");
				i = -1;
			}

				// Speed of enemy's bullet
			xBE += dxBE;
			yBE += dyBE;
		}

			// LEVEL 4 - Enemy with random radius with touch and bullet destruction
		if (i == 3) {
			    // Display level
			putText (game, "Level 4", Point(10, height - 10), FONT_HERSHEY_PLAIN, 2, Scalar(0,128,255), 2);

				// Radius of the enemy
			radius[i] = (radius[i] + 3) % 100;

				// Keep the enemy moving inside the window
			xE[i] = width/2 +150;
			yE[i] = height/2;
			if (xBE < 0 || xBE > width || yBE < 0 || yBE > height) {
				xBE = xE[i];
				yBE = yE[i];
				dxBE = (dxBE + 3) % 11 - 5;
				do {
					dyBE = -6 + rand()%14;
				} while (dyBE > -3 && dyBE < 5);
			}

				// Draw enemy's bullet
			circle (game, Point (xBE, yBE), rBE, Scalar (b[i], g[i], r[i]), -1);


				// Distance between shooter and enemy's bullet
			int distE = round(sqrt(pow(xBE - xCOM, 2) + pow (yBE - yCOM, 2)));

				// Distance between shooter and enemy
			int distM = round(sqrt(pow(xE[i] - xCOM, 2) + pow (yE[i] - yCOM, 2)));

				// If the enemy shoots us, we are damaged and lose shield
			if (distE < rBE + shield && available == true) {
				xBE = -3;
				available = false;
			}
				// If the shooter touches the enemy, we are damaged adn lose shield
			if (distM < radius[i] + shield && available == true) {
				dX = -dX;
				dY = -dY;
				available = false;
			}

				// If we are shot or touched without shield, we lose
			if (available == false) {
				if ( distE < rBE + life || distM < radius[i] + life) {
					printf("Game Over!! \n");
					i = -1;
				}
			}

				// Speed of enemy's bullet
			xBE += dxBE;
			yBE += dyBE;
		}

			// LEVEL 5 - Enemy bounces and shoots, destroyed by bullets and touch
		if (i == 4) {
			    // Display level
			putText (game, "Level 5", Point(10, height - 10),
					FONT_HERSHEY_PLAIN, 2, Scalar(0,128,255), 2);

				// Radius of the enemy
			radius[i] = 75;

				// Keep the enemy moving inside the window
			xE[i] += dX*2;
			yE[i] += dY*2;
			if (xE[i] - radius[i] < 0) {
				xE[i] = radius[i];
				dX = -dX;
			}
			if (xE[i] + radius[i] > width) {
				xE[i] = width - radius[i];
				dX = -dX;
			}
			if (yE[i] - radius[i] < 0) {
				yE[i] = radius[i];
				dY = -dY;
			}
			if (yE[i] + radius[i] > height) {
				yE[i] = height - radius[i];
				dY = -dY;
			}
			if (xBE < 0 || xBE > width || yBE < 0 || yBE > height) {
				xBE = xE[i];
				yBE = yE[i];
				dxBE = (dxBE + 1) % 11 - 5;
				do {
					dyBE = -5 + rand()%11;
				} while (dyBE > -2 && dyBE < 3);
			}

				// Draw enemy's bullet
			circle (game, Point (xBE, yBE), rBE, Scalar (b[i], g[i], r[i]), -1);

				// Distance between shooter and enemy's bullet
			int distE = round(sqrt(pow(xBE - xCOM, 2) + pow (yBE - yCOM, 2)));

				// Distance between shooter and enemy
			int distM = round(sqrt(pow(xE[i] - xCOM, 2) + pow (yE[i] - yCOM, 2)));

				// If the enemy shoots us, we are damaged and lose shield
			if (distE < rBE + shield && available == true) {
				xBE = -3;
				available = false;
			}

				// If the shooter touches the enemy, we are damaged and lose shield
			if (distM < radius[i] + shield && available == true) {
				dX = -dX;
				dY = -dY;
				available = false;
			}

				// If we are shot without shield, we lose
			if (available == false) {
				if (distE < rBE + life || distM < radius[i] + life) {
					printf("Game Over!! \n");
					i = -1;
				}
			}

				// Speed of enemy's bullet
			xBE += dxBE;
			yBE += dyBE;
		}

			// LEVEL UP
		int dist = round(sqrt(pow(xBullet - xE[i], 2) + pow (yBullet - yE[i], 2)));
		if (dist < radius[i] + 5) {
			i++;
			score ++;
		}

			// VICTORY
		if (i == 5) {
			putText(game, "You Win!!", Point(220,height/2), FONT_HERSHEY_PLAIN, 2, Scalar(255,0,0), 2);
		}

			// LOSS
		if (i == -1) {
			putText(game, "Game Over!!", Point(220,height/2), FONT_HERSHEY_PLAIN, 2, Scalar(255,0,0), 2);
		}

			// DRAW SHOOTER
		circle (game, Point(xCOM, yCOM), life, Scalar (0,0, 255), 3);
		circle (frame, Point(xCOM, yCOM), life, Scalar (0,0, 255), 3);

			// DRAW SHIELD
		if (available) {
			circle (game, Point (xCOM, yCOM), shield, Scalar (255,255,255), 3);
			circle (frame, Point (xCOM, yCOM), shield, Scalar (255,255,255), 3);
		}

			// SHOW ON WINDOWS
		imshow("Raw Image", frame);
		imshow ("Game", game);

		if (waitKey(20) >= 0) {
			break;
		}
	}

		// PRINT SCORE ON CMD
	printf("Score: %d", score);

		// STORE NAME AND SCORE ON TEXT FILE
	scores = fopen("scores.txt", "a");
	fprintf(scores, "Name: %s - Score: %d \n", name, score);
	fclose(scores);

	return 0;
}
