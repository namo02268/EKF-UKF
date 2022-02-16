#pragma once

#define F(x, k) 0.2*x+25.0*x/(1+x*x)+8.0*cos(1.2*k)
#define H(x) 1.0/20.0*x*x
#define A(x) 0.2+25*(1-x*x)/pow((1+x*x),2)
#define B 1.0
#define C(x) x/10