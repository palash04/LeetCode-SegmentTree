class NumArray {
private: 
    vector<int> tree;
    vector<int> arr;
    int n;
public:
    int buildTree(int index, int start,int end){
        if (start == end){
            tree[index] = arr[start];
            return arr[start];
        }
        
        int mid = start + (end-start)/2;
        tree[index] = buildTree(2*index,start,mid) + buildTree(2*index+1,mid+1,end);
        return tree[index];
    }
    
    NumArray(vector<int>& nums) {
        if(nums.empty()) return;
        arr = std::move(nums);
        n = arr.size();
        tree.resize(4*n);
        buildTree(1,0,n-1);
    }
    
    void updateQ(int diff,int updateIndex,int start,int end, int index){
        
        if (updateIndex >= start && updateIndex <= end){
            tree[index] += diff;
        }
        if (start == end){
            return;  
        }
        int mid = start + (end-start)/2;
        if (updateIndex > mid){
            updateQ(diff,updateIndex,mid+1,end,2*index+1);
        }else{
            updateQ(diff,updateIndex,start,mid,2*index);
        }
        
    }
    
    void update(int i, int val) {
        int diff = val - arr[i];
        arr[i] = val;
        updateQ(diff,i,0,n-1,1);
    }
    
    int rangeQ(int l,int r,int start,int end,int index){
        if (start>=l && end<=r){
            return tree[index];
        }
        else if((start<l && end<l) || (start>r && end>r)){
            return 0;
        }else{
            int mid = start + (end-start)/2;
            return rangeQ(l,r,start,mid,2*index) + rangeQ(l,r,mid+1,end,2*index+1);
        }
    }
    
    int sumRange(int i, int j) {
        return rangeQ(i,j,0,n-1,1);
    }
};
