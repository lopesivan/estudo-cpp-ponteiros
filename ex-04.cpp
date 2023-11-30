#include <iostream>
#include <memory>

struct Content {
private:
  std::string info;

public:
  Content(std::string info) : info(info) {}
  void getInfo() { std::cout << info << '\n'; }
};

int main() {
  std::unique_ptr<Content> c = std::make_unique<Content>("Olá mundo!");
  c->getInfo();
  return 0;
}
