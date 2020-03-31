#pragma once
namespace Constants {
	const int k_screenHeight{ 800 };
	
	const int k_screenWidth{ 600 };
	
	const int k_snakeBlockSize{ 15 };
	
	const int k_snakeSegmentDistance{ 5 };
	
	const int k_foodBlockSize{ 9 };
	
	const int k_gridSize{ k_snakeBlockSize + k_snakeSegmentDistance };

	const int k_standardGrowAmount{ 1 };
	const int k_specialGrowAmount{ 3 };
	const int k_gobbleGrowAmount{ 5 };

	const int k_AISnakeAmount{ 3 };
	const int k_foodAmount{ 5 };
}