#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX_SIZE 1000005
#include "nodeMap.cpp"

int main()
{
    setSieve();
    int n;
    cin>>n;
    string input_arr[n];
    for(int i=0;i<n;i++)
    {
        string a="";
        for(int j=0;j<7;j++)
        {
            int r=(rand()%(90-65))+65;
            char c=(char)(r);
            int r2=(rand()%(122-97))+97;
            char c2=(char)(r2);
           if(rand()%2)
                a+=c;
            else
                a+=c2;
        }
        input_arr[i]=a;
    }

    double before_del1[6];
    double after_del1[6];

    double before_del2[6];
    double after_del2[6];

    double before_del3[6];
    double after_del3[6];

    double before_del4[6];
    double after_del4[6];

    ll before_prb2[6]={0,0};
    ll after_prb2[6]={0,0};

    ll before_prb3[6]={0,0};
    ll after_prb3[6]={0,0};

    ll before_prb4[6]={0,0};
    ll after_prb4[6]={0,0};

    double load[6]={0.4,0.5,0.6,0.7,0.8,0.9};

    chaining arr[6]={chaining(n,0.4),chaining(n,0.5),chaining(n,0.6),chaining(n,0.7),chaining(n,0.8),chaining(n,0.9)};

    cout<<"FOR SEPARATE CHAINING HASH COLLISION RESOLUTION ---------->\n"<<endl;
    for(int i=0;i<6;i++)
    {
        int allowed_insert_cnt=(int)(load[i]*n);
        for(int j=0;j<allowed_insert_cnt;j++)
        {
            arr[i].insertHash(input_arr[j],j+1);
        }
    }
    for(int i=0;i<6;i++)
    {
        cout<<"For Load Factor "<<load[i]<<", ";
        int allowed_insert_cnt=(int)(load[i]*n);
        int search_cnt=(int)(0.1*allowed_insert_cnt);

        chrono::steady_clock::time_point chaining_search_begin = chrono::steady_clock::now();
        for(int j=0;j<search_cnt;j++)
        {
            int hereIdx = arr[i].searchHash(input_arr[((rand())%allowed_insert_cnt)]);
        }
        chrono::steady_clock::time_point chaining_search_end = chrono::steady_clock::now();
        before_del1[i]=chrono::duration_cast<chrono::nanoseconds>(chaining_search_end-chaining_search_begin).count();
        before_del1[i]=before_del1[i]/(double)search_cnt;
        cout<<"before delete avg time "<<before_del1[i]<<" nanoseconds and ";

        for(int j=0;j<search_cnt;j++)
        {
            arr[i].deleteHash(input_arr[((rand())%allowed_insert_cnt)]);
        }

        chrono::steady_clock::time_point chaining_search_begin2 = chrono::steady_clock::now();
        for(int j=0;j<search_cnt;j++)
        {
            int here = arr[i].searchHash(input_arr[((rand())%allowed_insert_cnt)]);
        }
        chrono::steady_clock::time_point chaining_search_end2 = chrono::steady_clock::now();
        after_del1[i]=chrono::duration_cast<chrono::nanoseconds>(chaining_search_end2-chaining_search_begin2).count();
        after_del1[i]=after_del1[i]/(double)search_cnt;
        cout<<"after delete avg time "<<after_del1[i]<<" nanoseconds\n"<<endl;

    }

    linearHash arr2[6]={linearHash(n,0.4),linearHash(n,0.5),linearHash(n,0.6),linearHash(n,0.7),linearHash(n,0.8),linearHash(n,0.9)};
    cout<<"FOR LINEAR PROBING HASH COLLISION RESOLUTION ---------->\n"<<endl;
    for(int i=0;i<6;i++)
    {
        int allowed_insert_cnt=(int)(load[i]*n);
        for(int j=0;j<allowed_insert_cnt;j++)
        {
            arr2[i].insertHash(input_arr[j],j+1);
        }
    }
    for(int i=0;i<6;i++)
    {
        cout<<"For Load Factor "<<load[i]<<", ";
        int allowed_insert_cnt=(int)(load[i]*n);
        int search_cnt=(int)(0.1*allowed_insert_cnt);

        chrono::steady_clock::time_point chaining_search_begin = chrono::steady_clock::now();
        for(int j=0;j<search_cnt;j++)
        {
            int hereIdx = arr2[i].searchHash(input_arr[((rand())%allowed_insert_cnt)]);
            before_prb2[i]+=(arr2[i].getProbe());
        }
        chrono::steady_clock::time_point chaining_search_end = chrono::steady_clock::now();
        before_del2[i]=chrono::duration_cast<chrono::nanoseconds>(chaining_search_end-chaining_search_begin).count();
        before_del2[i]=before_del2[i]/(double)search_cnt;
        before_prb2[i]/=search_cnt;
        cout<<"before delete avg time "<<before_del2[i]<<" nanoseconds and probe cnt "<<before_prb2[i]<<", ";

        for(int j=0;j<search_cnt;j++)
        {
            arr2[i].deleteHash(input_arr[((rand())%allowed_insert_cnt)]);
        }

        chrono::steady_clock::time_point chaining_search_begin2 = chrono::steady_clock::now();
        for(int j=0;j<search_cnt;j++)
        {
            int here = arr2[i].searchHash(input_arr[((rand())%allowed_insert_cnt)]);
            after_prb2[i]+=(arr2[i].getProbe());
        }
        chrono::steady_clock::time_point chaining_search_end2 = chrono::steady_clock::now();
        after_del2[i]=chrono::duration_cast<chrono::nanoseconds>(chaining_search_end2-chaining_search_begin2).count();
        after_del2[i]=after_del2[i]/(double)search_cnt;
        after_prb2[i]=after_prb2[i]/search_cnt;
        cout<<"after delete avg time "<<after_del2[i]<<" nanoseconds and probe cnt "<<after_prb2[i]<<"\n"<<endl;
    }


    quadHash arr3[6]={quadHash(n,0.4),quadHash(n,0.5),quadHash(n,0.6),quadHash(n,0.7),quadHash(n,0.8),quadHash(n,0.9)};
    cout<<"FOR QUADRATIC PROBING HASH COLLISION RESOLUTION ---------->\n"<<endl;
    for(int i=0;i<6;i++)
    {
        int allowed_insert_cnt=(int)(load[i]*n);
        for(int j=0;j<allowed_insert_cnt;j++)
        {
            arr3[i].insertHash(input_arr[j],j+1);
        }
    }
    for(int i=0;i<6;i++)
    {
        cout<<"For Load Factor "<<load[i]<<", ";
        int allowed_insert_cnt=(int)(load[i]*n);
        int search_cnt=(int)(0.1*allowed_insert_cnt);

        chrono::steady_clock::time_point chaining_search_begin = chrono::steady_clock::now();
        for(int j=0;j<search_cnt;j++)
        {
            int hereIdx = arr3[i].searchHash(input_arr[((rand())%allowed_insert_cnt)]);
            before_prb3[i]+=(arr3[i].getProbe());
        }
        chrono::steady_clock::time_point chaining_search_end = chrono::steady_clock::now();
        before_del3[i]=chrono::duration_cast<chrono::nanoseconds>(chaining_search_end-chaining_search_begin).count();
        before_del3[i]=before_del3[i]/(double)search_cnt;
        before_prb3[i]/=search_cnt;
        cout<<"before delete avg time "<<before_del3[i]<<" nanoseconds and probe cnt "<<before_prb3[i]<<", ";

        for(int j=0;j<search_cnt;j++)
        {
            arr3[i].deleteHash(input_arr[((rand())%allowed_insert_cnt)]);
        }

        chrono::steady_clock::time_point chaining_search_begin2 = chrono::steady_clock::now();
        for(int j=0;j<search_cnt;j++)
        {
            int here = arr3[i].searchHash(input_arr[((rand())%allowed_insert_cnt)]);
            after_prb3[i]+=(arr3[i].getProbe());
        }
        chrono::steady_clock::time_point chaining_search_end2 = chrono::steady_clock::now();
        after_del3[i]=chrono::duration_cast<chrono::nanoseconds>(chaining_search_end2-chaining_search_begin2).count();
        after_del3[i]=after_del3[i]/(double)search_cnt;
        after_prb3[i]/=search_cnt;
        cout<<"after delete avg time "<<after_del3[i]<<" nanoseconds and probe cnt "<<after_prb3[i]<<"\n"<<endl;

    }

    doubleHash arr4[6]={doubleHash(n,0.4),doubleHash(n,0.5),doubleHash(n,0.6),doubleHash(n,0.7),doubleHash(n,0.8),doubleHash(n,0.9)};
    cout<<"FOR DOUBLE HASH COLLISION RESOLUTION ---------->\n"<<endl;
    for(int i=0;i<6;i++)
    {
        int allowed_insert_cnt=(int)(load[i]*n);
        for(int j=0;j<allowed_insert_cnt;j++)
        {
            arr4[i].insertHash(input_arr[j],j+1);
        }
    }
    for(int i=0;i<6;i++)
    {
        cout<<"For Load Factor "<<load[i]<<", ";
        int allowed_insert_cnt=(int)(load[i]*n);
        int search_cnt=(int)(0.1*allowed_insert_cnt);

        chrono::steady_clock::time_point chaining_search_begin = chrono::steady_clock::now();
        for(int j=0;j<search_cnt;j++)
        {
            int hereIdx = arr4[i].searchHash(input_arr[((rand())%allowed_insert_cnt)]);
            before_prb4[i]+=(arr4[i].getProbe());
        }
        chrono::steady_clock::time_point chaining_search_end = chrono::steady_clock::now();
        before_del4[i]=chrono::duration_cast<chrono::nanoseconds>(chaining_search_end-chaining_search_begin).count();
        before_del4[i]=before_del4[i]/(double)search_cnt;
        before_prb4[i]/=search_cnt;
        cout<<"before delete avg time "<<before_del4[i]<<" nanoseconds and probe cnt "<<before_prb4[i]<<", ";

        for(int j=0;j<search_cnt;j++)
        {
            arr4[i].deleteHash(input_arr[((rand())%allowed_insert_cnt)]);
        }

        chrono::steady_clock::time_point chaining_search_begin2 = chrono::steady_clock::now();
        for(int j=0;j<search_cnt;j++)
        {
            int here = arr4[i].searchHash(input_arr[((rand())%allowed_insert_cnt)]);
            after_prb4[i]+=(arr4[i].getProbe());
        }
        chrono::steady_clock::time_point chaining_search_end2 = chrono::steady_clock::now();
        after_del4[i]=chrono::duration_cast<chrono::nanoseconds>(chaining_search_end2-chaining_search_begin2).count();
        after_del4[i]=after_del4[i]/(double)search_cnt;
        after_prb4[i]/=search_cnt;
        cout<<"after delete avg time "<<after_del4[i]<<" nanoseconds and probe cnt "<<after_prb4[i]<<"\n"<<endl;

    }

    for(int i=0;i<6;i++)
    {
        cout<<"FOR LOAD FACTOR "<<load[i]<<" -------->"<<endl;
        cout<<"Separate Chaining: Before Deletion (avg search time, avg probes) = ("<<
        before_del1[i]<<", N/A and After Deletion (avg search timr, avg probes) = ("
        <<after_del1[i]<<", N/A)"<<endl;
        cout<<"Linear Probing: Before Deletion (avg search time, avg probes) = ("<<
        before_del2[i]<<", "<<before_prb2[i]<<") and After Deletion (avg search timr, avg probes) = ("
        <<after_del2[i]<<", "<<after_prb2[i]<<")"<<endl;
        cout<<"Quad Probing: Before Deletion (avg search time, avg probes) = ("<<
        before_del3[i]<<", "<<before_prb3[i]<<") and After Deletion (avg search timr, avg probes) = ("
        <<after_del3[i]<<", "<<after_prb3[i]<<")"<<endl;
        cout<<"Double Hashing: Before Deletion (avg search time, avg probes) = ("<<
        before_del4[i]<<", "<<before_prb4[i]<<") and After Deletion (avg search timr, avg probes) = ("
        <<after_del4[i]<<", "<<after_prb4[i]<<")"<<endl;
    }

    return 0;
}
