#include<bits/stdc++.h>
using namespace std;
#define N 100

int n;
int inputMatrix[N][N];
map<int,vector<vector<int>>>mp;

int calcBand(vector<int>vec, int pivot, int boundIdx)
{
    int ans=INT_MIN;
    int left_cnt=1;
    int right_cnt=1;
    // Looping through pivot-1 towards back to position 1
    for(int i=pivot-1;i>=1;i--)
    {
        if(vec[i]==5)
        {
            left_cnt=max(left_cnt,pivot-i+1); // here, left count is updated as far as non-zero achieved.
        }
    }

    int outSideNonZeroCnt=0; // This marks the total count outside the boundIndex towards the end of the row.
    // Corner case handling when column number is greater than the fixedRow, then boundIndex is left one cell behind.
    if(pivot>boundIdx)
    {
        for(int i=pivot;i<=n;i++)
        {
            if(vec[i]==5)
                outSideNonZeroCnt++;
        }
        int res = max(outSideNonZeroCnt, left_cnt); // In this corner case, we need not consider anything else.
        return res;
    }



    for(int i=boundIdx+1;i<=n;i++) // Looping through boundIndex towards the last end of the row.
    {
        if(vec[i]==5)
            outSideNonZeroCnt++;
    }

    if(outSideNonZeroCnt!=0)
    {
        right_cnt=(boundIdx-pivot+1)+outSideNonZeroCnt;// We have to shift all the non-zero numbers towards the boundIndex.
    }
    else // Just considering the bounding from boundIndex down to pivot position. Same as the left_count.
    {
        for(int i=pivot+1;i<=boundIdx;i++)
        {
            if(vec[i]==5)
            {
                right_cnt=max(right_cnt,(i-pivot+1));
            }
        }
    }
    return max(left_cnt, right_cnt);// Finally we got the bound for this row vector or column whatever say.
}

