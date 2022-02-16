#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#include "EKF.h"
#include "funcDef.h"

void makeNoise(std::vector<double>& vec, int seed, double variance);

int main() {
	//----------------問題設定----------------//
	const int N = 50;	// データ数
	double Q = 1;	// システム雑音分散
	double R = 100;	// 観測雑音分散

	//----------------雑音生成----------------//
	std::vector<double> v(N);	// システム雑音
	int seed = 1;				// ノイズのシード値
	makeNoise(v, seed, Q);

	std::vector<double> w(N);	// 観測雑音
	seed = 2;					// ノイズのシード値
	makeNoise(w, seed, R);


	// 初期値
	std::vector<double> x(N);
	std::vector<double> y(N);
	std::vector<double> xhat(N);

	x[0] = 10.0;
	y[0] = H(x[0]);

	double P0 = 1;
	double xhat0 = x[0] + 1;
	EKF ekf(Q, R, P0, xhat0);

	xhat[0] = xhat0;

	// 時間更新
	for (int k = 1; k < N; k++) {
		x[k] = F(x[k - 1], k) + B * v[k - 1];
		y[k] = H(x[k]) + w[k];
		xhat[k] = ekf.update(y[k], k);
	}

	//----------------ファイル出力----------------//
	std::ofstream file("test.csv");
	for (int k = 0; k < N; ++k) {
		file << y[k] << ", " << x[k] << ", " << xhat[k] << std::endl;
	}
}

void makeNoise(std::vector<double>& vec, int seed, double variance) {
	std::mt19937 engine(seed);
	std::normal_distribution<> dist(0.0, sqrt(variance));
	for (auto& itr : vec)
		itr = dist(engine);
}
