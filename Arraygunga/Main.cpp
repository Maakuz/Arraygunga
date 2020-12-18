#include <iostream>
#include <Windows.h>
#include <chrono>
#include <ctime>
#include <vector>
#include <algorithm>



struct Combination
{
    std::vector<int> values;
    int sum;

    Combination(std::vector<int> values, int sum)
    {
        this->values = values;
        this->sum = sum;
    }

    bool operator<(const Combination& other)
    {
        //huge confuse
        return other.sum > this->sum;
    }
};

void calculateArrays(const std::vector<int> initialNumbers);
void addRec(std::vector<int> currentValues, const std::vector<int>* initialValues, std::vector<Combination>* combinations);

int main(int argc, char* argv[])
{

    auto start = std::chrono::system_clock::now();

    calculateArrays({ 543, 504, 418, 376, 206, 138, 528, 504, 440, 363, 213, 129 });


    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    std::cin.get();
    return 0;
}

void calculateArrays(const std::vector<int> initialNumbers)
{
    std::vector<Combination> combinations;

    if (initialNumbers.empty())
        exit(-4);

    int halfsum = 0;
    for (int num : initialNumbers)
    {
        halfsum += num;
    }

    halfsum /= 2;

    printf("Size: %d Goal: %d\n", initialNumbers.size(), halfsum);

    for (int i = 0; i < initialNumbers.size(); i++)
    {
        std::vector<int> currentNumbers({ i });
        combinations.push_back(Combination(currentNumbers, initialNumbers[i]));

        addRec(currentNumbers, &initialNumbers, &combinations);
    }

    std::sort(combinations.begin(), combinations.end());

    int winner = -1;
    for (int i = 0; i < combinations.size() && winner == -1; i++)
    {
        if (combinations[i].sum >= halfsum)
            winner = i;
    }

    if (combinations[winner].sum != halfsum)
    {
        int prevSum = combinations[winner - 1].sum;
        int sum = combinations[winner].sum;

        if (abs(prevSum - halfsum) < abs(sum - halfsum))
            winner--;
    }

    //create the arrays
    std::vector<int> arr1;
    std::vector<int> arr2;
    arr1 = combinations[winner].values;

    int readPos = 0;
    for (int i = 0; i < initialNumbers.size(); i++)
    {
        if (arr1[readPos] == i)
        {
            readPos++;
        }
        else
            arr2.push_back(i);
    }

    printf("Possibilities: %d\n", combinations.size());

    int sum = 0;
    for (int val : arr1)
    {
        printf("%d ", initialNumbers[val]);
        sum += initialNumbers[val];
    }

    printf(" sum: %d\n", sum);

    sum = 0;
    for (int val : arr2)
    {
        printf("%d ", initialNumbers[val]);
        sum += initialNumbers[val];
    }

    printf(" sum: %d\n", sum);

}

void addRec(std::vector<int> currentValues, const std::vector<int>* initialValues, std::vector<Combination>* combinations)
{
    for (int i = currentValues.back() + 1; i < initialValues->size(); i++)
    {
        std::vector<int> currentNumbers = currentValues;
        currentNumbers.push_back(i);

        int sum = 0;
        for (int val : currentNumbers)
        {
            sum += initialValues->at(val);
        }

        combinations->push_back(Combination(currentNumbers, sum));

        addRec(currentNumbers, initialValues, combinations);
    }

}