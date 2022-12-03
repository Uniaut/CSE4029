#include <iostream>
#include "data.hpp"
#include <algorithm>

using namespace std;

// vector is sorted. use intersection algorithm
int interest_fitness(vector <Interest> interest1, vector <Interest> interest2)
{
    int fitness = 0;
    int i = 0, j = 0;
    while (i < interest1.size() && j < interest2.size())
    {
        if (interest1[i] < interest2[j])
            i++;
        else if (interest1[i] > interest2[j])
            j++;
        else
        {
            fitness++;
            i++;
            j++;
        }
    }
    return fitness;
}

int combination_fitness(UserData *a, UserData *b)
{
    int mbti_fit = MBTICombination[a->mbti][b->mbti];  
    int interest_fit =0;
    int result =0;
    interest_fit = interest_fitness(a->interests, b->interests);
    // mbti fit 0 ~ 4 / interet_fit 0 ~ 10 5 : 2 5 : 1 10 :2 
    result = 8 * mbti_fit + 2 * interest_fit; 
    // cout << "mbti_fit : " << mbti_fit << " interest_fit : " << interest_fit << " result : " << result << endl;
    return result;
}

// heap sort
// input: array of UserData
// output: sorted array of UserData by fitness
UserData** heapsortAsFitness(UserData **unsorted, int index_query, int size)
{
    UserData **sorted = new UserData*[size];
    UserData *center = unsorted[index_query];
    for (int i = 0; i < size; i++)
    {
        sorted[i] = unsorted[i];
    }

    for (int i = 1; i < size; i++)
    {
        int child = i;
        while (child > 0)
        {
            int parent = (child - 1) / 2;
            if (combination_fitness(center, sorted[parent]) < combination_fitness(center, sorted[child]))
            {
                UserData *temp = sorted[parent];
                sorted[parent] = sorted[child];
                sorted[child] = temp;
            }
            child = parent;
        }
    }

    for (int i = size - 1; i >= 0; i--)
    {
        UserData *temp = sorted[0];
        sorted[0] = sorted[i];
        sorted[i] = temp;
        int parent = 0;
        int child = 1;
        while (child < i)
        {
            child = 2 * parent + 1;
            if (child < i - 1 && combination_fitness(center, sorted[child]) < combination_fitness(center, sorted[child + 1]))
            {
                child++;
            }
            if (child < i && combination_fitness(center, sorted[parent]) < combination_fitness(center, sorted[child]))
            {
                UserData *temp = sorted[parent];
                sorted[parent] = sorted[child];
                sorted[child] = temp;
            }
            parent = child;
        }
    }
    
    return sorted;
}


// merge sort
// input: array of UserData
// output: sorted array of UserData by fitness
UserData** mergesortAsFitness(UserData **unsorted, int index_query, int size)
{
    UserData **sorted = new UserData*[size];
    UserData *center = unsorted[index_query];
    for (int i = 0; i < size; i++)
    {
        sorted[i] = unsorted[i];
    }

    for (int i = 1; i < size; i *= 2)
    {
        for (int j = 0; j < size - i; j += i * 2)
        {
            int left = j;
            int right = j + i;
            int end = j + i * 2;
            if (end > size)
                end = size;
            UserData **temp = new UserData*[end - left];
            int index = 0;
            while (left < j + i && right < end)
            {
                if (combination_fitness(center, sorted[left]) > combination_fitness(center, sorted[right]))
                {
                    temp[index] = sorted[left];
                    left++;
                }
                else
                {
                    temp[index] = sorted[right];
                    right++;
                }
                index++;
            }
            while (left < j + i)
            {
                temp[index] = sorted[left];
                left++;
                index++;
            }
            while (right < end)
            {
                temp[index] = sorted[right];
                right++;
                index++;
            }
            for (int k = j; k < end; k++)
            {
                sorted[k] = temp[k - j];
            }
            delete[] temp;
        }
    }
    return sorted;
}

