#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

class ReadStats {
private:

    static const int MAX_USER_COUNT = 100000;
    static const int MAX_PAGE_NUMBER = 1000;

    vector<int> user_to_page_;
    vector<int> page_to_users_;
    unsigned int ppl = 0;
    

    double CheckStat(int user) {
        int curr_page = user_to_page_[user];
        if (!curr_page) {
            return 0;
        }
        if (ppl == 1) {
            return 1;
        }               
        double result = 0.0;
        double ppl_with_less = 0;       
        for (int i = 0; i < curr_page; ++i) {
            ppl_with_less += page_to_users_[i];
        }
        result = ppl_with_less  / (ppl - 1);
        return result;
    }


public:
    ReadStats(): user_to_page_(MAX_USER_COUNT + 1), page_to_users_(MAX_PAGE_NUMBER + 1)
    {}

    void SaveProgress(int user, int page) {
        int prev_page = user_to_page_[user];
        if (!prev_page) {
            ppl++;
        }           
        else {                                        
            page_to_users_[prev_page]--;
        }
        user_to_page_[user] = page;
        page_to_users_[page]++;
    }

    void PrintCheer(int user) {       
        double result = CheckStat(user);
        cout << setprecision(6) << result << "\n";
    }
};


int main() {
    ReadStats stat;
    int requests;
    cin >> requests;
    for (int i = 0; i < requests; ++i) {
        string req_type;
        int user = 0;
        cin >> req_type >> user;
        if (req_type == "READ") {
            int page = 0;            
            cin >> page;
            stat.SaveProgress(user, page);
        }
        else if (req_type == "CHEER") {           
            stat.PrintCheer(user);
        }
    }
    return 0;
}