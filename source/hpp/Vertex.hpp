#pragma once
#include<Preprocessor.hpp>
#include<set>

namespace geometry
{
	class Edge;
	class Vertex
	{
	public:
		static Vertex* New(const double& = 0.0, const double& = 0.0, const double& = 0.0, const size_t & = 0);
		virtual ~Vertex();
		Vertex(Vertex const&) = delete;
		Vertex& operator=(Vertex const&) = delete;

		void Reassign(const double& = 0.0, const double& = 0.0, const double& = 0.0);
		size_t GetId() const;
		double GetXCoord() const;
		double GetYCoord() const;
		double GetZCoord() const;
		std::set<Edge*>& GetAssociatedEdge();
		void Print() const;
        void SetPrevious(Vertex*);
        Vertex* GetPrevious();
        void SetDistance(const size_t&);
        size_t GetDistance();
	private:
		Vertex(const double& = 0.0, const double& = 0.0, const double& = 0.0, const size_t & = 0);

		static size_t m_count;
		size_t m_id;
		double m_x_coord, m_y_coord, m_z_coord;
		std::set<Edge*> m_associated_edge;
        Vertex* m_previous;
        size_t m_distance;
	};

}
