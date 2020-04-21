#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <iterator>
#define INPUT_FILE "Sample.int"
#define OUTPUT_FILE "Output"
using namespace std;

typedef long long ll;
unordered_map<string, int> NUM{{"new",1},{"request",2},{"terminate",3}};
unordered_map<ll, vector<ll>> MAX;
unordered_map<ll, vector<ll>> NEED;



bool safety_check(vector<ll> resources){ // 检查当前resources是否满足request或者new
    queue<ll> temp;
    int count = 0;
    bool valid = true;
    ll temppid;
    for(int i=0;i<NEED.bucket_count();i++){ //获取unordered_map里的key值
        for(auto iter=NEED.begin(i);iter!=NEED.end(i);++iter){
            temp.push(iter->first);
        }
    }
    while(!temp.empty() && count < temp.size()){ //count防止死循环
        valid = true;
        temppid = temp.front();
        temp.pop();
        for(int i=0;i<resources.size();++i){
            if(resources[i]<NEED.at(temppid)[i]){ //如果当前resources不满足当前pid的NEED，就放回队列
                temp.push(temppid);
                valid=false;
                break;
            }
        }
        count++;
        if(valid){ // 如果满足则认为该pid能跑完，就返回该pid之前占用的resources
            for(int i=0;i<resources.size();++i){
                resources[i] = resources[i] - NEED.at(temppid)[i] + MAX.at(temppid)[i];
            }
            count = 0;
        }
    }
    if(temp.empty()) // 如果遍历完队列，队列为空说明safe，反之为unsage
        return true;
    else
        return false;
}

int main(){
    ll n;
    ll pid;
    string command;
    string stage;
    cin>>n;
    vector<ll> resources(n);
    vector<ll> requirements(n); 
    for(int i=0;i<n;++i){
        cin>>resources[i];
    }
    while(!cin.eof()){
        stage = "";
        cin>>pid>>command;
        switch(NUM.at(command)){
        case 1: // new，检查资源是否满足，如果满足就判断剩余资源分配是否安全
            for(int i=0;i<n;++i){
                cin>>requirements[i];
            }
            for(int i=0;i<n;++i){
                if (requirements[i]>resources[i]){
                    stage = "NOT OK";
                    break;
                }
            }
            if(!stage.empty()){ // 不满足则打印NOT OK，break
                cout<<stage<<endl;
                break;
            }
            if(safety_check(resources)){
                MAX.insert(pair<ll, vector<ll>> {pid, requirements});
                NEED.insert(pair<ll, vector<ll>> {pid, requirements});
                stage = "OK";
            }
            else
                stage = "NOT OK";
            cout<<stage<<endl;
            break;
        case 2: // request   
            for(int i=0;i<n;++i){
                cin>>requirements[i];
            }
            for(int i=0;i<n;++i){
                if (requirements[i]>resources[i]||requirements[i]>MAX.at(pid)[i]||requirements[i]>NEED.at(pid)[i]){
                    stage = "NOT OK";
                    break;
                }
            }
            if(!stage.empty()){
                cout<<stage<<endl;
                break;
            }
            for (int i = 0; i < n; i++){ //同理，先减掉requirement
                resources[i] -= requirements[i];
                NEED.at(pid)[i] -= requirements[i];
            }
            if(safety_check(resources))
                stage = "OK";
            else{
                for (int i = 0; i < n; i++){
                    resources[i] += requirements[i];
                    NEED.at(pid)[i] += requirements[i];
                }
                stage = "NOT OK";
            }
            cout<<stage<<endl;
            break;
        case 3: // terminate
            stage = "OK";
            for(int i=0;i<n;++i){
                resources[i]+=MAX.at(pid)[i];
            }
            MAX.erase(pid);
            NEED.erase(pid);
            cout<<stage<<endl;
            break;
        default:
            break;
        }

    }
    return 0;
}
