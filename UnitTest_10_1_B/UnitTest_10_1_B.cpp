#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_10_1_B/lab_10_1_B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest101B
{
	TEST_CLASS(UnitTest101B)
	{
	public:
		
		TEST_METHOD(TestThreeStudents_AllFunctions)
		{
			const int N = 3;
			Student p[N]{};

			p[0].prizv = "Іваненко";
			p[0].kurs = 1;
			p[0].speciality = Komp_Nauky;
			p[0].fizyka = 5;
			p[0].matematyka = 4;
			p[0].prohram = 3;

			p[1].prizv = "Коваленко";
			p[1].kurs = 2;
			p[1].speciality = Informatyka;
			p[1].fizyka = 3;
			p[1].matematyka = 3;
			p[1].chyselni_metody = 4;

			p[2].prizv = "Ткаченко";
			p[2].kurs = 3;
			p[2].speciality = Matem_Econom;
			p[2].fizyka = 3;
			p[2].matematyka = 5;
			p[2].pedahoh = 3;

			Assert::AreEqual(3, Third(p[0]));
			Assert::AreEqual(4, Third(p[1]));
			Assert::AreEqual(3, Third(p[2]));

			Assert::AreEqual(12, Sum(p[0]));
			Assert::AreEqual(4.0, Average(p[0]), 1e-9);
			Assert::AreEqual(10, Sum(p[1]));
			Assert::AreEqual(10.0 / 3.0, Average(p[1]), 1e-9);
			Assert::AreEqual(11, Sum(p[2]));
			Assert::AreEqual(11.0 / 3.0, Average(p[2]), 1e-9);

			Assert::AreEqual(1, MinAverageIndex(p, N));

			int counts[5]{};
			CountSatisfactory(p, N, counts);

			Assert::AreEqual(2, counts[0]);
			Assert::AreEqual(1, counts[1]);
			Assert::AreEqual(1, counts[2]);
			Assert::AreEqual(0, counts[3]);
			Assert::AreEqual(1, counts[4]);
		}
	};
}
