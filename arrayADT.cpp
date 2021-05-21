#include <iostream>

using namespace std;


template <class T>

class Array
{
    private:
        T *A;
        int size;
        int length;
    public:
        Array(){
            size=10;
            length = 0;
            A = new T[size];
            for(int i=0; i<size;i++) A[i]=0;
        };
        Array(int sz){
            size = sz;
            length = 0;
            A = new T[size];
            for(int i=0; i<size;i++) A[i]=0;
        };
        Array(const Array &B){
            size = B.size;
            length = B.length;
            for(int i=0; i>length; i++){
                A[i] = B.A[i];
            }
        };
        ~Array(){
            delete []A;
        };
        void swap(T *x, T *y){
            T temp = *x;
            *x = *y;
            *y = temp;
        };

        void Display();
        void insert(T key, int i);
        void append(T key);
        T del(int i);
        T lSearch(T key);
        T bSearch(int low, int high, T key);
        int getL();
        int getSz();
        T* getArr();
        void setL(int l);
        void setSz(int sz);
        T get(int index);
        T set(int i, T key);
        T max();
        T min();
        T sum(int n);
        T avg(int n);
        void reverse();
        void lshiftWithrotation();
        int isSorted();
        int insertInSortedArr(T key);
        void mergeSorted(Array* B);
        void unsortUnion(Array* C);
        void unsortIntersect(Array* C);
};

template <class T>
void Array<T>::Display(){
    int i;
    cout<<"Elements are:"<<endl;
    for(i=0; i<length;i++) cout<<A[i]<<" ";
    cout<<" "<<endl;
};

template <class T>
void Array<T>::insert(T key, int i){
    if(length>=size) cout<<"Insertion not possible!"<<endl;
    else{
        for(int j=length;j>i;j--) A[j]=A[j-1];               // O(n) time
        A[i] = key;
        length++;
    };
};

template <class T>
void Array<T>::append(T key){
    if(length==size) cout<<"Array is full, cant append!"<<endl;

    else{
        A[length] = key;                                      // O(1) TIME
        length++;
    };
};

template <class T>
T Array<T>::del(int i){
    if(i<0) cout<<"Can't delete element at negative index"<<endl;
    else if(i>length) cout<<"Index exceeds array length"<<endl;
    else{
        T x = A[i];
        for(int j=i; j<length-1;j++) A[j] = A[j+1];
        A[length]=0;
        length--;                                          // O(n) time
        return x;
    };
    return 0;
};

template <class T>
T Array<T>::lSearch(T key){
    for(int i=0; i<length; i++){
        if (key==A[i]){                                    // O(n) time
            cout<<"Search successful, element found at "<<i<<"th position"<<endl;
            swap(&A[i], &A[i-1]);
            return i;
        };
        // Two ways of improving linear search
        // Transposition: If you find key at some index,
        // swap the key with the element at one index below.
        // swap(arr.A[i], arr.A[i-1]);
        // Progressively reduces steps-> n, n-1, n-2...1
        // Worst case time for first n-steps = n/2 = O(n)
        // Post n-steps = O(1)
        //
        // Move to head: If you find key at some index,
        // swap the key with the first element of array.
        // swap(arr.A[i], arr.A[0]);
        // Worst case time for searching element again: O(1)
    }
    cout<<"Element not found in array"<<endl;
    return 0;
};

template <class T>
T Array<T>::bSearch(int low, int high, T key){
    if(low>high) return high;                                 // O(log n) time for sorted array
    else{
        int mid = (low+high)/2;                               // Doesn't work for unsorted array
        if(A[mid]==key){
            cout<<"Search successful, element found at "<<mid<<"th position"<<endl;
            return mid;
        }
        else if(A[mid]>key) return bSearch(low, mid-1, key);
        else return bSearch(mid+1, high, key);
    };
};

template <class T>
int Array<T>::getL(){
    return length;                                                    // O(1)
};

template <class T>
int Array<T>::getSz(){
    return size;                                                      // O(1)
};

template <class T>
T* Array<T>::getArr(){
    return A;                                                         // O(1)
};

template <class T>
void Array<T>::setL(int l){
    length = l;                                                       // O(1)
};

template <class T>
void Array<T>::setSz(int sz){
    size = sz;                                                        // O(1)
};

template <class T>
T Array<T>::get(int index){
    if(index<0) cout<<"Can't retrieve element at negative index.";
    else if (index>length) cout<<"Index exceeds array length.";
    else{
        return A[index];
    }
    return -1;                                                        // O(1)
};

template <class T>
T Array<T>::set(int i, T key){
    if(i<0) cout<<"Can't set element at negative index.";
    else if (i>size) cout<<"Index exceeds array length.";
    else{
        T prev = A[i];
        A[i]=key;
        return prev;
    }
    return -1;                                                        // O(1)
};

template <class T>
T Array<T>::max(){
    T m = A[0];
    for (int i=1; i<length; i++) {                  // 1 + 1 + (n+1) + n + n + 1 + 1 = 3n+6 = O(n)
        m = A[i]*(A[i]>m) + m*(A[i]<=m);            // Nice branchless programming
    }
    return m;
};

