#pragma once
#include <iostream>
#include <queue>
#include <string>
#include <vector>

class CompareQuery {
public:
    bool operator()(std::pair<int, int> a, std::pair<int, int> b)
    {
        return a.second > b.second;
    }
};

struct Query {
    int id;
    std::string query;
    int numberOfRelevants;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, CompareQuery> docsByRelevance;

    void addRelevant(int rn, int value)
    {
        int result = 0;
        while(value > 0) {
            result += value%10;
            value /= 10;
        }
        
        docsByRelevance.push(std::make_pair(rn, result));
    }

    Query()
    {
        id = -1;
    }
};
