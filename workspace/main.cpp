#include <iostream>
#include "data.hpp"

using namespace std;


int main()
{
    //Data Insert
    cout<< "Initialize: Data Insertion" << endl << endl;

    UserData *UserSet[100];
    
    for( int i =0 ; i< 100; i++){
        
        UserSet[i] = randomGenerator(i);
        cout << "User ID: " << UserSet[i]->id << endl;
        cout << "User MBTI: " << UserSet[i]->mbti << endl;
        cout << "User Interests: "; 
        for(int j = 0; j<UserSet[i]->interests.size(); j++){
            cout << UserSet[i]->interests[j] << "/";
        }
    }
    // 알고리즘 별 결과 확인 
    // 1. MBTI별로 궁합도 확인하여 정렬 후 3, 4점인 사람들만 데이터 추출하여 새로운 임시 배열에 저장.
    // 2. 1번에서 만든 데이터들 중에 관심사가 같은 사람들 확인하여 결과 출력.
    // 3. ? 

    
    // Heap Sort
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