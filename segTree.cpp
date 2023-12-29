#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<long long>arr;
void build_tree(vector<long long>input){
    int desired_length = pow(2, ceil(log2((int)input.size())));
    arr.resize(2*desired_length, 0);
    int j = 0;
    for(int i = desired_length; i < arr.size(); i++){
        if (j < input.size()){
            arr[i] = input[j];
            j += 1;
        }
    }
    arr[0] = -1;
    int start_idx = arr.size()/2 - 1;
    while(start_idx != 0){
        arr[start_idx] = arr[2 * start_idx] + arr[2 * start_idx + 1];
        start_idx -= 1;
    }
}

long long get_sum_in_range(int want_low, int want_high, int curr_node_idx = 1, int curr_low=1, int curr_high = -10){
    if (curr_high < 0){
        curr_high = arr.size() / 2;
    }
    if (curr_low >= want_low && want_high >= curr_high){
        return arr[curr_node_idx];
    }

    if (curr_low == curr_high || (curr_high < want_low || curr_low > want_high)){
        return 0;
    }

    int middle = (curr_high + curr_low) / 2;

    int left_child_curr_low = curr_low;
    int left_child_curr_high = middle;

    int right_child_curr_low = middle+1;
    int right_child_curr_high = curr_high;

    return get_sum_in_range(want_low, want_high, 2 * curr_node_idx, left_child_curr_low,left_child_curr_high)
    + get_sum_in_range(want_low, want_high, 2 * curr_node_idx + 1, right_child_curr_low,right_child_curr_high);
}

void update(int index, int value){
    index += ((arr.size() / 2) - 1);
    arr[index] = value;
    index /= 2;
    while(index != 0){
        arr[index] = arr[2*index] + arr[2*index+1];
        index/=2;
    }
}

void solve(){
    int n, q;
    cin >> n >> q;
    vector<long long>input(n);
    for(int i =0 ; i < n; i++){
        cin >> input[i];
    }
    build_tree(input);
    for(int i = 0; i < q; i++){
        int type, first, second;
        cin >> type >> first >> second;
        if (type == 1){
            update(first, second);
        }
        else{
            first = min(first, second);
            second = max(first, second);
            cout << get_sum_in_range(first, second) << endl;
        }        
    }
}

int main(){
    ios_base::sync_with_stdio(false);  
    cin.tie(NULL); 
    solve();
    return 0;
}
