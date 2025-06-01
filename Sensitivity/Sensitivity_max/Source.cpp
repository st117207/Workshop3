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
	for (int i = 0; i < rows; i++)
	{
		int exponent1 = static_cast<int>(std::floor(std::log10(std::abs(res[i]))));
		double scale1 = std::pow(10, 1 - exponent1);
		float temp = round(res[i] * scale1) / scale1;
		sum += temp;
	}
	return sum / (rows);
}
float deviation(float res[], float cols, float rows)
{
	int exponent1 = static_cast<int>(std::floor(std::log10(std::abs(average_value(res, cols, rows)))));
	double scale1 = std::pow(10, 1 - exponent1);
	float average = round(average_value(res, cols, rows) * scale1) / scale1;
	float sum = 0;
	for (int i = 1; i < rows - 1; i++)
	{
		int exponent1 = static_cast<int>(std::floor(std::log10(std::abs(res[i]))));
		double scale1 = std::pow(10, 1 - exponent1);
		float temp = round(res[i] * scale1) / scale1;
		sum += pow(temp - average, 2);
	}
	return sqrt(sum / ((rows - 2) * ((rows - 2) - 1)));
}
float coefficient(float res[], float cols, float rows)
{
	int exponent1 = static_cast<int>(std::floor(std::log10(std::abs(average_value(res, cols, rows)))));
	double scale1 = std::pow(10, 1 - exponent1);
	float averageS_max = round(average_value(res, cols, rows) * scale1) / scale1;
	float averageS_y = 0.6;
	return averageS_max / averageS_y;
}
float errorK(float** arr, float res[], float cols, float rows)
{
	float S_y = 0.60;
	float S_y_max = 300;
	float S_y_error = 0.012;
	float S_y_max_error = deviation(res, cols, rows);
	float K_error = pow(pow(1 / S_y, 2) * pow(S_y_max_error, 2) + pow(-(S_y_max / pow(S_y, 2)), 2) * pow(S_y_error, 2), 0.5);
	return K_error;
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
	outputFile << "Максимальный коэффициент усиления - " << std::setprecision(2) << coefficient(res, cols, rows) << std::endl;
	outputFile << "Пошрешность максимального коэффициента усиления - " << std::setprecision(2) << errorK(arr, res, cols, rows) << std::endl;


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
