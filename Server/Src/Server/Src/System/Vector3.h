#pragma once

namespace Skyrim{
	namespace System
	{
		class Vector3
		{
		public:
			float X,Y,Z;

			float Distance(Vector3& pVec)
			{
				float a = X - pVec.X;
				float b = Y - pVec.Y;
				float c = Z - pVec.Z;
				return sqrt(a*a + b*b + c*c);
			}
		};
	}
}