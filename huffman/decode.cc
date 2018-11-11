#include <fstream>

#include "bitio.hh"
#include "huffman.hh"

int main(int argc, char *argv[]){
    for ( int i = 0; i< argc ; i++){
        std::ifstream infile {argv[i]};
        std::string infile_name = argv[i];
        assert(infile);
        std::string outfile_name = infile_name + ".plaintext";
        std::ofstream outfile{outfile_name};
        assert(outfile);
        Huffman huffman;
        BitIO bitio(std::ofstream ofs_);
        while (true){
            int symbol = -1;
            while (symbol == -1){
                bool bit = bitio.input_bit();
                symbol = huffman.decode(bit);
            
            }
            outfile << symbol;
            if (symbol == Huffman::HEOF){
                break;
            }
    }
    infile.close();
    outfile.close();
    }
return 0;
}
