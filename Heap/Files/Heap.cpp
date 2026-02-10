#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>  

//cross platform
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

using namespace std;

//creat primary list
void create_primary_list(int number,vector<int>& list){
    if (number ==0){}
    else{list.push_back(number);}}

// creat minheap
vector<int> create_minheap(vector<int>& list){
    vector<int> minheap;
    minheap.push_back(list[0]);
    int size = list.size();

    for (int i=1;i<size;i++){
        minheap.push_back(list[i]);
        int parent=(i-1)/2;
        int child=i;

        while(child>0 && minheap[child] < minheap[parent]){
            int temp=minheap[child];
            minheap[child]=minheap[parent];
            minheap[parent]=temp;
            child =parent;
            parent=(child-1)/2;
        }
    }
    return minheap;
}

//creat maxheap
vector<int> create_maxheap(vector<int>& list){
    vector<int> maxheap;
    maxheap.push_back(list[0]);
    int size = list.size();

    for (int i=1;i<size;i++){
        maxheap.push_back(list[i]);
        int parent=(i-1)/2;
        int child=i;
        while(child>0 && maxheap[child] > maxheap[parent]){
            int temp=maxheap[child];
            maxheap[child]=maxheap[parent];
            maxheap[parent]=temp;
            child =parent;
            parent=(child-1)/2;
        }
    }
    return maxheap;
}

//insert number in heap
vector<int> insert_num(bool t,int number,vector<int>& heap){
    heap.push_back(number);
    int index_child=heap.size()-1;
    int index_parent=(index_child-1)/2;

    if (t){
        while(index_child>0 && heap[index_child]<heap[index_parent]){
            int temp=heap[index_child];
            heap[index_child]=heap[index_parent];
            heap[index_parent]=temp;
            index_child=index_parent;
            index_parent=(index_child-1)/2;
        }
    }
    else{
        while(index_child>0 && heap[index_child]>heap[index_parent]){
            int temp=heap[index_child];
            heap[index_child]=heap[index_parent];
            heap[index_parent]=temp;
            index_child=index_parent;
            index_parent=(index_child-1)/2;
        }
    }
    return heap;
}
// find index 
int find_index(int number,vector<int> &heap){
    auto it = find(heap.begin(),heap.end(),number);
    int index;
    if (it != heap.end()){
        index=it-heap.begin();
    }
    else{
        index=-1;
    }


    return index;
}

void Delet(bool t,int index,vector<int> &heap){
    heap[index]=heap.back();
    heap.pop_back();
    int size=heap.size();
    int target=index;
    
    //minheap
    if (t){
        while (true) {
            int left = 2*target + 1;
            int right = 2*target + 2;
            int smallest = target;

            if (left < size && heap[left] < heap[smallest])
                smallest = left;
            if (right < size && heap[right] < heap[smallest])
                smallest = right;

            if (smallest != target) {
                swap(heap[target], heap[smallest]);
                target = smallest;
            } 
            else {
                break; 
            }
        }
    }
    //maxheap
    else{
        while (true) {
            int left = 2*target + 1;
            int right = 2*target + 2;
            int largest = target;

            if (left < size && heap[left] > heap[largest])
                largest = left;
            if (right < size && heap[right] > heap[largest])
                largest = right;

            if (largest != target) {
                swap(heap[target], heap[largest]);
                target = largest;
            } else {
                break;
            }
        }

    }    
}

void Disply(vector<int>& heap) {
    int n = heap.size();
    if(n == 0) return;

    int maxLevel = floor(log2(n)) + 1;
    int index = 0;

    for(int level = 0; level < maxLevel; level++){
        int numNodes = 1 << level; // 2^level
        int spaceBefore = (1 << (maxLevel - level)) - 1;
        int spaceBetween = (1 << (maxLevel - level + 1)) - 1;

        
        for(int i = 0; i < spaceBefore; i++) cout << " ";

        
        for(int i = 0; i < numNodes && index < n; i++, index++){
            cout << "\033[1;32m" << heap[index] << "\033[0m";
            
            for(int j = 0; j < spaceBetween; j++) cout << " ";
        }
        cout << "\n";
    }
}

