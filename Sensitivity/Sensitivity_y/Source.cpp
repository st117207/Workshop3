#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>


void inputdata(float** arr, float cols, float rows)
{
	std::ifstream inputFile("InputData.csv");;
	for (int i = 0; i < rows; i++)
		inputFile >> arr[i][0] >> arr[i][1];

}
void sensitivity_calculation(float** arr, float res[], float cols, float rows)
{
	for (int i = 0; i < rows; i++)
		res[i] = 0.354 * arr[i][0] / arr[i][1];
}
float average_value(float res[], float cols, float rows)
{
	float sum = 0;
	for (int i = 1; i < rows - 1; i++)
	{
		int exponent1 = static_cast<int>(std::floor(std::log10(std::abs(res[i]))));
		double scale1 = std::pow(10, 1 - exponent1);
		float temp = round(res[i] * scale1) / scale1;
		sum += temp;
	}
	return sum / (rows-2);
}
float deviation(float res[], float cols, float rows)
{
	int exponent1 = static_cast<int>(std::floor(std::log10(std::abs(average_value(res, cols, rows)))));
	double scale1 = std::pow(10, 1 - exponent1);
	float average = round(average_value(res, cols, rows) * scale1) / scale1;
	float sum = 0;
	for (int i = 1; i < rows-1; i++)
	{
		int exponent1 = static_cast<int>(std::floor(std::log10(std::abs(res[i]))));
		double scale1 = std::pow(10, 1 - exponent1);
		float temp = round(res[i] * scale1) / scale1;
		sum += pow(temp - average, 2);
	}
	return sqrt(sum / ((rows-2) * ((rows-2) - 1)));
}
void outputdata(float** arr, float res[], float cols, float rows)
{
	sensitivity_calculation(arr, res, cols, rows);
	std::ofstream outputFile("OutputData.csv");
	for (int i = 0; i < rows; i++) {
		outputFile << std::setprecision(2) << res[i] << std::endl;
	}
	outputFile << "-------------------------------------------" << std::endl;
	outputFile << "Среднее значение чувствительности - " << std::setprecision(2) << average_value(res, cols, rows) << std::endl;
	outputFile << "Погрешность чувствительности - " << std::setprecision(2) << deviation(res, cols, rows) << std::endl;


}
int main() {
	float k = 2;
	float n = 5;
	float** data = new float* [n];
	for (int i = 0; i < n; ++i) {
		data[i] = new float[k];
	}
	float result[5];
	inputdata(data, k, n);
	outputdata(data, result, k, n);

	return 0;
}
