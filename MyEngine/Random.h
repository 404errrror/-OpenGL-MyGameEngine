#pragma once
class Random
{
public:
	Random();
	~Random();

	/// <summary>
	/// min���� max���� �������� ��ȯ�մϴ�. (min�� max�� �����մϴ�.)
	/// </summary>
	static int		Range(int min, int max);
	/// <summary>
	/// min���� max���� �������� ��ȯ�մϴ�. (min�� max�� �����մϴ�.)
	/// </summary>
	static float	Range(double min, double max);
};

