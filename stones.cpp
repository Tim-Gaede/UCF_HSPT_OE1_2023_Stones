#include <bits/stdc++.h>

using namespace std;

//will add comments later

int n, m;
priority_queue<int, vector<int>, greater<int>> qA, qB;

string solve(){
    vector<int> resA, resB;
    while(qA.size() > 1){
        int curr = qA.top(); qA.pop();
        int next = qA.top();
        if(curr != next){
            resA.push_back(curr);
            continue;
        }
        qA.pop();
        qA.push(curr+1);
    }
    if(!qA.empty())
        resA.push_back(qA.top());

    while(qB.size() > 1){
        int curr = qB.top(); qB.pop();
        int next = qB.top();
        if(curr != next){
            resB.push_back(curr);
            continue;
        }
        qB.pop();
        qB.push(curr+1);
    }
    if(!qB.empty())
        resB.push_back(qB.top());
    
    reverse(resA.begin(), resA.end());
    reverse(resB.begin(), resB.end());

    if(resA == resB)
        return "Tie!";
    if(resA > resB)
        return "Alice will have more fun!";
    return "Bob will have more fun!";
}

int main(){
    int numCases; cin >> numCases;
    for(int c = 0; c < numCases; c++){
        cin >> n;
        qA = priority_queue<int, vector<int>, greater<int>>();
        for(int i = 0; i < n; i++){
            int ai; cin >> ai;
            qA.push(ai);
        }
        cin >> m;
        qB = priority_queue<int, vector<int>, greater<int>>();
        for(int j = 0; j < m; j++){
            int bj; cin >> bj;
            qB.push(bj);
        }
        cout << solve() << endl;
    }
}
