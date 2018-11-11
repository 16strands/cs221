#include <fstream>

#include "huffman.hh"
#include "bitio.hh"

int main(int argc, char *argv[]){
    for ( int i = 0; i< argc ; i++){
        std::ifstream infile {argv[i]};
        std::string infile_name = argv[i];
        assert(infile);
        std::string outfile_name = infile_name + ".comp";
        std::ofstream outfile{outfile_name};
        assert(outfile);
        int symbol;
        Huffman huffman;
        BitIO bitio(std::istream is);
        while (symbol != Huffman::HEOF){
            infile >> symbol;
            Huffman::bits_t bools_list = huffman.Huffman::encode(symbol);
            for (bool bool_t : bools_list){
                bitio.BitIO::output_bit(bool_t);
            }
        Huffman::bits_t EOF_asboollist = huffman.Huffman::encode(Huffman::HEOF);
        for (bool bool_heof : EOF_asboollist){
            bitio.BitIO::output_bit(bool_heof);

        }
    }
    infile.close();
    outfile.close();
    }
return 0;
}