template <class T>
T Array<T>::min(){
    T m = A[0];
    for (int i=1; i<length; i++) {                  // O(n)
        m = A[i]*(A[i]<m) + m*(A[i]>=m);            // Nice branchless programming
    }
    return m;
};

template <class T>
T Array<T>::sum(int n){
    if (n-1<0) return 0;                            // O(n)
    else return sum(n-1) + A[n-1];                  // As you can't access A[length]
};

template <class T>
T Array<T>::avg(int n){
    if (n-1<0) return 0;
    else return (sum(n-1) + A[n-1])/n;              // n+1 + n + n = O(n)
};

template <class T>
void Array<T>::reverse(){
    for (int i=0; i<length/2;i++){                  // If we used auxillary array then we would
                                                    // need two loops: O(2*(5n/2+2)) = O(n)
        swap(&A[i], &A[length-1-i]);                // 1 + (n/2+1) + n + n + 1 = 5n/2 + 3 = O(n)
    }
    Display();
};
template <class T>
void Array<T>::lshiftWithrotation(){

    T temp = A[0];
    for(int i=1; i<length;i++){
        A[i-1] = A[i];                              // O(n)
    };
    A[length-1]=temp;
    Display();
};

template <class T>
int Array<T>::isSorted(){
    for (int i =0; i<length-1;i++){
        if(A[i]>A[i+1]){
            return -1;                             // O(n)
        };
    };
    return 0;
};

template <class T>
int Array<T>::insertInSortedArr(T key){
    if (isSorted()==-1) return -1;                 // Check if array is sorted-> n
    int index = bSearch( 0, length-1, key);        // Find index to insert-> log n
    insert( key, index+1);                         // Insert number-> n
                                                   // O(n)
    Display();
    return 0;
};

template <class T>
void Array<T>::mergeSorted(Array* B){
    if(isSorted()==-1 || B->isSorted()==-1) {
        cout<<"Arrays not sorted"<<endl;
    }
    else{
            Array *arr;
            arr = new Array(length + B->getL());
            arr->setL(length+B->getL());
            int i=0,j=0,k=0;
            while(i<length && j<B->getL()){
                T * B_dash =B->getArr();
                if(A[i]<B_dash[j]) arr->set(k++, A[i++]);
                //else if(arr1.A[i]==arr2.A[j]){
                //arr.A[k++] = arr1.A[i++];        //  Sorted Union
                //j++;
                //}
                else arr->set(k++, B->get(j++));
            };
        //while(i<arr1.length && j<arr2.length){
        // if(arr1.A[i]<arr2.A[j]) i++;
        // else if(arr1.A[i]<=>arr2.A[j]) j++;     // Sorted Intersect
        // else arr.A[k++] == (arr1.A[i++] + arr2.A[j++])/2;
        for (;i<length;i++) arr->set(k++,A[i]);
        for (;j<B->getL();j++) arr->set(k++,B->get(j));      // Theta(m+n)
        arr->Display();
    };
};

template <class T>
void Array<T>::unsortUnion(Array* C){
    int max1 = max();                                // O(n)
    int max2 = C->max();                             // O(m)
    int max3 = max1*(max1>max2) + max2*(max2>=max1); // O(1)
    int B[max3+1] = {0};                             // O(k)
    Array *arr3;
    arr3 = new Array(length + C->getL());            // O(1)
    cout<<"SIZE OF ARR3: "<< arr3->getSz()<<endl;
    int i =0, j=0,k=0;                               // O(1)
    for(; i<length;i++){                             // O(n)
        if(B[A[i]]==0){                              // O(1)
            arr3->set(k++, A[i]);                    // O(1)
        };
        B[A[i]]++;                                   // O(1)
    };
    T* C_dash = C->getArr();
    for(; j<C->getL();j++){                          // O(m)
        if(B[C_dash[j]]==0){                         // O(1)
            arr3->set(k++, C_dash[j]);               // O(1)
        };
        B[C_dash[j]]++;                              // O(1)
    };
    arr3->setL(k);                                   // O(1)
    arr3->Display();                                 // O(m+n)
                                                     // Total: O(m+n) on average
                                                     // but if max3>m+n, then O(k)
};

