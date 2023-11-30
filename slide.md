---
title: Smart Pointers C++
author: Ivan Lopes (lopesivan.ufrj@gmail.com)
date: 2023-11-28
---

# O início

```cpp
#include <iostream>

int main() {

    return 0; // success return
}
```

---

# ex-01.cpp

```cpp
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
```

---

# ex-02.cpp

```cpp
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
```

---

# ex-03.cpp

```cpp
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
```

---

# ex-04.cpp

```cpp
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
```

---

# ex-05.cpp

```cpp
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
  std::shared_ptr<Content> c;
  c = std::make_shared<Content>("Olá mundo!");
  c->getInfo();
  return 0;
}
```

---

# ex-06.cpp

```cpp
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
  auto c = std::make_shared<Content>("Olá mundo!");
  c->getInfo();
  return 0;
}
```

---

# Contato

**lopesivan.ufrj**@gmail.com

/_ -_- vim: set ts=4 sw=4 tw=64 ft=markdown: -_- _/
