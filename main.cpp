#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;
using namespace std::chrono;

void random(int n, int maxx, vector<int> & v)
{
    srand((unsigned)time(0));
    int randomnumber;
    for(int i = 0; i < n; i++)
    {
        randomnumber = rand()*rand()% maxx;
        v.push_back(randomnumber);
    }
}

bool test(vector<int> & v, int n)
{
    for(int i = 1; i <= n-1; i++)
        if(v[i] < v[i-1])
            return false;
    return true;
}
void bubblesort(int n, vector<int> & v)
{
    auto start0 = high_resolution_clock::now();
    int i, ok;
    do
    {
        ok = 1;
        for(i = 0; i < n; i++)
            if(v[i] > v[i+1])
            {
                v[i] += v[i+1];
                v[i+1] = v[i] - v[i+1];
                v[i] -= v[i+1];
                ok = 0;
            }
    }
    while(ok == 0);
    auto stop0 = high_resolution_clock::now();
    auto duration0 = duration_cast<microseconds>(stop0 - start0);
    if(test(v, n) == true)
        cout << "Bubblesort: CORECT- Timpul de rulare: "<<duration0.count()/1000000.00000000000000<<" secunde "<<'\n';
    else
        cout << "Bubblesort nu a sortat bine"<<endl;
}

void countsort(int n, vector <int> & v)
{
    auto start1 = high_resolution_clock::now();
    int  i, j=0, maxx = v[0];
    vector <int> cnt;
    for(i = 1; i < n; i++)
        if(v[i] > maxx)
            maxx = v[i];
    for(i = 0; i <= maxx; i++)
        cnt.push_back(0);
    for(i = 0; i < n; i++)
        cnt[v[i]]++;
    for(i = 0; i<= maxx; i++)
        while(cnt[i] > 0)
        {
            v[j++] = i;
            cnt[i]--;
        }
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    if(test(v, n) == true)
        cout << "Countsort: CORECT- Timpul de rulare: "<<duration1.count()/1000000.00000000000000 <<" secunde"<< endl;
    else
        cout << "Countsort nu a sortat bine"<<endl;
}

