#include<bits/stdc++.h>
using namespace std;

bool comp(pair<int, int>a, pair<int, int> b)
{
    return a.first > b.first;
}

int main(){
    int m;
    cout<<"Enter the number of devices that needed to be scheduled: ";
    cin>>m;
    int P[m];    // power consumption for each m defferable appliances
    int E[m];   // Execution time for each m defferable appliances
    int T;     //  scheduling horizon (scheduling deadline)
    cout<<"Enter the scheduling horizon : "; 
    cin>>T;
    vector<int> L(T,0);  //Load array
    vector<vector<int>> G;


    //power consumption input
    cout<<"Enter the power consumption for each appliaces: ";
    for(int i=0; i<m; i++) cin>>P[i];
    
    cout<<"Enter the execution time for each appliaces: ";
    for(int i=0; i<m; i++) cin>>E[i];

    for(int i=0; i<m; i++) if(E[i]>T){
        cout<<"Appliances can't be scheduled";
        return 0;
    }

    vector<pair<int, int>> P_E;
    for(int i=0; i<m; i++) {
        int temp = P[i]/E[i];
        P_E.push_back(make_pair(temp, i));
    }

    sort(P_E.begin(), P_E.end(), comp);

    // for(int i=0; i<m; i++) cout<<P_E.at(i).first<<"  "<<P_E.at(i).second<<endl;
    
    for(int i=0; i<m; i++){
        int ind = P_E.at(i).second;
        int val = P_E.at(i).first;

        //no of discrete values of exection time
        int exe = E[ind];
        int cnt = 0;
        while(exe>0){
            L[cnt] += val;
            cnt++;
            exe--;
        }
        sort(L.begin(), L.end());
    }
    cout<<"MinPeak of given appliances is: "<<L[T-1];
    
    return 0;

}