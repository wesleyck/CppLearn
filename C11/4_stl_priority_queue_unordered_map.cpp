#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>

// 1.priority_queue
template<typename T> void print_queue(T& q) {
  while (!q.empty()) {
    std::cout << q.top() << " ";
    q.pop();
  }
  std::cout << std::endl;
}

int main1() {
  std::priority_queue<int> q;

  for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2}) {
    q.push(n);
  }
  print_queue(q);

  std::priority_queue<int, std::vector<int>, std::greater<int>> q2;
  
  for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2}) {
    q.push(n);
  }
  print_queue(q);

  auto cmp = [](int left, int right) {return left > right;}; // 从小到大
  std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
  for(int n : {1,8,5,6,3,4,0,9,7,2})
        q3.push(n);
  print_queue(q3);

  return 0;
}


// 2. unordered_map map
void unordered_map_test() {
  std::cout << "unordered_map_test" << std::endl;
  std::unordered_map<std::string, std::string> umap = {
    {"2RED", "#FF0000"},
    {"1GREEN", "#00FF00"},
    {"3BLUE", "#0000FF"},
    {"a", "#0000FF"},
    {"b", "#0000FF"}
  };

  for (const auto& n : umap) {
    std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
  }

  umap["BLACK"] = "#000000";
  umap["WHITE"] = "#FFFFFF";
  std::cout << "The Hex of color Red is [" << umap["RED"] << "]" << std::endl;
  std::cout << "The Hex of color BLACK is [" << umap["BLACK"] << "]" << std::endl;
}

void ordered_map_test() {
  std::cout << "ordered_map_test" << std::endl;
  std::map<std::string, std::string> map = {
    {"2RED", "#FF0000"},
    {"1GREEN", "#00FF00"},
    {"3BLUE", "#0000FF"},
    {"a", "#0000FF"},
    {"b", "#0000FF"}
  };

  for (const auto& n : map) {
    std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
  }

  map["BLACK"] = "#000000";
  map["WHITE"] = "#FFFFFF";
  std::cout << "The Hex of color Red is [" << map["RED"] << "]" << std::endl;
  std::cout << "The Hex of color BLACK is [" << map["BLACK"] << "]" << std::endl;
}

int main() {
  unordered_map_test();
  ordered_map_test();
  return 0;
}