void merge(vector <int> & v, int low, int m, int high)
{
    int i, j, k;
    int n1 = m - low + 1;
    int n2 =  high - m;

    int *L = new int[n1], *R = new int[n2];

    for (i = 0; i < n1; i++)
        L[i] = v[low + i];
    for (j = 0; j < n2; j++)
        R[j] = v[m + 1+ j];

    i = 0;
    j = 0;
    k = low;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else
        {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        v[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector <int> & v, int low, int high)
{
    if (low < high)
    {
        long long m = low+(high-low)/2;

        mergeSort(v, low, m);
        mergeSort(v, m+1, high);

        merge(v, low, m, high);
    }
}
int pozitie(int p, int u, vector<int> & v)
{
    int pivot = v[u], i = p - 1;
    for(int j = p; j <= u - 1; j++)
    {
        if(v[j] < pivot)
        {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i+1], v[u]);
    return (i + 1);

}
void quicksort(int p, int u, vector<int> & v)
{
    if(p < u)
    {
        int x = pozitie(p, u, v);
        quicksort(p, x - 1, v);
        quicksort(x + 1, u, v);
    }
}
void radixsort(vector<int> & v, int low, int high)
{
    auto start1 = high_resolution_clock::now();
    queue<int> L[256];
    int maxi = v[low];
    for(int i = low + 1; i <= high; i++)
        if(v[i] > maxi)
            maxi = v[i];
    int putere = 0;
    int STOP = 1 << 56;
    if(maxi >= STOP)
        putere = 64;
    else
        while(maxi >= 1 << putere)
            putere += 8;
    for(int k = 0; k < putere; k+=8)
    {
        for(int i = low; i <= high; i++)
            L[(v[i] >> k) & 255].push(v[i]);
        int t = low;
        for(int i = 0; i < 256; i++)
            while(!L[i].empty())
            {
                v[t] = L[i].front();
                t++;
                L[i].pop();
            }
    }
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    if(test(v, high) == true)
        cout << "RadixSort: CORECT- Timpul de rulare: "<<duration1.count()/1000000.00000000000000 <<" secunde"<< endl;
    else
        cout << "radixsort nu a sortat bine"<<endl;
}

int mediana(int left, int right, vector <int> &v)
{
    int x,y,z,i,j;
    x = v[left];
    y = v[(right-left)/2+left];
    z = v[right-1];
    i = left-1;
    j = right;

    if(y>x && y<z || y>z && y<x)
        x=y;
    else if(z>x && z<y || z>y && z<x)
        x=z;

    while(1){
        do {
            j--;
        }while(v[j]>x);

        do {
            i++;
        }while(v[i]<x);

        if (i<j) swap(v[i],v[j]);
        else return j+1;


    }

}
void quicksort3(int p, int u, vector<int> &v)
{
    int pv;
    if (u-p>=2)
    {
        pv = mediana(p,u,v);

        quicksort3(p,pv,v);
        quicksort3(pv,u,v);


    }}

void shellsort( vector <int> &v, int n)
{  int gap, t;
    for(int gap = n/2; gap > 0; gap /= 2)
    {
        for(int i = gap; i < n; i +=1)
        {int t = v[i];
         int j;
         for(j = i; j >= gap && v[j - gap] > t; j -= gap)
            v[j]= v[j - gap];
        }
    }
}

int main()
{
    ifstream f("fisier.in");
    int N,n,maxx, i,j;
    vector <int> v;
    vector <int> c;
    f>>N;

    for(i = 0; i < N; i++)
    {
        f>>n>>maxx;
        cout<< "TEST "<< i+1 <<" :n = "<< n<< " maxx = "<<maxx<<" "<<endl;
        random(n, maxx, v);

        if(n > 100000000)
            cout<<"NativeSort: Nu exista suficienta memorie pentru a aloca vectorul";
                else
            { c.clear();
                for (int j = 0; j < n; j++)
                    c.push_back(v[j]);

                auto start = high_resolution_clock::now();
                sort(c.begin(), c.end());
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                if(test(c, n) == true)
                    cout << "NativeSort: CORECT- Timpul de rulare: " << duration.count() / 1000000.00000000000000 << " secunde" << endl;
                else
                    cout << "NativeSort nu a sortat bine"<<endl;
            }

        if(n > 10000)
            cout<<"BubbleSort: Nu exista suficienta memorie pentru a aloca vectorul"<<endl;
        else
        { c.clear();
            for ( j = 0; j < n; j++)
                c.push_back(v[j]);
            bubblesort(n, c);
        }



        if(n > 100000000)
            cout<<"CountSort: Nu exista suficienta memorie pentru a aloca vectorul"<<endl;
        else
        { c.clear();
            for (int j = 0; j < n; j++)
                c.push_back(v[j]);
            countsort(n, v);
        }



        if(n > 10000000)
            cout<<"MergeSort: Nu exista suficienta memorie pentru a aloca vectorul"<<endl;
        else
        { c.clear();
            for (int j = 0; j < n; j++)
                c.push_back(v[j]);
            auto start1 = high_resolution_clock::now();
            mergeSort(c, 0, n-1);
            auto stop1 = high_resolution_clock::now();
            auto duration1 = duration_cast<microseconds>(stop1 - start1);
            if(test(c,n)==true)
            cout<<"MergeSort: CORECT- Timpul de rulare: "<<duration1.count()/1000000.00000000000000 <<" secunde"<< endl;
            else cout<<"MergeSort nu a sortat bine\n";

        }



        if(n > 50000)
            cout<<"QuickSort: Timpul de rulare este prea mare"<<endl;
        else
        { c.clear();
            for (int j = 0; j < n; j++)
                c.push_back(v[j]);
            auto start2 = high_resolution_clock::now();
            quicksort(0, n-1, c);
            auto stop2 = high_resolution_clock::now();
            auto duration2 = duration_cast<microseconds>(stop2 - start2);
            if(test(c,n)==true)
            cout<<"QuickSort: CORECT- Timpul de rulare: "<<duration2.count()/1000000.00000000000000 <<" secunde"<< endl;
            else cout<<"QuickSort nu a sortat bine";
        }
        if(n > 100000000)
            cout<<"QuickSort cu mediana: Nu exista suficienta memorie pentru a aloca vectorul"<<endl;
        else
        { c.clear();
            for (int j = 0; j < n; j++)
                c.push_back(v[j]);
            auto start5 = high_resolution_clock::now();
            quicksort3(0, n, c);
            auto stop5 = high_resolution_clock::now();
            auto duration5 = duration_cast<microseconds>(stop5 - start5);
            if(test(c,n)==true)
            cout<<"QuickSort cu mediana: CORECT- Timpul de rulare: "<<duration5.count()/1000000.00000000000000 <<" secunde"<< endl;
            else cout<<"Quicksort cu mediana nu a sortat bine";
        }



        if(n > 100000000)
            cout<<"RadixSort: Nu exista suficienta memorie pentru a aloca vectorul"<<endl;
        else
        { c.clear();
            for (int j = 0; j < n; j++)
                c.push_back(v[j]);
            radixsort(c, 0, n-1);
        }

        if(n > 100000000)
            cout<<"ShellSort: Nu exista suficienta memorie pentru a aloca vectorul"<<endl;
        else
        { c.clear();
            for (int j = 0; j < n; j++)
                c.push_back(v[j]);
            auto start6 = high_resolution_clock::now();
            shellsort(c, n);
            auto stop6 = high_resolution_clock::now();
            auto duration6 = duration_cast<microseconds>(stop6 - start6);
            if(test(c,n)==true)
            cout<<"ShellSort: CORECT- Timpul de rulare: "<<duration6.count()/1000000.00000000000000 <<" secunde"<< endl;
            else cout<<"ShellSort nu a sortat bine";
        }

        c.clear();
        v.clear();
    }

    return 0;
}
