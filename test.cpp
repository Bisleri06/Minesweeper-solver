#include<iostream>
#include<vector>
#include<utility>
using namespace std;

/*
instructions for input matrix cell
-1 for square not opened
0-side: number of mines around
example input (6x6):
 -1 -1 -1 -1 3 -1
 2 3 3 2 -1 -1
 0 0 1 -1 4 -1
 0 0 2 -1 -1 -1
 1 1 2 -1 4 -1
 -1 -1 1 1 -1 -1
*/


vector<vector<float>> probabilities;
vector<vector<int>> matrix;
int side;


//function to check bounds
bool check_valid(int i,int j){
    if(i>=0 and i<side and j>=0 and j<side)
        return true;
    return false;
}


//find probability of unopened neighbouring cells around a cell
void find_prob(int i,int j)
{

    if(matrix[i][j]==0 or matrix[i][j]==-1 or probabilities[i][j]==1)
        return;

    vector<pair<int,int>> edges={       //neighbouring coordinates
        {0,1},
        {1,0},
        {1,1},
        {-1,-1},
        {0,-1},
        {-1,0},
        {1,-1},
        {-1,1}
    };

    int mines=0;
    int unopened=0;

    //counting number of mines and unopened squares around a cell
    for(auto edge:edges)    
    {
        if(!check_valid(i+get<0>(edge),j+get<1>(edge)))
            continue;

        if(matrix[i+get<0>(edge)][j+get<1>(edge)]==-1)
            unopened++;

        else if(probabilities[i+get<0>(edge)][j+get<1>(edge)]==1)
            mines++;
    }


    float prob=float(matrix[i][j]-mines)/float(unopened);
    //find the probability of potential mines present in unopened cells
    //0 is no mines and 1 is mine present


    //assigning probability to neighbouring unopened cells
    for(auto edge:edges)
    {
        if(!check_valid(i+get<0>(edge),j+get<1>(edge)))
            continue;
        
        if(matrix[i+get<0>(edge)][j+get<1>(edge)]!=-1)  //check if unopened
            continue;

        if(probabilities[i+get<0>(edge)][j+get<1>(edge)]==100)  //directly assign if cell unvisited
            probabilities[i+get<0>(edge)][j+get<1>(edge)]=prob;

        //replace probability with 0 if unopened cells surrounding a cell are safe
        else if(probabilities[i+get<0>(edge)][j+get<1>(edge)]<1 and probabilities[i+get<0>(edge)][j+get<1>(edge)]>0 and prob==0)
            probabilities[i+get<0>(edge)][j+get<1>(edge)]=prob;
        
        //find out average probability in case the cell already has a probability present
        else if(probabilities[i+get<0>(edge)][j+get<1>(edge)]<1 and probabilities[i+get<0>(edge)][j+get<1>(edge)]>0)
            probabilities[i+get<0>(edge)][j+get<1>(edge)]=(probabilities[i+get<0>(edge)][j+get<1>(edge)]+prob)/2;
    }
}



void solve(){

    for(int i=0;i<side;i++)     //find probabilities for all cells
    {
        for(int j=0;j<side;j++){
            find_prob(i,j);
        }
    }

    pair<int,int> min_prob=make_pair(0,0);
    float min_num=100;
    float avg_prob=0;
    

    //this block finds the best next move by finding the cell with lowest probability of a mine
    cout<<endl;
    for(int i=0;i<side;i++)
    {
        for(int j=0;j<side;j++){
            cout<<probabilities[i][j]<<" ";

            if(probabilities[i][j]==100)
                continue;

            if(avg_prob==0)
                avg_prob=probabilities[i][j];
            else
                avg_prob=(avg_prob+probabilities[i][j])/2;

            if(min_num>probabilities[i][j]){
                min_num=probabilities[i][j];
                min_prob=make_pair(i,j);
            }
        }
        cout<<endl;
    }
    cout<<endl;


    //risky but finds another unvisited border cell if existing cells are becoming risky, probability of a mine >= 48%
    if(min_num>=0.48)
    {
        for(int i=0;i<side;i++)
        {
            for(int j=0;j<side;j++){
                if(probabilities[i][j]==100 && matrix[i][j]==-1 && (i==0 || j==0 || i==side-1 || j==side-1))
                {
                    min_num=100;
                    min_prob=make_pair(i,j);
                }
            }
        }
    }

    cout<<get<0>(min_prob)+1<<" "<<get<1>(min_prob)+1<<endl; //counting from 1, prints cell location for next move
    cout<<"Min: "<<min_num<<endl;
    cout<<"AVG: "<<avg_prob<<endl;
    probabilities[get<0>(min_prob)][get<1>(min_prob)]=100;  //reset probability of the cell
}



int main(){

    cout<<"Enter maze side length: ";
    cin>>side;

    probabilities.resize(side);
    matrix.resize(side);
    for(int i=0;i<side;i++)
    {
        probabilities[i].resize(side,100);     //default value
        matrix[i].resize(side,0);
    }

    while(1)                    //take matrix input every iteration and solve for each step
    {
        for(int i=0;i<side;i++)
        {
            for(int j=0;j<side;j++){
                int c;
                cin>>c;
                matrix[i][j]=c;

                if(c!=-1)
                    probabilities[i][j]=100;
            }
        }
        solve();
    }

    

}