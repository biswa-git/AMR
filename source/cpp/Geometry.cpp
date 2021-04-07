#include<Geometry.hpp>
#include<Stl.hpp>
#include<iostream>



Geometry::Geometry() :m_is_read(false), m_is_bounding_box(false)
{
    m_bounding_box.resize(6);
}

Geometry::~Geometry()
{
    /*
    if (!m_face_list.empty())
    {
        for (auto it = m_face_list.begin(); it != m_face_list.end(); ++it)
        {
            FREE_OBJ_MACRO(*it);
        }
    }
    if (!m_vertex_list.empty())
    {
        for (auto it = m_vertex_list.begin(); it != m_vertex_list.end(); ++it)
        {
            FREE_OBJ_MACRO(*it);
        }
    }
    */
}

GeometryResult Geometry::Read(const std::string& file_name)
{
    GeometryResult result;
    // reading the mesh
    if (!m_is_read)
    {
        try {
            stl_reader::StlMesh <float, unsigned int> mesh(file_name.c_str());

            m_coord_list.reserve(mesh.num_vrts());
            m_tri_list.reserve(mesh.num_tris());

            size_t vertNum = 0;
            for (size_t i = 0; i < mesh.num_vrts(); i++)
            {
                auto c = mesh.vrt_coords(i);
                Triplet<float> coord(c[0], c[1], c[2]);
                m_coord_list.emplace_back(coord);

                ++vertNum;
                m_vertex_list.emplace_back(geometry::Vertex::New(c[0], c[1], c[2], vertNum));
            }

            size_t faceNum = 0;
            for (size_t i = 0; i < mesh.num_tris(); i++)
            {
                auto t = mesh.tri_corner_inds(i);
                Triplet<unsigned int> tri(t[0], t[1], t[2]);
                m_tri_list.emplace_back(tri);
                ++faceNum;
                auto new_face = geometry::TriFace::New(m_vertex_list[t[0]], m_vertex_list[t[1]], m_vertex_list[t[2]], faceNum);
                m_face_list.push_back(new_face);
            }
            result.success = true;
        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        m_is_read = true;
    }
    else
    {
        result.error = GEOMETRY_ALREADY_READ;
    }
    return result;
}

GeometryResult Geometry::CalculateBoundingBox()
{
    GeometryResult result;

    if (!m_is_bounding_box)
    {
        //initializing the bounding box
        m_bounding_box[0] = m_coord_list[0].x;
        m_bounding_box[1] = m_coord_list[0].y;
        m_bounding_box[2] = m_coord_list[0].z;
        m_bounding_box[3] = m_coord_list[0].x;
        m_bounding_box[4] = m_coord_list[0].y;
        m_bounding_box[5] = m_coord_list[0].z;

        for (auto it = m_coord_list.begin(); it != m_coord_list.end(); it++)
        {
            if ((*it).x < m_bounding_box[0])
            {
                m_bounding_box[0] = (*it).x;
            }
            if ((*it).y < m_bounding_box[1])
            {
                m_bounding_box[1] = (*it).y;
            }
            if ((*it).z < m_bounding_box[2])
            {
                m_bounding_box[2] = (*it).z;
            }
            if ((*it).x > m_bounding_box[3])
            {
                m_bounding_box[3] = (*it).x;
            }
            if ((*it).y > m_bounding_box[4])
            {
                m_bounding_box[4] = (*it).y;
            }
            if ((*it).z > m_bounding_box[5])
            {
                m_bounding_box[5] = (*it).z;
            }
        }
        m_is_bounding_box = true;
        result.success = true;
    }
    else
    {
        result.error = GEOMETRY_BOUNDING_BOX_PRESENT;
    }

    return result;
}

GeometryResult Geometry::Write(const std::string& file_location, const std::string& file_name)
{
    GeometryResult result;

    std::ofstream myfile;
    auto file = file_location + "/" + file_name + ".dat";
    myfile.open(file);
    myfile << "TITLE = \"title\"\n";
    myfile << "VARIABLES = \"X\", \"Y\", \"Z\"\n";
    myfile << "ZONE T = \"Rampant\", N = " << m_coord_list.size() << ", E = " << m_tri_list.size() << ", DATAPACKING=POINT, ZONETYPE=FETRIANGLE\n";

    for (auto it = m_vertex_list.begin(); it != m_vertex_list.end(); it++)
    {
        myfile << (*it)->GetXCoord() << " " << (*it)->GetYCoord() << " " << (*it)->GetZCoord() << "\n";
    }

    for (auto it = m_face_list.begin(); it != m_face_list.end(); it++)
    {
        myfile << (*it)->GetHalfEdge()[0]->GetEnd()->GetId() << " " << (*it)->GetHalfEdge()[1]->GetEnd()->GetId() << " " << (*it)->GetHalfEdge()[2]->GetEnd()->GetId() << "\n";
    }
    
    myfile.close();

    result.success = true;
    return result;
}
