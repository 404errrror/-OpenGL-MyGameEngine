#pragma once
class Random
{
public:
	Random();
	~Random();

	/// <summary>
	/// min부터 max까지 랜덤값을 반환합니다. (min과 max를 포함합니다.)
	/// </summary>
	static int		Range(int min, int max);
	/// <summary>
	/// min부터 max까지 랜덤값을 반환합니다. (min과 max를 포함합니다.)
	/// </summary>
	static float	Range(double min, double max);
};

