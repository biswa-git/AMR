#include<iostream>
#include<Mortonhasher.hpp>
#include<Stl.hpp>
#include<set>

int main()
{
    /*
    HasherParams params;
    Hasher hash(params);
    //hash_int in = 786;
    //auto bin = hash.DecimalToBinary(in);
    //auto dec = hash.BinaryToDecimal(bin);
    
    hash.SetLevel(3);
    hash.SetCoord(4,2,0);
    auto ans = hash.Get();
    std::cout << ans << "\n";

    try {
        stl_reader::StlMesh <float, unsigned int> mesh("C:/Users/MegaMind/Downloads/model/tractor.stl");

        for (size_t itri = 0; itri < mesh.num_tris(); ++itri) {
            std::cout << "coordinates of triangle " << itri << ": ";
            for (size_t icorner = 0; icorner < 3; ++icorner) {
                //float* c = mesh.vrt_coords(mesh.tri_corner_ind(itri, icorner));
                const float* c = mesh.tri_corner_coords(itri, icorner);
                // or alternatively:
                // float* c = mesh.vrt_coords (mesh.tri_corner_ind (itri, icorner));
                std::cout << "(" << c[0] << ", " << c[1] << ", " << c[2] << ") ";
            }
            std::cout << std::endl;

            auto n = mesh.tri_normal(itri);
            std::cout << "normal of triangle " << itri << ": "
                << "(" << n[0] << ", " << n[1] << ", " << n[2] << ")\n";
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    */

    std::set<stl_reader::Coord<double>> crd;

    stl_reader::Coord<double > c,d;

    crd.emplace(c);
    c.x = 8;
    crd.emplace(c);
    crd.emplace(c);
    crd.emplace(d);
    std::sort(crd.begin(), crd.end());

    return 0;
}