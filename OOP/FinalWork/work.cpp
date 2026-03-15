// test_system_short.cpp
// g++ -std=c++17 test_system_short.cpp -o test_system && ./test_system
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

// ---------- helpers ----------

static string readLineTrim() {
    string s;
    getline(cin, s);
    auto l = s.find_first_not_of(" \t\r\n");
    if (l == string::npos) return "";
    auto r = s.find_last_not_of(" \t\r\n");
    return s.substr(l, r - l + 1);
}

static vector<string> split(const string &s, char d) {
    vector<string> v;
    string c;
    stringstream ss(s);
    while (getline(ss, c, d)) v.push_back(c);
    return v;
}

static string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

// ---------- user results ----------

struct Result {
    string testName;
    int score, total;

    string serialize() const {
        return testName + "," + to_string(score) + "," + to_string(total);
    }

    static Result d(const string &s) {
        auto p = split(s, ',');
        Result r;
        if (p.size() >= 3) {
            r.testName = p[0];
            r.score = stoi(p[1]);
            r.total = stoi(p[2]);
        }
        return r;
    }
};

// ---------- user ----------

struct User {
    string name, pass;
    bool admin = false;
    vector<Result> res;

    string serialize() const {
        string out = name + "|" + pass + "|" + (admin ? "1" : "0") + "|";
        for (size_t i = 0; i < res.size(); i++) {
            out += res[i].serialize();
            if (i + 1 < res.size()) out += ';';
        }
        return out;
    }

    static User d(const string &l) {
        User u;
        auto p = split(l, '|');
        if (p.size() < 3) return u;

        u.name = p[0];
        u.pass = p[1];
        u.admin = p[2] == "1";

        if (p.size() > 3 && !p[3].empty()) {
            auto rr = split(p[3], ';');
            for (auto &r : rr) u.res.push_back(Result::d(r));
        }
        return u;
    }
};

// ---------- questions ----------

class Question {
public:
    string prompt;
    int weight = 1;
    virtual ~Question() = default;
    virtual double ask() const = 0;
};

class SingleChoice : public Question {
public:
    vector<pair<string, bool>> opt;

    double ask() const override {
        cout << prompt << "\n";
        for (size_t i = 0; i < opt.size(); i++)
            cout << " " << i + 1 << ") " << opt[i].first << "\n";
        cout << "Your choice: ";

        string s = readLineTrim();
        int c = s.empty() ? -1 : stoi(s) - 1;

        return (c >= 0 && c < (int)opt.size() && opt[c].second) ? weight : 0;
    }
};

class Open : public Question {
public:
    string expected;

    double ask() const override {
        cout << prompt << "\nAnswer: ";
        string s = readLineTrim();
        return toLower(s).find(toLower(expected)) != string::npos ? weight : 0;
    }
};

// ---------- test ----------

class Test {
public:
    string name;
    vector<shared_ptr<Question>> qs;

    string serialize() const {
        string o = "TEST|" + name + "\n";
        for (auto &q : qs) {
            if (auto s = dynamic_pointer_cast<SingleChoice>(q)) {
                o += "SINGLE|" + to_string(s->weight) + "|" + s->prompt;
                for (auto &o1 : s->opt)
                    o += "|" + o1.first + "~" + (o1.second ? "1" : "0");
            } else if (auto o2 = dynamic_pointer_cast<Open>(q)) {
                o += "OPEN|" + to_string(o2->weight) + "|" + o2->prompt + "|" + o2->expected;
            }
            o += "\n";
        }
        o += "END\n";
        return o;
    }

    static shared_ptr<Test> d(const vector<string> &L, size_t &i) {
        if (i >= L.size()) return nullptr;

        auto h = split(L[i++], '|');
        if (h.size() < 2 || h[0] != "TEST") return nullptr;

        auto t = make_shared<Test>();
        t->name = h[1];

        while (i < L.size() && L[i] != "END") {
            auto p = split(L[i++], '|');
            if (p[0] == "SINGLE") {
                auto q = make_shared<SingleChoice>();
                q->weight = stoi(p[1]);
                q->prompt = p[2];
                for (size_t j = 3; j < p.size(); ++j) {
                    auto o = split(p[j], '~');
                    if (o.size() == 2) q->opt.push_back({o[0], o[1] == "1"});
                }
                t->qs.push_back(q);
            } else if (p[0] == "OPEN") {
                auto q = make_shared<Open>();
                q->weight = stoi(p[1]);
                q->prompt = p[2];
                q->expected = p[3];
                t->qs.push_back(q);
            }
        }

        if (i < L.size()) ++i;
        return t;
    }

    void run(User &u) {
        double s = 0;
        int tot = 0;

        for (auto &q : qs) tot += q->weight;
        for (auto &q : qs) s += q->ask();

        cout << "Score: " << s << "/" << tot << "\n";
        u.res.push_back({name, (int)s, tot});
    }
};

