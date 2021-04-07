#include<Face.hpp>

size_t geometry::Face::m_count = 0;

geometry::Face::Face() :m_area(0.0), m_is_orphaned_edge_remove_flag{ true }, m_distance(SIZE_MAX), m_id(0) //NOT SURE ABOUT GCC INF
{
}

geometry::Face::~Face()
{
}

void geometry::Face::SetOrphanedEdgeRemoveFlag(bool status)
{
	m_is_orphaned_edge_remove_flag = status;
}

void geometry::Face::SetDistance(const size_t& d)
{
	m_distance = d;
}

size_t geometry::Face::GetDistance()
{
	return m_distance;
}

geometry::TriFace* geometry::TriFace::New(Vertex* a, Vertex* b, Vertex* c, const size_t& id)
{
	return new TriFace(a, b, c, id);
}

geometry::TriFace::~TriFace()
{
	for (size_t i = 0; i < 3; i++)
	{	
		auto parentEdge = m_half_edge[i]->GetParentEdge();
		m_half_edge[i]->SetNext(nullptr);
		m_half_edge[i]->SetFace(nullptr);
		if (m_is_orphaned_edge_remove_flag && parentEdge->GetHalfEdge(0)->GetFace() == nullptr && parentEdge->GetHalfEdge(1)->GetFace() == nullptr)
		{	
			//DELETE THE EDGE IF IT IS ORPHANED. i.e. NO ASSOCIATED WITH ANY FACE/FACES.
			delete parentEdge;
		}
	}
}

double geometry::TriFace::GetArea()
{
	return m_area;
}

geometry::Vector geometry::TriFace::GetNormalVector()
{
	auto half_edge = this->GetHalfEdge();
	auto normal = (half_edge[0]->GetEdgeVector() ^ half_edge[1]->GetEdgeVector()).Unit();
}

geometry::TriFace::TriFace(Vertex* a, Vertex* b, Vertex* c, const size_t& id = 0)
{
	m_id = id;
	m_half_edge.resize(3, nullptr);
	//IF IT IS COLINEAR THEN IT IS NOT A VALID SURFACE. WE NEED TO STOP THAT.
	auto lhs = (a->GetYCoord() - b->GetYCoord()) / (a->GetXCoord() - b->GetXCoord());
	auto rhs = (a->GetYCoord() - c->GetYCoord()) / (a->GetXCoord() - c->GetXCoord());
	if (fabs(lhs - rhs) < std::numeric_limits<double>::epsilon())
	{
		std::cout << "Warning:The points of the triangle wiht id="<< m_id <<"are colinear!" << std::endl;
	}

	//	FIRST WE CREATE THREE EDGE / CHECK EXISTANCE

	Vertex* tempVertexArray[3]{ a,b,c };
	Edge* triEdge[3]{ nullptr,nullptr,nullptr };

	//CHECKING WHETHER EDGE EXIST BETWEEN Vertex
	for (size_t i = 0; i < 3; i++)
	{
		auto edgeList = tempVertexArray[i]->GetAssociatedEdge();
		for (auto it = edgeList.begin(); it != edgeList.end(); it++)
		{
			auto associatedEdge = *it;
			if (associatedEdge->GetEnd() == tempVertexArray[(i + 1) % 3] || associatedEdge->GetStart() == tempVertexArray[(i + 1) % 3])
			{
				triEdge[i] = associatedEdge;
				break;
			}
		}
		if (triEdge[i] == nullptr) triEdge[i] = Edge::New(tempVertexArray[i], tempVertexArray[(i + 1) % 3]);
	}

	for (size_t i = 0; i < 3; i++)
	{
		Vector directionVec(Edge::DistanceVector(triEdge[i]->GetHalfEdge(0)->GetEnd(), tempVertexArray[(i+2)%3]));

		if ((triEdge[i]->GetHalfEdge(0)->GetEdgeVector() ^ directionVec).Abs() > 0.0)
		{
			m_half_edge[i] = triEdge[i]->GetHalfEdge(0);
		}
		else
		{
			m_half_edge[i] = triEdge[i]->GetHalfEdge(1);
		}
		m_half_edge[i]->SetFace(this);
	}

	if (m_half_edge[0]->GetEnd() == m_half_edge[1]->GetStart())
	{
		m_half_edge[0]->SetNext(m_half_edge[1]);
		m_half_edge[1]->SetNext(m_half_edge[2]);
		m_half_edge[2]->SetNext(m_half_edge[0]);
	}
	else
	{
		m_half_edge[0]->SetNext(m_half_edge[2]);
		m_half_edge[2]->SetNext(m_half_edge[1]);
		m_half_edge[1]->SetNext(m_half_edge[0]);
	}
	//AREA BEING A BASIC PROPERTY OF FACE, BEING CALCULATED IMMIDIATELY
	CalculateArea();
}

void geometry::TriFace::CalculateArea()
{
	Vector firstEdgeVector(Edge::DistanceVector(m_half_edge[0]->GetStart(), m_half_edge[0]->GetEnd()));
	Vector secondEdgeVector(Edge::DistanceVector(m_half_edge[1]->GetStart(), m_half_edge[1]->GetEnd()));
	m_area = 0.5*(firstEdgeVector ^ secondEdgeVector).Abs();
}

std::vector<geometry::HalfEdge*>& geometry::TriFace::GetHalfEdge()
{
	return m_half_edge;
}

