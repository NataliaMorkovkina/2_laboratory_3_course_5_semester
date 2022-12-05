#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <chrono>

using namespace std;

int snail_n;



void divide_and_sort(double* array, int start, int mid, int end)
{


    if (start < end)
    {
        int mid = start + (end - start) / 2;
        int end = mid;
        int start = mid + 1;

        return divide_and_sort(array, start, mid, end);
    }

    int n1 = mid - start + 1;
    int n2 = end - mid;

    double* lArray = new double[n1];
    double* rArray = new double[n2];

    for (int i = 0; i < n1; i++)
        rArray[i] = array[start + i];

    for (int j = 0; j < n2; j++)
        lArray[j] = array[mid + 1 + j];


    int i = 0, j = 0, s = start;

    while (i < n1 && j < n2)
    {
        if (rArray[i] <= lArray[j])
        {
            array[s] = lArray[i];
            i++;
        }
        else
        {
            array[s] = rArray[j];
            j++;
        }
        s++;
    }

    while (i < n1)
    {
        array[s] = lArray[i];
        i++;
        s++;
    }

    while (j < n2)
    {
        array[s] = rArray[j];
        j++;
        s++;
    }

    delete[] lArray;
    delete[] rArray;


   
}



struct Snail
{

    double* way = new double[snail_n - 1];
    bool confusion = false;
    void is_this_confusion()
    {

        divide_and_sort(way, 0, 0, snail_n);
        if (way[0] == way[1])
            this->confusion = true;

    }
};



double wayLength(double x1, double y1, double x2, double y2)
{
    return (pow(x1 - x2, 2) + pow(y1 - y2, 2));
}



int main()
{
    cout << "\n enter the number of snails \n";
    cin >> snail_n;
    vector<pair<double, double>> ys(snail_n);
    cout << "\n enter the coordinates of the snails \n";
    for (auto& i : ys)
    {
        cin >> i.first >> i.second;
    }

    if (snail_n == 1)
    {
        cout << "\n this snail will die alone :( \n";
        return 0;
    }

    auto start_time = chrono::high_resolution_clock::now();

    Snail* snails = new Snail[snail_n];
    double shortest_way = 1000000000;
    double temp = 0;
    int ways = 0;
    for (int i = 0; i < snail_n; i++)
    {
        for (int j = 0; j < snail_n; j++)
        {
            if (i != j)
            {
                temp = wayLength(ys[i].first, ys[i].second, ys[j].first, ys[j].second);
                snails[i].way[ways] = temp;
                if (temp < shortest_way)
                    shortest_way = temp;
                ways++;
            }
        }
        snails[i].is_this_confusion();
        ways = 0;
    }

    int k = 0;
    for (int i = 0; i < snail_n; i++)
    {
        if (snails[i].confusion)
        {
            cout << "Snail " << i + 1 << " confused \n";
            k++;
            break;
        }

    }

    if (k != snail_n)
        cout << " time = " << shortest_way / 2.f * 1000000.f << " sec \n";

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end_time - start_time;
    cout << "\nlead time - " << duration.count() * 100 << endl;

    return 0;

}
