#include "docollection.hpp"
#include "evaluation.hpp"
#include "parser.hpp"
#include <cstdio>
#include <cstring>
#include <iomanip> // std::setprecision
#include <queue>
using namespace std;

int main(int argc, char* argv[])
{
    Parser parser;
    Docollection collection;
    std::queue<string> documentQueue;

    for (int i = 1; i < argc; i++) {
        documentQueue.push(argv[i]);
    }

    documentQueue.push("cfc/cf74");
    documentQueue.push("cfc/cf75");
    documentQueue.push("cfc/cf76");
    documentQueue.push("cfc/cf77");
    documentQueue.push("cfc/cf78");
    documentQueue.push("cfc/cf79");

    while (!documentQueue.empty()) {

        parser.setFile(documentQueue.front());
        documentQueue.pop();

        Document* document = parser.parseNext();

        while (document) {
            if (document->id == -1) {
                break;
            }
            document->calculateTF();
            collection += document;
            document = parser.parseNext();
        }
    }

    collection.calculateIDF();
    collection.calculateTFIDF();

    // for (auto& idfMap : collection.idfMap) {
    //     std::cout << idfMap.first << " -> " << idfMap.second << '\n';
    // }

    // for (auto& document : collection.tfidfMap) {
    //     auto& wordSet = document.second;
    //     std::cout << "--- Document # " << document.first << '\n';
    //     for (auto& wordAndTFIDF : wordSet) {
    //         std::cout << wordAndTFIDF.first << " -> " << wordAndTFIDF.second << '\n';
    //     }
    // }

    // for (auto& document : collection.documentsById) {
    //     std::cout << "--- Document # " << document.first << '\n';
    //     for (auto& wordTf : document.second->tfMap) {
    //         std::cout << wordTf.first << " -> " << wordTf.second << '\n';
    //     }
    // }

    parser.setFile("cfc/cfquery");
    Query q = parser.nextQuery();

    double prAverage = 0, mapAverage = 0;
    int prCount = 0, mapCount = 0;

    while (q.id != -1) {
        std::cout << " --- Query # " << q.id << " - \"" << q.query << "\"\n";
        std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>, std::allocator<std::pair<int, double>>>, QueryComparator_t> queryResponse = collection.performQuery(q);

        // auto value = precisionR(q, queryResponse, 10, 10);
        auto value = pArroba(q, queryResponse, 10);
        auto mapValue = mapEvalutation(q, queryResponse);
        prAverage += value;
        prCount++;

        mapAverage += mapValue;
        mapCount++;
        // while (!queryResponse.empty()) {
        //     auto& response = queryResponse.top();
        //     // std::cout << " Doc # " << response.first << " = " << std::fixed << std::setprecision(20) << response.second << '\n';
        //     // printf(" ------ Doc # %d = %f\n", response.first, response.second);
        //     queryResponse.pop();
        // }

        cout << "P@: " << std::fixed << std::setprecision(10) << value << endl;
        cout << "Map Evaluation: " << std::fixed << std::setprecision(10) << mapValue << endl;

        std::cout << '\n';

        q = parser.nextQuery();
    }

    cout << "P@ Average: " << std::fixed << std::setprecision(10) << (prAverage / (double)prCount) << endl;
    cout << "Map Evaluation Average: " << std::fixed << std::setprecision(10) << (mapAverage / (double)mapCount) << endl;
}
