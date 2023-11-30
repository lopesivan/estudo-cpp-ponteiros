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
  std::shared_ptr<Content> c = std::make_shared<Content>("Olá mundo!");
  c->getInfo();
  return 0;
}
