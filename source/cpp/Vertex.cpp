#include<Vertex.hpp>

size_t geometry::Vertex::m_count = 0;

geometry::Vertex::Vertex(const double& x, const double& y, const double& z, const size_t& id) :m_id(id), m_x_coord(x), m_y_coord(y), m_z_coord(z), m_previous(nullptr), m_distance(SIZE_MAX)
{
}

geometry::Vertex* geometry::Vertex::New(const double& x, const double& y, const double& z, const size_t& id)
{
	return new Vertex(x,y,z,id);
}

geometry::Vertex::~Vertex()
{
}

void geometry::Vertex::Reassign(const double& x, const double& y, const double& z)
{
	m_x_coord = x;
	m_y_coord = y;
	m_z_coord = z;
}

size_t geometry::Vertex::GetId() const
{
	return m_id;
}

double geometry::Vertex::GetXCoord() const
{
	return m_x_coord;
}

double geometry::Vertex::GetYCoord() const
{
	return m_y_coord;
}

double geometry::Vertex::GetZCoord() const
{
	return m_z_coord;
}

std::set<geometry::Edge*>& geometry::Vertex::GetAssociatedEdge()
{
	return m_associated_edge;
}

void geometry::Vertex::Print() const
{
	std::cout << "id:" << m_id << " [" << m_x_coord << "," << m_y_coord << "," << m_z_coord << "]" << std::endl;
}

void geometry::Vertex::SetPrevious(geometry::Vertex* P)
{
	m_previous = P;
}

geometry::Vertex* geometry::Vertex::GetPrevious()
{
    return m_previous;
}

void geometry::Vertex::SetDistance(const size_t& d)
{
	m_distance = d;
}

size_t geometry::Vertex::GetDistance()
{
    return m_distance;
}
