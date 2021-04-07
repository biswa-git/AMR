#pragma once
#include<Preprocessor.hpp>
#include<Vertex.hpp>
namespace geometry
{
	class Vector
	{
	public:
		static Vector* New(const double& = 0.0, const double& = 0.0, const double& = 0.0);
		Vector(const double& = 0.0, const double& = 0.0, const double& = 0.0);
		virtual ~Vector();

		Vector operator+(const Vector&);
		Vector operator-(const Vector&);
		Vector operator*(const double&); // SCALAR PRODUCT
		Vector operator/(const double&); // DOT PRODUCT
		double operator*(const Vector&); // DOT PRODUCT
		Vector operator^(const Vector&); // CROSS PRODUCT
		double Abs();
		Vector Unit();

		double GetDx() const;
		double GetDy() const;
		double GetDz() const;

		void Reassign(Vertex*, Vertex*);
		void Reassign(const double&, const double&, const double& = 0.0);

		void Print() const;

	private:
		double m_dx, m_dy, m_dz;
	};
}