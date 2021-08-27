//
// Created by Denys Fisher on 26/08/2021.
//

#pragma once
#include <fstream>
#include <set>
#include <string>

namespace set_serial {
  template<typename T>
  std::set<T> readFromFile(std::string file){
    std::ifstream in(file, std::ios::binary);
    std::uint32_t size;
    in.read(reinterpret_cast<char *>(&size), sizeof(size));
    std::set<T> res;
    for (std::uint32_t i = 0; i < size; ++i) {
      T x = read<T>(in);
      res.insert(x);
    }
    return res;
  }
  template <typename T>
  void writeToFile(const std::set<T>& data, std::string file) {
    std::ofstream out(file, std::ios_base::binary);
    std::uint32_t size = data.size();
    out.write(
        reinterpret_cast<const char*>(&size), sizeof(size)
    );
    for (const T& i: data) {
      write<T>(i, out);
    }
    out.close();
  }
};