int main()
{
    char c;
    int band=0;
    int nonZero=0;
    int id=1;
    int cnt=1;
    int popCnt=0;
    int level=1;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>c;
            if(c=='x')
            {
                inputMatrix[i][j]=5;
                nonZero++; //
            }
            else
                inputMatrix[i][j]=0;
        }
    }



    int remCnt=0;
    int sumOfInitialNonZero=INT_MIN;
    for(int i=1;i<=n;i++) // Detecting the rows
    {
        remCnt=0;
        for(int j=1;j<=n;j++)
        {
            if(inputMatrix[i][j]==5)
                remCnt++;
        }
        sumOfInitialNonZero=max(sumOfInitialNonZero,remCnt);
    }
    for(int j=1;j<=n;j++) // Detecting the columns.
    {
        remCnt=0;
        for(int i=1;i<=n;i++)
        {
            if(inputMatrix[i][j]==5)
                remCnt++;
        }
        sumOfInitialNonZero=max(sumOfInitialNonZero,remCnt);
    }
        band=floor((sumOfInitialNonZero+1)/2);
        vector<vector<int>>vec;
        for(int i=1;i<=n;i++)
        {
            vector<int>v;
            for(int j=1;j<=n;j++)
            {
                v.push_back(inputMatrix[i][j]);
            }
            vec.push_back(v);
        }
        mp[id]=vec;

        int rowNow,colNow,fixedRow=0,fixedCol=0;

        priority_queue<pair<pair<int,int>,pair<int,int>>>pq; // Based on the Ordering of -> band, level, count, id of the matrix.


        pq.push(make_pair(make_pair((-1)*band,level),make_pair(cnt,id)));


        while(pq.empty()==false)
        {
            popCnt++;
            pair<pair<int,int>,pair<int,int>> pp=pq.top();
            pq.pop();


            int bandNow=(pp.first.first)*(-1);
            int idMat=pp.second.second;
            int cntNow=pp.second.first;
            int levelNow=pp.first.second;



            vector<vector<int>>vv=mp[idMat];
            int parent[N][N];

            for(int i=1;i<=n;i++)
            {
                for(int j=1;j<=n;j++)
                    parent[i][j]=vv[i-1][j-1];
            }

            if(levelNow==(2*n-1))
            {
                cout<<"The column number to fix is equal to n and so we are done."<<endl;
                cout<<"The final band is "<<bandNow<<endl;
                cout<<"Below the final matrix is shown:"<<endl;
                for(int i=1;i<=n;i++)
                {
                    for(int j=1;j<=n;j++)
                    {
                        if(parent[i][j]==5)
                            cout<<'x'<<" ";
                        else
                            cout<<'o'<<" ";
                    }
                    cout<<endl;
                }
                break;
            }


            if(levelNow%2==1)
            {
                colNow=(levelNow+1)/2; // the column number to fix now maintains the equation 2*levelNow-1.
                fixedCol=colNow-1;     // Previously fixed columns where we will not do any change, not even swap.
                fixedRow=fixedCol;     // Number of previously fixed col is equal to the fixed rows.

                for(int i=colNow;i<=n;i++) // We will swap present column to fix with all the front side columns.
                {
                    int temp[N][N]; // Matrix to store the condition after swapping.

                    // Just copy the last fixed column items.
                    for(int j=1;j<colNow;j++)
                    {
                        for(int k=1;k<=n;k++)
                        {
                            temp[k][j]=parent[k][j];
                        }
                    }

                    // swapping the column.
                    for(int k=1;k<=n;k++)
                    {
                        temp[k][colNow]=parent[k][i];
                    }

                    // remaining position of our columns.
                    int baki=colNow+1;
                    for(int j=colNow;j<=n;j++)
                    {
                        if(j==i)
                            continue; // We already placed those values.
                        else
                        {
                            for(int k=1;k<=n;k++)
                                temp[k][baki]=parent[k][j];
                            baki++;// Incrementing next column Position to fill.
                        }
                    }
                    // Now we have our temporary matrix.


                    /*cout<<"So our temporary matrix is "<<endl;
                    for(int i=1;i<=n;i++)
                    {
                        for(int j=1;j<=n;j++)
                        {
                            cout<<temp[i][j]<<" ";
                        }
                        cout<<endl;
                    }*/

                    vector<vector<int>>vec; // to store the matrix in vector format in map.
                    for(int i=1;i<=n;i++)
                    {
                        vector<int>v;
                        for(int j=1;j<=n;j++)
                        {
                            v.push_back(temp[i][j]);
                        }
                        vec.push_back(v);
                    }
                    id++;
                    cnt++;
                    mp[id]=vec;

                    // band calculation for the temporary matrix

                    int bandOfTemp=INT_MIN;

                    for(int i=1;i<=colNow;i++) // The total fixed column vectors in vector to send to calculation function.
                    {
                        vector<int>v;
                        v.push_back(-1);
                        for(int j=1;j<=n;j++)
                        {
                            v.push_back(temp[j][i]);
                        }
                        bandOfTemp=max(bandOfTemp, calcBand(v,i,fixedRow));
                    }

                    for(int i=1;i<=fixedRow;i++) // The total fixed row vectors in vector to send to calculation function.
                    {
                        vector<int>v;
                        v.push_back(-1);
                        for(int j=1;j<=n;j++)
                        {
                            v.push_back(temp[i][j]);
                        }
                        bandOfTemp=max(bandOfTemp, calcBand(v,i,colNow));
                    }

                    int badbakiCnt=0;
                    int sum=INT_MIN; // It will hold the value of the maximum values among all the bands within the unfixed portion.

                    for(int i=fixedRow+1;i<=n;i++)
                    {
                        badbakiCnt=0;
                        for(int j=colNow+1;j<=n;j++)
                        {
                            if(temp[i][j]==5)
                                badbakiCnt++;
                        }
                        sum=max(sum,badbakiCnt);
                    }
                    for(int j=colNow+1;j<=n;j++)
                    {
                        badbakiCnt=0;
                        for(int i=fixedRow+1;i<=n;i++)
                        {
                            if(temp[i][j]==5)
                                badbakiCnt++;
                        }
                        sum=max(sum,badbakiCnt);
                    }
                    bandOfTemp=max(bandOfTemp,(sum+1)/2);

                    // This marks the end of band calculation
                    //cout<<"pushing in priority queue "<<bandOfTemp<<endl;
                    pq.push(make_pair(make_pair((-1)*bandOfTemp,levelNow+1),make_pair(cnt,id)));
                }
            }
            else
            {
                rowNow=levelNow/2;  // the ROW number to fix now maintains the equation 2*levelNow.
                fixedCol=rowNow;    // Number of previously fixed col is equal to the fixed rows.
                fixedRow=rowNow-1; // Previously fixed rows where we will not do any change, not even swap.

                for(int i=rowNow;i<=n;i++)  // We will swap present rowNow to fix with all the front side rows.
                {
                    int temp[N][N];// Matrix to store the condition after swapping.

                    // Just copy the last fixed row items.
                    for(int j=1;j<rowNow;j++)
                    {
                        for(int k=1;k<=n;k++)
                        {
                            temp[j][k]=parent[j][k];
                        }
                    }

                    // swapping the row.
                    for(int k=1;k<=n;k++)
                    {
                        temp[rowNow][k]=parent[i][k];
                    }

                    // remaining position of our rows.
                    int baki=rowNow+1;
                    for(int j=rowNow;j<=n;j++)
                    {
                        if(j==i)
                            continue; // Already placed these items.
                        else
                        {
                            for(int k=1;k<=n;k++)
                                temp[baki][k]=parent[j][k];
                            baki++; // Incrementing next row position.
                        }
                    }
                    //Got the temporary matrix ready.


                    /*cout<<"So our temporary matrix is "<<endl;
                    for(int i=1;i<=n;i++)
                    {
                        for(int j=1;j<=n;j++)
                        {
                            cout<<temp[i][j]<<" ";
                        }
                        cout<<endl;
                    }*/

                    vector<vector<int>>vec; // to store in global map.
                    for(int i=1;i<=n;i++)
                    {
                        vector<int>v;
                        for(int j=1;j<=n;j++)
                        {
                            v.push_back(temp[i][j]);
                        }
                        vec.push_back(v);
                    }
                    id++;
                    cnt++;
                    mp[id]=vec;

                    // band calculation for the temporary matrix

                    int bandOfTemp=INT_MIN;

                    for(int i=1;i<=rowNow;i++)
                    {
                        vector<int>v;
                        v.push_back(-1);
                        for(int j=1;j<=n;j++)
                        {
                            v.push_back(temp[i][j]);
                        }
                        bandOfTemp=max(bandOfTemp, calcBand(v,i,fixedCol));
                    }

                    for(int i=1;i<=fixedCol;i++)
                    {
                        vector<int>v;
                        v.push_back(-1);
                        for(int j=1;j<=n;j++)
                        {
                            v.push_back(temp[j][i]);
                        }
                        bandOfTemp=max(bandOfTemp, calcBand(v,i,rowNow));
                    }

                    int badbakiCnt=0;
                    int sum=INT_MIN;
                    for(int i=fixedCol+1;i<=n;i++)
                    {
                        badbakiCnt=0;
                        for(int j=rowNow+1;j<=n;j++)
                        {
                            if(temp[j][i]==5)
                                badbakiCnt++;
                        }
                        sum=max(sum,badbakiCnt);
                    }
                    for(int j=rowNow+1;j<=n;j++)
                    {
                        badbakiCnt=0;
                        for(int i=fixedCol+1;i<=n;i++)
                        {
                            if(temp[j][i]==5)
                                badbakiCnt++;
                        }
                        sum=max(sum,badbakiCnt);
                    }
                    bandOfTemp=max(bandOfTemp,(sum+1)/2);

                    // This marks the end of band calculation
                    pq.push(make_pair(make_pair((-1)*bandOfTemp,levelNow+1),make_pair(cnt,id)));
                }
            }
        }
    return 0;
}

