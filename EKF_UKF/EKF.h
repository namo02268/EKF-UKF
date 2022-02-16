#pragma once

#include "funcDef.h"

class EKF {
private:
	double Q, R;		// 雑音分散
	double G;			// カルマンゲイン
	double P;			// 誤差共分散行列
	double xhat;		// 状態推定値

public:
	// コンストラクタ・デストラクタ
	EKF(double Q, double R, double P0, double xhat0)
		: Q(Q), R(R), P(P0), xhat(xhat0) {}
	~EKF() {}

	// 時間更新
	double update(double y, double k) {
		// 予測ステップ 
		double xhatm = F(xhat, k);
		double Pm = A(xhat) * P * A(xhat) + B * Q * B;

		// フィルタリングステップ
		G = Pm * C(xhatm) / (C(xhatm) * Pm * C(xhatm) + R);
		xhat = xhatm + G * (y - H(xhatm));
		P = (1 - G * C(xhatm)) * Pm;
		return xhat;
	}

};