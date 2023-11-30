#include <iostream>

struct Content {
private:
  std::string info;

public:
  Content(std::string info) : info(info) {}
  void getInfo() { std::cout << info << '\n'; }
};

int main() {
  // STACK
  Content c("Olá mundo!");
  c.getInfo();
  return 0;
}
