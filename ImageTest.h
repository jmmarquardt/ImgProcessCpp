#pragma once

#include <gtest/gtest.h>
#include "src/Image.h"

struct ImageTest : testing::Test
{
	Image* image;
	const char* testSource = "./images/test.jpg";
	ImageTest()
	{
		image = new Image(testSource);
	}

	~ImageTest()
	{
		delete image;
	}
};