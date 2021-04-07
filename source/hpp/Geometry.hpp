#pragma once
#include<string>
#include<set>

#include <algorithm>
#include <exception>
#include <fstream>
#include <sstream>
#include <vector>
#include<Face.hpp>

#ifdef STL_READER_NO_EXCEPTIONS
#define STL_READER_THROW(msg) return false;
#define STL_READER_COND_THROW(cond, msg) if(cond) return false;
#else
/// Throws an std::runtime_error with the given message.
#define STL_READER_THROW(msg) {std::stringstream ss; ss << msg; throw(std::runtime_error(ss.str()));}

/// Throws an std::runtime_error with the given message, if the given condition evaluates to true.
#define STL_READER_COND_THROW(cond, msg)  if(cond){std::stringstream ss; ss << msg; throw(std::runtime_error(ss.str()));}
#endif


enum error
{
    GEOMETRY_NO_ERROR = 0,
    GEOMETRY_ALREADY_READ,
    GEOMETRY_BOUNDING_BOX_PRESENT
};

struct GeometryResult
{
	bool success = false;
    int error = GEOMETRY_NO_ERROR;
};

template <typename t_number>
class Triplet
{
public:
    Triplet(const t_number& x, const t_number& y, const t_number& z) :x(x), y(y), z(z)
    {};
    ~Triplet() = default;
public:
    t_number x;
    t_number y;
    t_number z;
};

class Geometry
{
public:
	Geometry();
	~Geometry();
    GeometryResult Read(const std::string& file_name);
    GeometryResult CalculateBoundingBox();
    GeometryResult Write(const std::string& file_location, const std::string& file_name);
    std::vector<geometry::Face*> CoolectInvalidFaces();
private:
    bool m_is_read;
    bool m_is_bounding_box;
    std::vector<Triplet<float>> m_coord_list;
    std::vector<Triplet<unsigned int>> m_tri_list;
    std::vector<float> m_bounding_box;


    std::vector<geometry::Vertex*> m_vertex_list;
    std::vector<geometry::Face*> m_face_list;
};
