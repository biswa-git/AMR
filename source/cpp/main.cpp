#include<iostream>
#include<Mortonhasher.hpp>

int main()
{
    HasherParams params;
    Hasher hash(params);
    //hash_int in = 786;
    //auto bin = hash.DecimalToBinary(in);
    //auto dec = hash.BinaryToDecimal(bin);
    
    hash.SetLevel(3);
    hash.SetCoord(4,2,0);
    auto ans = hash.Get();
    std::cout << ans << "\n";

    return 0;
}