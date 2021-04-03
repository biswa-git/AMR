#include<iostream>
#include<Mortonhasher.hpp>
#include<Geometry.hpp>

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
    */

    Geometry geom;
    geom.Read("C:/Users/MegaMind/Downloads/model/tractor.stl");
    geom.CalculateBoundingBox();
    geom.Write("C:/Users/MegaMind/Downloads/model", "tractor");

    return 0;
}