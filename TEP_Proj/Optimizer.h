#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <iostream>
using namespace std;

namespace NGroupingChallenge
{
	class COptimizer
	{
	public:
		virtual ~COptimizer() = 0;
		virtual void vInitialize() = 0;
		virtual void vRun() = 0;
	};

	inline COptimizer::~COptimizer()
	{
		cout<< "~COptimizer"<<endl;
	}

}

#endif