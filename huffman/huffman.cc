#include <climits>
#include <vector>

#include "htree.hh"
#include "hforest.hh"
#include "huffman.hh"

  using bits_t = std::vector<bool>;

  Huffman::Huffman(){
    freqs = freqs;
    for ( int i=0; i<257; i++){
      freqs.vector::push_back(0);
    }
    forest = Huffman::forest;
    huff_tree = Huffman::huff_tree;
    decode_node = Huffman::decode_node;

  }

  void Huffman::build_forest(){
    for (int i=0; i<257; i++){
      forest.add_tree(HTree::tree_ptr_t(new HTree(i, freqs.vector::at(i))));
    }
  }
  void Huffman::build_huff_tree(){
    while (forest.HForest::size() > 1){
      HTree::tree_ptr_t t1 = forest.HForest::pop_top();
      HTree::tree_ptr_t t2 = forest.HForest::pop_top();
      HForest::tree_t t3 = HForest::tree_t(new HTree::HTree(-1, (t1->get_value()+t2->get_value())));
      forest.HForest::add_tree(t3);
      huff_tree = t3;
    }
  }

  bits_t Huffman::path_to_bools(HTree::path_t path){
    bits_t path_bits;
    for ( HTree::Direction x : path){
      if (x == HTree::Direction::LEFT){
        path_bits.push_back(false);
      }
      else{
        path_bits.push_back(true);
      }
    }
    return path_bits;
  }





  // Encode a symbol into a sequence of bits, then update frequency table.
  bits_t Huffman::encode(int symbol){
    build_forest();
    build_huff_tree();
    HTree::path_t path = huff_tree->path_to(symbol);
    bits_t path_bits = path_to_bools(path);
    freqs.vector::at(symbol) += 1;
    return path_bits;
  }

  // Decode a single bit into a symbol. If no symbol can be unmabiguously decoded
  // without additional bits, returns a negative value.
  // Subsequent calls with more bits should eventually resolve to either
  // a character symbol or HEOF.
  // Finally, updates the frequency table with this additional symbol.
  int Huffman::decode(bool bit){
    HForest::tree_t next_t;
    if (!decode_node){
      build_forest();
      build_huff_tree();
      decode_node = huff_tree;
    }
      if (bit == false){
        next_t = decode_node->get_child(HTree::Direction::LEFT);
      }
      else if (bit == true){
        next_t = decode_node->get_child(HTree::Direction::RIGHT);
      }
      if (next_t->get_key() == -1){
        decode_node = next_t;
        return -1;
      }
      else{
        freqs.vector::at(next_t->get_key()) += 1;
        build_forest();
        build_huff_tree();
        decode_node = huff_tree;
        return next_t->get_key();
      }
    }









