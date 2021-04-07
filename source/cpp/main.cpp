#include<iostream>
#include<Mortonhasher.hpp>
#include<Geometry.hpp>
#include<set>
#include<iostream>

class Cell
{
public:
    unsigned int c[3];
    hash_int hash_val;
    bool operator < (const Cell& c) const
    {
        return this->hash_val < c.hash_val;
    }
};

int main()
{

    HasherParams params;
    Hasher hash(params);
    //hash_int in = 786;
    //auto bin = hash.DecimalToBinary(in);
    //auto dec = hash.BinaryToDecimal(bin);

    hash.SetLevel(0);
    /*
    hash.SetCoord(4,2,0);
    auto ans = hash.Get();
    std::cout << ans << "\n";
    */

    /*
    Geometry geometry;
    geometry.Read("C:/Users/MegaMind/Downloads/model/bugatti.stl");
    geometry.CalculateBoundingBox();
    geometry.Write("C:/Users/MegaMind/Downloads/model", "bugatti");
    auto faces = geometry.CoolectInvalidFaces();
    */
    std::set<Cell> clist;
    for (size_t i = 0; i < 16; i++)
    {
        for (size_t j = 0; j < 16; j++)
        {
            for (size_t k = 0; k < 16; k++)
            {
                Cell cell;

                cell.c[0] = i;
                cell.c[1] = j;
                cell.c[2] = k;

                hash.SetCoord(i*32, j*32, k*32);
                cell.hash_val = hash.Get();

                clist.emplace(cell);
            }
        }
    }

    std::ofstream myfile;
    myfile.open("test.dat");
    myfile << "TITLE = \"Example: Simple 3D Line\"" << std::endl;
    myfile << "VARIABLES = \"X\", \"Y\", \"Z\", \"T\"" << std::endl;
    myfile << "ZONE I = " << clist.size() << ", J = 1, K = 1, DATAPACKING = POINT" << std::endl;

    int num = 0;
    for (auto it = clist.begin(); it != clist.end(); ++it)
    {
        myfile << (*it).c[0] << " " << (*it).c[1] << " " << (*it).c[2] << " " << ++num << "\n";
    }

    return 0;
}