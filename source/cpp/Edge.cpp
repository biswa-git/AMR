#include<Edge.hpp>
#include<vector>

size_t geometry::Edge::m_count = 0;

geometry::Edge* geometry::Edge::New(Vertex* start, Vertex* end)
{
	geometry::Edge* newEdge = new Edge(start, end);
	start->GetAssociatedEdge().insert(newEdge);
	end->GetAssociatedEdge().insert(newEdge);
	return newEdge;
}

geometry::Edge::~Edge()
{
	m_start->GetAssociatedEdge().erase(this);
	m_end->GetAssociatedEdge().erase(this);
	delete m_half_edge[0];
	delete m_half_edge[1];
}

geometry::Edge::Edge(Vertex* start, Vertex* end) :m_id(m_count++), m_start(start), m_end(end)
{
	m_half_edge[0] = geometry::HalfEdge::New(this, start);
	m_half_edge[1] = geometry::HalfEdge::New(this, end);
}

void geometry::Edge::Flip()
{
	Vertex* temp = m_start;
	m_start = m_end;
	m_end = temp;
}

size_t geometry::Edge::GetId()
{
	return m_id;
}

geometry::Vertex* geometry::Edge::GetStart()
{
	return m_start;
}

geometry::Vertex* geometry::Edge::GetEnd()
{
	return m_end;
}
/*
geometry::vector geometry::Edge::GetVector()
{
	return vector(start,end);
}
*/
geometry::HalfEdge* geometry::Edge::GetHalfEdge(const size_t& index)
{
	return m_half_edge[index];
}

void geometry::Edge::Legalize(Edge* E)
{
}

geometry::Vector geometry::Edge::DistanceVector(Vertex* start, Vertex* end)
{
	auto dx = end->GetXCoord() - start->GetXCoord();
	auto dy = end->GetYCoord() - start->GetYCoord();
	auto dz = end->GetZCoord() - start->GetZCoord();

	return Vector(dx, dy, dz);
}

geometry::HalfEdge* geometry::HalfEdge::New(Edge* e, Vertex* v)
{
	return new HalfEdge(e, v);
}

geometry::Edge* geometry::HalfEdge::GetParentEdge()
{
	return m_parent;
}

geometry::Vertex* geometry::HalfEdge::GetStart()
{
	return m_start;
}

geometry::Vertex* geometry::HalfEdge::GetEnd()
{
	if (m_start == m_parent->GetStart()) return m_parent->GetEnd();
	else return m_parent->GetStart();
}

void geometry::HalfEdge::SetNext(HalfEdge* half_edge)
{
	m_next = half_edge;
}

geometry::HalfEdge* geometry::HalfEdge::GetNext()
{
	return m_next;
}

void geometry::HalfEdge::SetFace(Face* f)
{
	m_associated_Face = f;
}

geometry::Face* geometry::HalfEdge::GetFace()
{
	return m_associated_Face;
}

geometry::Vector geometry::HalfEdge::GetEdgeVector()
{
	auto end = GetEnd();
	return Edge::DistanceVector(m_start, end);
}

geometry::HalfEdge::HalfEdge(Edge* e, Vertex* v) :m_parent(e), m_start(v), m_next(nullptr), m_associated_Face(nullptr)
{
}
