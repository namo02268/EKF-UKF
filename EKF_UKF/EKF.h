#pragma once

#include "funcDef.h"

class EKF {
private:
	double Q, R;		// �G�����U
	double G;			// �J���}���Q�C��
	double P;			// �덷�����U�s��
	double xhat;		// ��Ԑ���l

public:
	// �R���X�g���N�^�E�f�X�g���N�^
	EKF(double Q, double R, double P0, double xhat0)
		: Q(Q), R(R), P(P0), xhat(xhat0) {}
	~EKF() {}

	// ���ԍX�V
	double update(double y, double k) {
		// �\���X�e�b�v 
		double xhatm = F(xhat, k);
		double Pm = A(xhat) * P * A(xhat) + B * Q * B;

		// �t�B���^�����O�X�e�b�v
		G = Pm * C(xhatm) / (C(xhatm) * Pm * C(xhatm) + R);
		xhat = xhatm + G * (y - H(xhatm));
		P = (1 - G * C(xhatm)) * Pm;
		return xhat;
	}

};