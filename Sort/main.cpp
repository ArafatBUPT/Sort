#include <iostream>
#include <assert.h>

using namespace std;

void BubbleSort(int arr[],int n){
    //第一循环设置每次的循环次数 第一次循环n-1次 第二次n-2次
    for (int i = 0; i < n-1; ++i) {
        //每次循环次数减少
        for (int j = 0; j <n-i-1; ++j) {
            if (arr[j]>arr[j+1])
                swap(arr[j],arr[j+1]);
        }
    }
}

void SelectionSort(int arr[],int n){

    //每次循环把第i个元素设成最小
    for (int i = 0; i < n; ++i) {
        int minIndex=i;
        //每循环一次 和 minIndex比较 最后 交换位置
        for (int j = i+1; j < n ; ++j) {
            if (arr[j]<arr[minIndex])
                minIndex=j;
        }
        swap(arr[i],arr[minIndex]);
    }
}

void InsertionSort(int arr[],int n){

    //从第二个元素开始 往前比较
    for (int i = 1; i < n ; ++i) {
        //每次把循环开始的元素存起来 跟前面比，比它大就赋值给当前元素
        int temp=arr[i],j;
        for (j = i; j >0 && arr[j-1]>temp; --j) {
            arr[j]=arr[j-1];
        }
        arr[j]=temp;
    }
}

void merge(int arr[],int l,int mid,int r){
    //设一个辅助数组 把分治好的元素存放在这个数组中
    int aux[r-l+1];
    for (int i = l; i <=r ; ++i) {
        aux[i-l]=arr[i];
    }

    // i 指向 辅助数组的第一元素 j指向辅助数组的中间+1
    int i=l;
    int j=mid+1;

    //k 从第一元素遍历 按大小赋值给arr数组
    for (int k = l; k <=r ; ++k) {
        if (i>mid){
            arr[k]=aux[j-l];
            j++;
        }
        else if (j>r){
            arr[k]=aux[i-l];
            i++;
        }
        else if (aux[i-l]<aux[j-l]){
            arr[k]=aux[i-l];
            i++;
        } else {
            arr[k]=aux[j-l];
            j++;
        }
    }
}
void mergeSort(int arr[],int l,int r){
    //分成一个元素后 返回
    if(l>=r)
        return;

    //设mid为数组中间位置
    int mid = l+(r-l)/2;

    //递归分成单个元素 再合并
    mergeSort(arr,l,mid);
    mergeSort(arr,mid+1,r);
    merge(arr,l,mid,r);
}
void mergeSort(int arr[],int n){
    // 递归函数
    mergeSort(arr,0,n-1);
}

int partition(int arr[],int l,int r){
    // 第一个元素设置成比较元素 j指向第一个位置
    int v = arr[l];
    int j=l;
    for (int i = l+1; i <=r ; ++i) {
        // i 位置的元素小于当前比较的v j前面的元素和i替换
        if (arr[i] < v) {
            swap(arr[j + 1], arr[i]);
            j++;
        }
    }
    //最后 第一位置和j交换
    swap(arr[l],arr[j]);
    return j;
}
void quickSort(int arr[],int l,int r){
    if(l>=r)
        return;

    //p 分成两部分
    int p = partition(arr,l,r);
    quickSort(arr,l,p-1);
    quickSort(arr,p+1,r);
}


template <typename Item>
class maxHeap{

private:
    Item* data;
    int count;
    int capacity;

    void shiftUp(int k){
        while (k>1 && data[k/2]<data[k]){
            swap(data[k/2],data[k]);
            k/=2;
        }
    }

    void shiftDown(int k){
        while (k*2<=count){

            int j =2*k;//在此轮循环中，data[k]和data[j]交换
            if (j+1<=count && data[j+1]>data[j])
                j+=1;
            if (data[k]>=data[j])
                break;
            swap(data[k],data[j]);
            k=j;
        }
    }

public:
    maxHeap(int capacity){
        data = new Item[capacity+1];
        count = 0;
        this->capacity=capacity;
    }
    ~maxHeap(){
        delete [] data;
    }

    int size(){
        return count;
    }

    bool empty(){
        return count==0;
    }

    void insert(Item item){

        assert(count+1<=capacity);

        data[count+1]=item;
        count++;
        shiftUp(count);
    }

    Item getMax(){

        assert(count>0);

        Item res=data[1];
        swap(data[1],data[count]);
        count--;
        shiftDown(1);
        return res;
    }

    void pr(){
        for (int i = 1; i <= count; ++i) {
            cout<<data[i]<<' ';
        }
        cout<<endl;
    }



};



int main() {

    maxHeap<int> m = maxHeap<int>(30);

    m.insert(5);
    m.insert(3);
    m.insert(10);
    m.insert(300);

    m.pr();

    m.getMax();
    m.pr();
}