// ---------- system ----------

class Sys {
public:
    vector<User> users;
    vector<shared_ptr<Test>> tests;
    string uf = "users.txt", tf = "tests.txt";

    Sys() {
        loadU();
        loadT();
        if (!findU("admin")) addU("admin", "admin", true);
    }

    User *findU(const string &n) {
        for (auto &u : users)
            if (u.name == n) return &u;
        return nullptr;
    }

    bool addU(const string &n, const string &p, bool a = false) {
        if (findU(n)) return false;
        users.push_back({n, p, a, {}});
        saveU();
        return true;
    }

    void saveU() {
        ofstream o(uf);
        for (auto &u : users) o << u.serialize() << "\n";
    }

    void loadU() {
        ifstream in(uf);
        string l;
        while (getline(in, l))
            if (!l.empty()) users.push_back(User::d(l));
    }

    void saveT() {
        ofstream o(tf);
        for (auto &t : tests) o << t->serialize();
    }

    void loadT() {
        ifstream in(tf);
        string l;
        vector<string> L;
        while (getline(in, l)) L.push_back(l);
        size_t i = 0;
        while (i < L.size()) {
            if (L[i].rfind("TEST|", 0) == 0)
                tests.push_back(Test::d(L, i));
            else
                ++i;
        }
    }

    User *login(const string &n, const string &p) {
        auto *u = findU(n);
        return u && u->pass == p ? u : nullptr;
    }

    Test *findT(const string &n) {
        for (auto &t : tests)
            if (t->name == n) return t.get();
        return nullptr;
    }

    // ----------- menus -----------

    void admin(User &a) {
        while (true) {
            cout << "\n[Admin] 1)Add test 2)List 3)Add user 4)Logout\n> ";
            string c = readLineTrim();

            if (c == "1") {
                auto t = make_shared<Test>();
                cout << "Test name: ";
                t->name = readLineTrim();

                while (true) {
                    cout << "Add q? (y/n): ";
                    if (readLineTrim() != "y") break;

                    cout << "Type (1=single,2=open): ";
                    string tp = readLineTrim();

                    if (tp == "1") {
                        auto q = make_shared<SingleChoice>();
                        cout << "Prompt: ";
                        q->prompt = readLineTrim();
                        cout << "Weight: ";
                        q->weight = stoi(readLineTrim());

                        while (true) {
                            cout << "Option: ";
                            string o = readLineTrim();
                            if (o.empty()) break;
                            cout << "Correct(y/n): ";
                            bool cor = readLineTrim() == "y";
                            q->opt.push_back({o, cor});
                        }
                        t->qs.push_back(q);
                    } else {
                        auto q = make_shared<Open>();
                        cout << "Prompt: ";
                        q->prompt = readLineTrim();
                        cout << "Weight: ";
                        q->weight = stoi(readLineTrim());
                        cout << "Expected: ";
                        q->expected = readLineTrim();
                        t->qs.push_back(q);
                    }
                }

                tests.push_back(t);
                saveT();
                cout << "Added.\n";

            } else if (c == "2") {
                for (auto &t : tests)
                    cout << "- " << t->name << " (" << t->qs.size() << " q)\n";

            } else if (c == "3") {
                cout << "Name: ";
                string n = readLineTrim();
                cout << "Pass: ";
                string p = readLineTrim();
                addU(n, p, false);

            } else break;
        }
    }

    void user(User &u) {
        while (true) {
            cout << "\n[User] 1)List 2)Take test 3)Results 4)Logout\n> ";
            string c = readLineTrim();

            if (c == "1") {
                for (auto &t : tests)
                    cout << "- " << t->name << " (" << t->qs.size() << " q)\n";

            } else if (c == "2") {
                cout << "Test name: ";
                string n = readLineTrim();
                if (auto *t = findT(n)) {
                    t->run(u);
                    saveU();
                }

            } else if (c == "3") {
                for (auto &r : u.res)
                    cout << r.testName << " -> " << r.score << "/" << r.total << "\n";

            } else break;
        }
    }

    void run() {
        while (true) {
            cout << "\n1)Reg 2)Login 3)Exit\n> ";
            string c = readLineTrim();

            if (c == "1") {
                cout << "Name: ";
                string n = readLineTrim();
                cout << "Pass: ";
                string p = readLineTrim();
                addU(n, p);

            } else if (c == "2") {
                cout << "Name: ";
                string n = readLineTrim();
                cout << "Pass: ";
                string p = readLineTrim();

                auto *u = login(n, p);
                if (!u) {
                    cout << "Fail\n";
                    continue;
                }
                if (u->admin) admin(*u);
                else user(*u);

            } else break;
        }
    }
};

int main() {
    Sys s;
    s.run();
}
