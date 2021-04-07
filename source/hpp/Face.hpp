#pragma once
#include<Edge.hpp>
#include<vector>

namespace geometry
{
	class HalfEdge;
	class Face
	{
	public:
		Face();
		virtual ~Face();
		Face(Face const&) = delete;
		Face& operator=(Face const&) = delete;
		virtual double GetArea() = 0;
		virtual Vector GetNormalVector() = 0;
		virtual void SetOrphanedEdgeRemoveFlag(bool);
		virtual std::vector<HalfEdge*>& GetHalfEdge() = 0;
		void SetDistance(const size_t&);
		size_t GetDistance();
	protected:
		virtual void CalculateArea() = 0;
		static size_t m_count;
		double m_area;
		bool m_is_orphaned_edge_remove_flag;
		std::vector<HalfEdge*> m_half_edge;
		size_t m_distance;
		size_t m_id;
	};

	class TriFace :public Face
	{
	public:
		static TriFace* New(Vertex*, Vertex*, Vertex*, const size_t&);
		~TriFace();
		virtual double GetArea();
		virtual Vector GetNormalVector();
		virtual std::vector<HalfEdge*>& GetHalfEdge();
	protected:
		virtual void CalculateArea();
	private:
		TriFace(Vertex*, Vertex*, Vertex*,const size_t&);
	};
}
