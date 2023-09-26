#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<class S, class T> string join(S sep, vector<T>& vec){
    stringstream res;
    rep(i, 0, vec.size()){
        if(i) res << sep;
        res << vec[i];
    }
    return res.str();
}

typedef pair<pair<int, vector<int>>, pair<int, vector<int>>> testcase;
typedef string answer;

const string aliceWin = "Alice will have more fun!",
               bobWin = "Bob will have more fun!",
              tieGame = "Tie!";

ostream& operator<<(ostream &os, testcase &tc){
    auto [astuff, bstuff] = tc;
    os << astuff.first << "\n" << join(" ", astuff.second) << "\n";
    return os << bstuff.first << "\n" << join(" ", bstuff.second);
}

testcase genTestcase(int maxn, int maxv){
    int a = 1+(rand()%maxn), b = 1+(rand()%maxn);
    vector<int> avec(a), bvec(b);
    for(auto &x : avec) x = 1+(rand()%maxv);
    for(auto &x : bvec) x = 1+(rand()%maxv);
    return {{a, avec}, {b, bvec}};
}

answer solve(testcase tc){
    auto [astuff, bstuff] = tc;
    auto [a, as] = astuff;
    auto [b, bs] = bstuff;
    map<int, int> fa, fb;
    for(auto x : as) fa[x]++;
    for(auto x : bs) fb[x]++;
    
    sort(all(as)); sort(all(bs));

    for(auto it = fa.begin(); it != fa.end(); it++){
        auto [k, v] = *it;
        if(v/2) fa[k+1] += v/2;
        fa[k] = v&1;
    }

    for(auto it = fb.begin(); it != fb.end(); it++){
        auto [k, v] = *it;
        if(v/2) fb[k+1] += v/2;
        fb[k] = v&1;
    }

    vector<int> ares, bres;
    for(auto [k, v] : fa){
        assert(v < 2);
        if(v) ares.push_back(k);
    }
    for(auto [k, v] : fb){
        assert(v < 2);
        if(v) bres.push_back(k);
    }
    sort(ares.rbegin(), ares.rend());
    sort(bres.rbegin(), bres.rend());

    if(ares == bres) return tieGame;
    if(ares > bres) return aliceWin;
    return bobWin;
}

vector<testcase> trickyCases(){
    vector<testcase> res;
    
    { // A case where alice has 100k of 1e8 (which merge to 1e8 + 16) and bob has 1 of 1e8+16
      // Also the same case, but bob has 1e8 + 17, so he wins
        int a = 100000;
        vector<int> as(a, 1e8);
        testcase lose = {{a, as}, {1, {int(1e8 + 16)}}};
        testcase win = {{a, as}, {1, {int(1e8 + 17)}}};

        assert(solve(lose)==aliceWin);
        assert(solve(win)==bobWin);

        res.push_back(lose);
        res.push_back(win);
    }

    { // A case where alice has 2 ones, and then one of every number up to 1e5-1
      // and bob has 1e5, 1e5-1, and 1e5+1 resulting in tie, alicewin, and bobwin
        int a = 100000;
        vector<int> as(2, 1);
        for(int i = 2; as.size() < a; i++) as.push_back(i);

        testcase tiee = {{a, as}, {1, {int(1e5)}}};
        testcase alice = {{a, as}, {1, {int(1e5 - 1)}}};
        testcase bob = {{a, as}, {1, {int(1e5 + 1)}}};

        assert(solve(tiee) == tieGame);
        assert(solve(alice) == aliceWin);
        assert(solve(bob) == bobWin);

        res.push_back(tiee); res.push_back(alice); res.push_back(bob);
    }

    { // Cases where they tie on the first item so comparison continues downward
        testcase alice = {{3, {2, 3, 4}}, {3, {1, 3, 4}}};
        testcase bob = {{3, {1, 3, 4}}, {3, {2, 3, 4}}};
        assert(solve(alice) == aliceWin);
        assert(solve(bob) == bobWin);
        
        res.push_back(alice); res.push_back(bob);
    }

    { // Cases where they tie but someone has an extra item
        testcase alice = {{3, {1, 3, 4}}, {2, {3, 4}}};
        testcase bob = {{2, {3, 4}}, {3, {1, 3, 4}}};

        assert(solve(alice) == aliceWin);
        assert(solve(bob) == bobWin);
        
        res.push_back(alice); res.push_back(bob);
    }

    return res;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vector<testcase> samples = {
        {{2, {100, 200}}, {5, {101, 102, 103, 104, 105}}},
        {{4, {2, 2, 2, 2}}, {2, {3, 3}}}
    };

    vector<testcase> input;
    vector<answer> output;

    cout << "Generating..." << endl;
    for(auto x : samples) input.push_back(x);
    rep(i, 0, 3) input.push_back(genTestcase(20, 100)); // Small correctness cases
    rep(i, 0, 3) input.push_back(genTestcase(1000, 100000)); // Medium correctness
    rep(i, 0, 2) input.push_back(genTestcase(100000, int(1e9))); // TLE cases (no merges, probably)

    rep(i, 0, 10) input.push_back(genTestcase(20, 15)); // small pigeonhole cases
    rep(i, 0, 5) input.push_back(genTestcase(1000, 500)); // medium pigeonhole cases
    rep(i, 0, 5) input.push_back(genTestcase(100000, int(1e4))); // large pigeonhole cases

    auto tricky = trickyCases();
    for(auto c : tricky) input.push_back(c);

    cout << "Solving..." << endl;
    for(auto x : input) output.push_back(solve(x));


    ofstream inFile("stones.in");
    ofstream outFile("stones.out");

    cout << "Printing..." << endl;
    inFile << input.size() << endl;
    for(auto x : input) inFile << x << endl;
    for(auto x : output) outFile << x << endl;

    return 0;
}