// quick sort
// input: array of UserData
// output: sorted array of UserData by fitness
void _quicksortAsFitness(UserData **unsorted, UserData *center, int left, int right)
{
    int i = left;
    int j = right;
    int pivot = combination_fitness(center, unsorted[(left + right) / 2]);
    while (i <= j)
    {
        while (combination_fitness(center, unsorted[i]) > pivot)
            i++;
        while (combination_fitness(center, unsorted[j]) < pivot)
            j--;
        if (i <= j)
        {
            UserData *temp = unsorted[i];
            unsorted[i] = unsorted[j];
            unsorted[j] = temp;
            i++;
            j--;
        }
    }
    if (left < j)
        _quicksortAsFitness(unsorted, center, left, j);
    if (i < right)
        _quicksortAsFitness(unsorted, center, i, right);
}

UserData** quicksortAsFitness(UserData **unsorted, int index_query, int size)
{
    UserData **sorted = new UserData*[size];
    UserData *center = unsorted[index_query];
    for (int i = 0; i < size; i++)
    {
        sorted[i] = unsorted[i];
    }
    _quicksortAsFitness(sorted, center, 0, size - 1);
    return sorted;
}


int main()
{
    //Data Insert
    cout<< "Initialize: Data Insertion" << endl << endl;

    UserData *UserSet[100];
    
    for(int i = 0 ; i< 100; i++){
        
        UserSet[i] = randomGenerator(i);
        cout << "User ID: " << UserSet[i]->id << endl;
        cout << "User MBTI: " << UserSet[i]->mbti << endl;
        cout << "User Interests: "; 
        for(int j = 0; j<UserSet[i]->interests.size(); j++)
        {
            cout << UserSet[i]->interests[j] << "/";
        }
        cout << endl;
    }
    // 알고리즘 별 결과 확인 
    // 1. MBTI별로 궁합도 확인하여 정렬 후 3, 4점인 사람들만 데이터 추출하여 새로운 임시 배열에 저장.
    // 2. 1번에서 만든 데이터들 중에 관심사가 같은 사람들 확인하여 결과 출력.
    // 3. ????????????????????????????????????????????????????

    cout << "Algorithm 1: Merge Sort" << endl;
    auto merge_result = mergesortAsFitness(UserSet, 3, 100);
    for(int i = 0 ; i< 100; i++)
    {
        cout << "User ID: " << merge_result[i]->id << '\t';
        cout << "Fitness: " << combination_fitness(merge_result[i], UserSet[3]) << endl;
    }

    cout << "Algorithm 2: Quick Sort" << endl;
    auto quick_result = quicksortAsFitness(UserSet, 3, 100);
    for(int i = 0 ; i< 100; i++)
    {
        cout << "User ID: " << quick_result[i]->id << '\t';
        cout << "Fitness: " << combination_fitness(quick_result[i], UserSet[3]) << endl;
    }

    cout << "Algorithm 3: Heap Sort" << endl;
    auto heap_result = heapsortAsFitness(UserSet, 3, 100);
    for(int i = 0 ; i< 100; i++)
    {
        cout << "User ID: " << quick_result[i]->id << '\t';
        cout << "Fitness: " << combination_fitness(quick_result[i], UserSet[3]) << endl;
    }
    //  //Heap Sort
	// clock_t start, end;
	// double result;
    // start = clock();
    // cout <<"Algorithm: Heap Sort"<<endl;
	// end = clock();
	// result = double(end - start);
	// cout << "정렬에 소요된 시간: " << end << "-" << start << "=" << result << "ms" << endl << endl;


    // // Merge Sort
    // start = clock();
    // cout <<"Algorithm: Merge Sort"<<endl;
    // end = clock();
	// result = double(end - start);
	// cout << "정렬에 소요된 시간: " << end << "-" << start << "=" << result << "ms" << endl << endl;


    // // Quick Sort
    // start = clock();
    // cout <<"Algorithm: Quick Sort"<<endl;
    // end = clock();
	// result = double(end - start);
	// cout << "정렬에 소요된 시간: " << end << "-" << start << "=" << result << "ms" << endl << endl;


    // Data result 

	return 0;
}