#include <string>
#include <vector>
#include <random>

#include <cstdlib>

using namespace std;

enum MBTI
{
    INFP,
    ENFP,
    INFJ,
    ENFJ,
    INTJ,
    ENTJ,
    INTP,
    ENTP,
    ISFP,
    ESFP,
    ISTP,
    ESTP,
    ISFJ,
    ESFJ,
    ISTJ,
    ESTJ
};

enum Interest
{
    Game,
    Movie,
    Exercise,
    Book,
    Music,
    Cooking,
    Travel,
    Coding,
    Sleeping,
    Drama
};

int MBTICombination[16][16] = 
{   //우리 궁합 다시 생각해봐요 = 0(빨강), 최악은 아니지만 좋지도 않음 = 1(노랑), 
//안맞는 것 맞는 것 반반! = 2(민트), 좋은 관계로 발전 가능 = 3(초록), 우리 궁합 천생영분 =4(파랑)
    {3, 3, 3, 4, 3, 4, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0},//INFP
    {3, 3, 4, 3, 4, 3 ,3, 3, 0, 0, 0, 0, 0, 0, 0, 0},//ENFP
    {3, 4, 3, 3, 3, 3, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0},//INFJ
    {4, 3, 3, 3, 3, 3, 3, 3, 4, 0, 0, 0, 0, 0, 0, 0},//ENFJ
    {3, 4, 3, 3, 3, 3, 3, 4, 2, 2, 2, 2, 1, 1, 1, 1},//INTJ
    {4, 3, 3, 3, 3, 3, 4, 3, 2, 2, 2, 2, 1, 1, 1, 1},//ENTJ
    {3, 3, 3, 3, 3, 4, 3, 3, 2, 2, 2, 2, 1, 1, 1, 4},//INTP
    {3, 3, 4, 3, 4, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1},//ENTP
    {0, 0, 0, 4, 2, 2, 2, 2, 1, 1, 1, 1, 2, 4, 2, 4},//ISFP
    {0, 0, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 4, 2, 4, 2},//ESFP
    {0, 0, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 2, 4, 2, 4},//ISTP
    {0, 0, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 4, 2, 2, 2},//ESTP
    {0, 0, 0, 0, 1, 1, 1, 1, 2, 4, 2, 4, 3, 3, 3, 3},//ISFJ
    {0, 0, 0, 0, 1, 1, 1, 1, 4, 2, 4, 2, 3, 3, 3, 3},//ESFJ
    {0, 0, 0, 0, 1, 1, 1, 1, 2, 4, 2, 2, 3, 3, 3, 3},//ISTJ
    {0, 0, 0, 0, 1, 1, 4, 1, 4, 2, 4, 2, 3, 3, 3, 3} //ESTJ
};

class UserData 
{
public:
    int id;
    MBTI mbti;
    vector<Interest> interests;
    UserData(int id, MBTI mbti, vector<Interest> interests): id(id), mbti(mbti)
    {
        for (int i = 0; i < interests.size(); i++)
        {
            this->interests.push_back(interests[i]);
        }
    }

};

UserData* randomGenerator(int id)
{
    MBTI mbti = MBTI(rand() % 16);
    vector<Interest> interests;
    for(int i = 0; i < 10; i++)
        if (rand() % 2 == 0)
            interests.push_back(Interest(i));

    return new UserData(id, mbti, interests);
}