int main(){
    string back;
    system(CLEAR);
    int choice,num;
    
    int status =0;
    vector<int> primary_list;
    vector<int> minheap;
    vector<int> maxheap;

    while(true){
        cout << "\033[1;33m**********Menu**********\n\033[0m" << "\033[1;34m"
             << "1.Insert Primary number of heap\n"
             << "2.Insert number\n"
             << "3.Delete number\n"
             << "4.Display\n"
             << "5.Exit\n"
             << "\033[0m";
        cin >> choice;

        if (choice == 1){status=1;}

        if (status == 1){
            switch(choice){
                case 1:
                    primary_list.clear();
                    system(CLEAR);
                    cout << "\033[1;31minsert your list.(When It's Done Enter 0)\n\033[0m";
                    while(1){
                        cin >> num;
                        create_primary_list(num,primary_list);
                        if (num==0){
                            minheap=create_minheap(primary_list);
                            maxheap=create_maxheap(primary_list);
                            break;
                        }}
                    system(CLEAR);
                    break;
                case 2:
                    system(CLEAR);
                    cout << "\033[1;31mEnter The number:\n\033[0m";
                    cin >> num;
                    minheap=insert_num(true,num,minheap);
                    maxheap=insert_num(false,num,maxheap);


                    system(CLEAR);
                    break;
                case 3:{
                    system(CLEAR);
                    cout << "\033[1;31mEnter The number:\n\033[0m";
                    cin >> num;
                    int index_min=find_index(num,minheap);
                    int index_max=find_index(num,maxheap);
                    if (index_max==-1 || index_min==-1){
                        system(CLEAR);
                        cout << "\033[1;31mnumber is not in your list\n\033[0m";
                    }
                    else{
                        Delet(true,index_min,minheap);
                        Delet(false,index_max,maxheap);
                        system(CLEAR);
                    }
                    break;
                }
                case 4:
                    system(CLEAR);
                    int mn;
                    cout << "\033[1;34m1.Minheap\n2.Maxheap\n\033[0m";
                    cin >> mn;
                    if (mn==1){
                        system(CLEAR);
                        cout << "\033[1mList View:\n\033[0m" << "\033[1;32m[";
                        for (int i:minheap) cout <<i<<", ";
                        cout << "\b\b]\033[0m";
                        cout << "\033[1m\nTree View:\n\033[0m";
                        Disply(minheap);
                        cout << "\033[1;31m\nEnter any charactor to back:\n\033[0m";
                        
                        cin >> back;
                    }
                    else if(mn==2){
                        system(CLEAR);
                        cout << "\033[1mList View:\n\033[0m" << "\033[1;32m[";
                        for (int i:maxheap) cout <<i<<", ";

                        cout << "\b\b]\033[0m";
                        cout << "\033[1m\nTree View:\n\033[0m";
                        Disply(maxheap);
                        cout << "\033[1;31m\nEnter any charactor to back:\n\033[0m";
                        cin >> back;
                    }
                    else{
                        system(CLEAR);
                        continue;
                    }
                    system(CLEAR);
                    break;
                case 5:
                    return 0;
                default:
                    system(CLEAR);
                    cout << "\033[1;31mWarninng!!! Please choice the correct number\n\033[0m";
                    break;
            }
        }
        else if(choice==2 || choice==3 || choice==4 ){
            system(CLEAR);
            cout << "\033[1;31mNo primary list has been set.\nyou should first define a list.\n\033[0m";
        }
        else if (choice == 5){
            system(CLEAR);
            break;
        }
        else{
            system(CLEAR);
            cout << "\033[1;31mWarninng!!! Please choice the correct number\n\033[0m";
        }

}
}