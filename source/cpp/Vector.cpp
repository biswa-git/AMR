#include<Vector.hpp>

geometry::Vector::Vector(const double& m_dx, const double& m_dy, const double& m_dz) :m_dx(m_dx), m_dy(m_dy), m_dz(m_dz)
{
}

geometry::Vector* geometry::Vector::New(const double& m_dx, const double& m_dy, const double& m_dz)
{
	return new geometry::Vector(m_dx,m_dy,m_dz);
}

geometry::Vector::~Vector()
{
}

geometry::Vector geometry::Vector::operator+(const Vector& v)
{
	return Vector(this->m_dx + v.m_dx, this->m_dy + v.m_dy, this->m_dz + v.m_dz);
}

geometry::Vector geometry::Vector::operator-(const Vector& v)
{
	return Vector(this->m_dx - v.m_dx, this->m_dy - v.m_dy, this->m_dz - v.m_dz);
}

geometry::Vector geometry::Vector::operator*(const double& s)
{
	return Vector(this->m_dx * s, this->m_dy * s, this->m_dz * s);
}

geometry::Vector geometry::Vector::operator/(const double& s)
{
	return Vector(this->m_dx / s, this->m_dy / s, this->m_dz / s);
}

double geometry::Vector::operator*(const Vector& v)
{
	return (this->m_dx * v.m_dx + this->m_dy * v.m_dy + this->m_dz * v.m_dz);
}

//3d implementation needed
geometry::Vector geometry::Vector::operator^(const Vector& v)
{
	return Vector(
		this->m_dy * v.m_dz - this->m_dz * v.m_dy,
		this->m_dz * v.m_dx - this->m_dx * v.m_dz,
		this->m_dx * v.m_dy - this->m_dy * v.m_dx);
}

double geometry::Vector::Abs()
{
	return sqrt(m_dx * m_dx + m_dy * m_dy + m_dz * m_dz);
}

geometry::Vector geometry::Vector::Unit()
{
	return (*this / this->Abs());
}

double geometry::Vector::GetDx() const
{
	return m_dx;
}

double geometry::Vector::GetDy() const
{
	return m_dy;
}

double geometry::Vector::GetDz() const
{
	return m_dz;
}

void geometry::Vector::Reassign(Vertex* vStart, Vertex* vEnd)
{
	m_dx = vEnd->GetXCoord() - vStart->GetXCoord();
	m_dy = vEnd->GetYCoord() - vStart->GetYCoord();
	m_dz = vEnd->GetZCoord() - vStart->GetZCoord();

}

void geometry::Vector::Reassign(const double& m_dx, const double& m_dy, const double& m_dz)
{
	this->m_dx = m_dx;
	this->m_dy = m_dy;
	this->m_dz = m_dz;
}

void geometry::Vector::Print() const
{
	std::cout << "[" << m_dx << "," << m_dy << "," << m_dz << "]" << std::endl;
}