template <class T>
void Array<T>::unsortIntersect(Array* C){
    int max1 = max();                                // O(n)
    int max2 = C->max();                             // O(m)
    int max3 = max1*(max1>max2) + max2*(max2>=max1); // O(1)
    int B[max3+1] = {0};                             // O(k)
    Array *arr3;                                     // O(1)
    arr3 = new Array(length+C->getL());              // O(m+n)
    int i =0, j=0;                                   // O(1)
    for(; i<length; i++){                            // O(n)
        B[A[i]]++;                                   // O(1)
    };
    int k=0;                                         // O(1)
    for(; j<C->getL();j++){                          // O(m)
        ++B[C->get(j)];                              // O(1)
        if(B[C->get(j)]>=2){                         // O(1)
            arr3->set(k++,C->get(j));                // O(1)
            B[C->get(j)]=0;                          // O(1)
        };
    };
    arr3->setL(k);                                   // O(1)
    arr3->Display();                                 // O(m+n)
                                                     // Total: O(m+n+k)
};
//=========================================================================
//=========================================================================
int main(){
    Array<int> *A;
    A = new Array<int>();
    int key;                       // Change key data-type if Array not int
    int choice;
    do{
        cout<<"\n### MENU ###"<<endl;
        cout<<"1. Create"<<endl;
        cout<<"2. Insert"<<endl;
        cout<<"3. Append"<<endl;
        cout<<"4. Delete"<<endl;
        cout<<"5. Sum upto n"<<endl;
        cout<<"6. Average upto n"<<endl;
        cout<<"7. Min"<<endl;
        cout<<"8. Max"<<endl;
        cout<<"9. Display"<<endl;
        cout<<"10. Reverse"<<endl;
        cout<<"11. Linear Search"<<endl;
        cout<<"12. Binary Search"<<endl;
        cout<<"13. Left Shift with Rotation"<<endl;
        cout<<"14. Insert in Sorted Array"<<endl;
        cout<<"15. Merge Sorted Arrays"<<endl;
        cout<<"16. Union of Unsorted Arrays"<<endl;
        cout<<"17. Intersection of Unsorted Arrays"<<endl;
        cout<<"18. Exit"<<endl;
        cout<<"\nEnter your choice: ";
        cin>>choice;

        switch(choice){
            int n, i, size, l;
            Array<int> *B;
            B = new Array<int>();

            case 1:
                cout<<"Enter length: ";
                cin>>l;
                size = 2*l;
                if(A = new Array<int>(size)) cout<<"1\n";
                else cout<<"\n0\n";
                cout<<endl<<"Enter elements of new  array: ";
                for(int i=0;i<l;i++){
                    cin>>key;
                    if(key==NULL) break;
                    A->insert(key,i);
                }
                break;

            case 2:
                cout<<"Enter key and index (in that order): ";
                cin>>key>>i;
                A->insert(key, i);
                cout<<endl;
                break;

            case 3:
                cout<<"Enter key: ";
                cin>>key;
                A->append(key);
                cout<<endl;
                break;

            case 4:
                cout<<"Enter index to be deleted: ";
                cin>>i;
                cout<<"Element: ("<<A->del(i)<<") deleted"<<endl;
                break;

            case 5:
                cout<<"Enter n (or enter -1 for sum of entire length): ";
                cin>>n;
                if(n==-1) n = A->getL();
                cout<<"Sum upto "<<n<<": "<<A->sum(n)<<endl;
                cout<<endl;
                break;

            case 6:
                cout<<"Enter n (or enter -1 for sum of entire length): ";
                cin>>n;
                if(n==-1) n = A->getL();
                cout<<"Avg upto "<<n<<": "<<A->avg(n)<<endl;
                cout<<endl;
                break;

            case 7:
                cout<<"Min: "<<A->min()<<endl;
                break;

            case 8:
                cout<<"Max: "<<A->max()<<endl;
                break;

            case 9:
                A->Display();
                break;

            case 10:
                A->reverse();
                break;

            case 11:
                cout<<"Enter key: ";
                cin>> key;
                cout<<endl;
                A->lSearch(key);
                cout<<endl;
                break;

            case 12:
                cout<<"Enter key: ";
                cin>> key;
                cout<<endl;
                if(A->isSorted()==0) A->bSearch(0, A->getL()-1, key);
                else cout<<"Array not sorted"<<endl;
                cout<<endl;
                break;

            case 13:
                A->lshiftWithrotation();
                break;

            case 14:
                cout<<"Enter key: ";
                cin>>key;
                A->insertInSortedArr(key);
                cout<<endl;
                break;

            case 15:
                cout<<"Enter length of new sorted array: ";
                cin>>l;
                if(B = new Array<int>(2*l)) cout<<"1\n";
                else cout<<"0\n";
                cout<<endl<<"Enter elements of new sorted array: ";
                for(int i=0;i<l;i++){
                    cin>>key;
                    B->insert(key,i);
                }
                cout<<endl;
                A->mergeSorted(B);
                break;

            case 16:
                cout<<"Enter length of array: ";
                cin>>l;
                if(B = new Array<int>(2*l)) cout<<"1\n";
                else cout<<"0\n";
                cout<<endl<<"Enter elements of array: ";
                for(int i=0;i<l;i++){
                    cin>>key;
                    B->insert(key,i);
                }
                cout<<endl;
                A->unsortUnion(B);
                break;

            case 17:
                cout<<"Enter length of array: ";
                cin>>l;
                if(B = new Array<int>(2*l)) cout<<"1\n";
                else cout<<"0\n";
                cout<<endl<<"Enter elements of array: ";
                for(int i=0;i<l;i++){
                    cin>>key;
                    B->insert(key,i);
                }
                cout<<endl;
                A->unsortIntersect(B);
                break;

            case 18:
                break;

            default:
                cout<<"Erroneous input"<<endl;
                break;

            B->~Array();

        };
    };
    while(choice!=18);
    A->~Array();
    return 0;
}
