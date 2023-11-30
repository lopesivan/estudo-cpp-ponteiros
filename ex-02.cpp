#include <iostream>

struct Content {
private:
  std::string info;

public:
  Content(std::string info) : info(info) {}
  void getInfo() { std::cout << info << '\n'; }
};

int main() {
  /* MEMÓRIA BRUTA */
  Content *c = new Content("Olá mundo!");
  c->getInfo();
  delete c;
  return 0;
}
