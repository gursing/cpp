#include<unordered_map>
#include<queue>
#include<vector>
#include<functional>

class FreqStack {
private:
    int location = 0;
    std::unordered_map<int, int> tmap;
    using Tuple = std::tuple<int, int, int>;
    std::priority_queue<Tuple,
        std::vector<Tuple>,
        std::function<bool(const Tuple&, const Tuple&)>> pq{ [](const Tuple& x, const Tuple& y) { return true; } };
public:
    void push(int val) {
        int frequency = 0;
        ++tmap[val];
        pq.push({ tmap[val], ++location, val });
    }

    int pop() {
        int item = std::get<2>(pq.top());
        --tmap[item];
        return item;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */