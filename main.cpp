#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>

using std::vector;
using std::set;
using std::cout;
using std::endl;
using std::pair;
using std::tuple;

vector<int> arr = {0, 0, 1, -1};

auto collect_set(const vector<int> &vec, bool pos) {
    set<int> ret;
    for (const auto &v: vec) {
        if (pos && v > 0) {
            ret.insert(v);
        } else if (!pos && v < 0) {
            ret.insert(v);
        }
    }
    return ret;
}

bool operator+(const std::pair<int, int> &intPair, int nextVal) {
    return std::get<0>(intPair) + std::get<1>(intPair) + nextVal == 0;
}

bool has_zero(const vector<int> &vec) {
    return std::any_of(vec.begin(), vec.end(), [](int i) { return i == 0; });
}

vector<pair<int, int>> get_all_pairs(const set<int> &collection) {
    vector<pair<int, int>> retVec;
    const auto &itr_beg = collection.begin();
    const auto &itr_end = collection.end();
    auto itr = itr_beg;
    std::for_each(itr_beg, itr_end, [&retVec, &itr_beg, &itr_end, &itr](int i) {

        auto tmp_itr = itr;
        for (++itr; itr != itr_end; ++itr) {
            retVec.emplace_back(i, *(itr));
        }
        itr = ++tmp_itr;
        // for_each

    });
    return retVec;
}

int main(int, char **) {
    bool is_zero_contains = has_zero(arr);
    set<int> pos_set(collect_set(arr, true));
    set<int> neg_set(collect_set(arr, false));

    set<tuple<int, int, int>> result;
    if (pos_set.size() < 2 || neg_set.size() < 2) {
        auto posVal = *(pos_set.cbegin());
        auto negVal = *(neg_set.cbegin());
        if (is_zero_contains && (posVal == -negVal)) {
            result.emplace(0, posVal, negVal);
        }
    }


    auto pos_pairs = get_all_pairs(pos_set);
    auto neg_pairs = get_all_pairs(neg_set);

    for (const auto &posv: pos_pairs) {
        // cout << posv.first <<" "<<posv.second <<endl;
    }
    for (const auto &posv: neg_pairs) {
        //cout << posv.first <<" "<<posv.second<< endl;
    }


    std::for_each(pos_pairs.begin(), pos_pairs.end(),
                  [&result, &neg_set, &is_zero_contains](const std::pair<int, int> &p) {
                      for (const auto &ne: neg_set) {
                          if (is_zero_contains) {
                              if (p.first == -ne) result.emplace(0, p.first, ne);
                              else if (p.second == -ne) result.emplace(0, p.second, ne);
                          }
                          if (p + ne) {
                              result.emplace(p.first, p.second, ne);
                          }
                      }
                  });
    std::for_each(neg_pairs.begin(), neg_pairs.end(),
                  [&result, &pos_set, &is_zero_contains](const std::pair<int, int> &p) {
                      for (const auto &e: pos_set) {
                          if (is_zero_contains) {
                              if (-p.first == e) result.emplace(0, e, p.first);
                              else if (-p.second == e) result.emplace(0, e, p.second);
                          }
                          if (p + e) {
                              result.emplace(e, p.first, p.second);
                          }
                      }
                  });
    for (const auto &e: result) {
        cout << get<0>(e) << "," << get<1>(e) << "," << get<2>(e) << endl;
    }
    cout << std::boolalpha << std::pair<int, int>(1, 3) + -1 << endl;
}