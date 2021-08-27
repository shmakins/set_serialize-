#include <iostream>
#include <cassert>
template<typename T>
T read(std::istream& is);

template<>
std::uint32_t read<uint32_t> (std::istream& is) {
  std::uint32_t size;
  is.read(reinterpret_cast<char *>(&size), sizeof(size));
  return size;
}

template<>
std::string read<std::string>(std::istream& is ) {
  std::uint32_t size = read<std::uint32_t>(is);
  std::string data(" ", size);
  is.read(data.data(), size);
  return std::move(data);
}

template<typename T>
void write(const T& x, std::ostream& os);

template<>
void write<std::uint32_t> (const std::uint32_t& x, std::ostream& os) {
  os.write(reinterpret_cast<const char*>(&x), sizeof(x));
}
template<>
void write<std::string> (const std::string& x, std::ostream& os) {
  write<uint32_t>(x.size(), os);
  os.write(x.data(), x.size());
}

#include "set_serial.h"
int main() {
  {
    std::set<std::uint32_t> inSet;
    inSet.insert(2);
    inSet.insert(1);
    inSet.insert(5);

    set_serial::writeToFile(inSet, "intSet");
    std::set<std::uint32_t> outSet
      = set_serial::readFromFile<uint32_t>("intSet");
    assert(inSet == outSet && "Int set is invallid");
  }
  {
    std::set<std::string> inSet;
    inSet.insert("dog");
    inSet.insert("cat");
    inSet.insert("hippo");

    set_serial::writeToFile(inSet, "stringSet");
    std::set<std::string> outSet
        = set_serial::readFromFile<std::string>("stringSet");
    assert(inSet == outSet && "String set in not equal");
  }

  return 0;
}
