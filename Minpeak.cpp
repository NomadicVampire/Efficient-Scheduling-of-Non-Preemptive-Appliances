#include<bits/stdc++.h>
using namespace std;

//Menu function
int menu(){
    int value;
    cout<<"Select the home appliances that needed to be scheduled:\n 1. Air Conditioner\n 2. Washing Machine\n 3. Oven\n 4. Refrigerator\n 5. Geaser\n 6. Other appliances\n 7. Schedule the input appliances\n Enter your choice: ";
    cin>>value;
    return value;
}

bool comp(pair<int, int>a, pair<int, int> b)
{
    return a.first > b.first;
}

//Return an array of size = T
vector<double> f(int T){
    vector<double> temp(T,0);
	return temp;
}


//function that puts value in given row for given no. of times from left to right
void putValue(int row, int start, int end, double powerConsumption, vector<vector<double>> &strips){
    for(int i = start; i<end; i++){
        strips[row][i] = powerConsumption;
    }
}




int main(){
    // -------------------------- Taking input devices -------------------------------

    //pair of power consumption, execution time
    //A[i][0] - power consumption,   
    //A[i][1] - execution time
    vector<pair<float, int>> A;

    //EER(Energy Efficiency Ratio)=cooling capacity of ac/power consumed by ac
    float EER[5] = {2.24,2.31,2.7,3.01,3.3};
    int ch = menu();
    while(ch != 7){
        int exectionTime;
        double powerConsumption;

        switch(ch){
            case 1:
                int star;
                float ton;
                cout<<"Enter the start rating and ton of AC: ";
                cin>>star>>ton;
                cout<<"Enter the execution time(in hour): ";
                cin>>exectionTime;
                //Cooling capacity of 1 ton is equal to 3.517 kW of power
                powerConsumption = (ton*3.517)/ EER[star-1];
                A.push_back(make_pair(powerConsumption*1000,exectionTime));
                break;
            
            case 2:
                cout<<"Enter the power consumption(in Watt) and execution time(in hour): ";
                cin>>powerConsumption>>exectionTime;
                A.push_back(make_pair(powerConsumption,exectionTime));
                break;

            case 3:
                cout<<"Enter the power consumption(in Watt) and execution time(in hour): ";
                cin>>powerConsumption>>exectionTime;
                A.push_back(make_pair(powerConsumption,exectionTime));
                break;

            case 4:
                cout<<"Enter the power consumption(in Watt) and execution time(in hour): ";
                cin>>powerConsumption>>exectionTime;
                A.push_back(make_pair(powerConsumption,exectionTime));
                break;

            case 5:
                cout<<"Enter the power consumption(in Watt) and execution time(in hour): ";
                cin>>powerConsumption>>exectionTime;
                A.push_back(make_pair(powerConsumption,exectionTime));
                break;

            case 6:
                cout<<"Enter the power consumption(in Watt) and execution time(in hour): ";
                cin>>powerConsumption>>exectionTime;
                A.push_back(make_pair(powerConsumption,exectionTime));
                break;
            
            default:
                cout<<"Invalid input\n";
                break;

        }

        ch = menu();
    }
    
    //No. of appliances
    int m = A.size();

    //Printing input values;
    cout<<"Entered inputs: \n Power Consumption \tExecution Time\n";
    for(int i=0; i<m; i++){
        cout<<A[i].first<<" "<<A[i].second<<endl;
    }

    // -------------------------  SCHEDULING  -----------------------------------

    int T;
    cout<<"Enter the scheduling horizon : "; 
    cin>>T;
    vector<int> L(T,0);  //Load array

    // Checking feasibility of the input specifications
    for(int i=0; i<m; i++) if(A[i].second>T){
        cout<<"Appliances can't be scheduled\n";
        cout<<"Device A"<<i+1<<" have execution time greater than scheduling horizon";
        return 0;
    }

    //sorting according to power consumption
    sort(A.begin(), A.end(), comp);
    cout<<"\nEntered inputs in sorted order w.r.t Power consumption: \n Power Consumption \tExecution Time\n";
    //Printing input values in sorted order in decereasing order w.r.t power consumption
    for(int i=0; i<m; i++){
        cout<<A[i].first<<" "<<A[i].second<<endl;
    }
    
    //Scheduling: 
    vector<vector<double>> strips;

    // space left in that row
    vector<int> space_left(m, T);
    // for(int i=0; i<space_left.size(); i++) cout<<space_left[i]<<" ";


    strips.push_back(f(T));

    //starting index of max value in that
    vector<int> maxValind(m, 0);


    // row_no., starting_index, executionTime/ending_index, powerConsuption, map
    for(int d=0; d<m; d++){
        bool fl = true;
        for(int i=0; i<strips.size(); i++){
            if(space_left[i] >= A[d].second){
                if(i == 0){
                    putValue(i, T - space_left[i], T - space_left[i] + A[d].second, A[d].first, strips);
                    space_left[i] -= A[d].second;
                    fl = false;
                }
                else{
                    putValue(i, space_left[i] - A[d].second, space_left[i], A[d].first, strips);
                    space_left[i] -= A[d].second;
                    fl = false;
                }
                i = strips.size();
            }
        }
        if(fl){
            strips.push_back(f(T));
            int r = strips.size()-1;
            putValue(r, space_left[r]-A[d].second, space_left[r], A[d].first, strips);
            space_left[r] -= A[d].second;
        }

    }


    for(int i=0; i< strips.size(); i++){
        for(int j=0; j< strips[i].size(); j++){
            cout<<strips[i][j]<<"\t";
        }
        cout<<endl;
    }
    int minPeak = INT_MIN;
    for(int j=0; j< strips[0].size(); j++){
        int sum = 0;
        for(int i=0; i< strips.size(); i++){
            sum += strips[i][j];
        }
        minPeak = max(minPeak, sum);
    }

    cout<<"Actual Schedule value : "<<minPeak;

    return 0;
}