#include "image.h"
#include <string>

using std::string;

int main(int argc, char* argv[])
{
	const char* testSource = "./images/test.jpg";
	const char* test02_Copy = "./images/testOutput/test_02_copy.jpg";
	const char* test03_copy_blankTopline = "./images/testOutput/test_03_sizeCopyblanked.png";
	const char* test04_newBlank = "./images/testOutput/test_04_newBlank100x100.jpg";
	const char* test05_gray_avg = "./images/testOutput/test_05_gray_avg.png";
	const char* test06_gray_lum = "./images/testOutput/test_05_gray_lum.png";

	// test 1 see if there is an image file and if it can construct an image instance
	Image test(testSource);
	
	// test 2 does test.write create a new image file with test data at specified path/filename
	test.write(test02_Copy);
	
	// test 3 makes a copy of original test data, turns all values white and writes to file
	Image sizeCopyWhite(testSource);
	for (int i = 0; i < sizeCopyWhite.width * sizeCopyWhite.channels; i++)
	{
		sizeCopyWhite.data[i] = 255;
	}
	sizeCopyWhite.write(test03_copy_blankTopline);
	
	// test 4 constructor passing in width, height and channel values creating a blank image of specified size
	Image blank(100, 100, 3);
	blank.write(test04_newBlank);
	
	// test 5 the grayscale_avg function creates a black and white image at the specified path.
	Image gray_avg(testSource);
	gray_avg.grayscale_avg();
	gray_avg.write(test05_gray_avg);

	// test 6 the gray_lum method creates a grayscale luminant image at the specified path
	Image gray_lum(testSource);
	gray_lum.grayscale_lum();
	gray_lum.write(test06_gray_lum);

	return 0;
}
