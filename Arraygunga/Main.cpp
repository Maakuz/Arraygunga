#include <iostream>
#include <Windows.h>
#include <chrono>
#include <ctime>
#include <vector>
#include <algorithm>



struct Combination
{
    std::vector<int> left;
    std::vector<int> right;
    int leftSum;
    int rightSum;

    Combination(std::vector<int> left, std::vector<int> right, int leftSum, int rightSum)
    {
        this->left = left;
        this->right = right;
        this->leftSum = leftSum;
        this->rightSum = rightSum;
    }

    int dif() const
    {
        return abs(this->leftSum - this->rightSum);
    }

    bool operator<(const Combination& other)
    {
        return this->dif() < other.dif();
    }
};

void calculateArrays(const std::vector<int> initialNumbers);
void addRec(std::vector<int> currentValues, const std::vector<int>* initialValues, std::vector<Combination>* combinations);
int sumIndexed(const std::vector<int>* initialValues, const std::vector<int>* positions);
int sumValues(const std::vector<int>* values);
void fillInverseVector(std::vector<int>* inverse, const std::vector<int>* initialValues, const std::vector<int>* positionsToInvert);

int main(int argc, char* argv[])
{

    auto start = std::chrono::system_clock::now();

    calculateArrays({ 543, 504, 418, 376, 206, 138, 528, 504, 440, 363, 213, 128 });


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

    int halfsum = sumValues(&initialNumbers) / 2;

    printf("Size: %d Goal: %d\n", initialNumbers.size(), halfsum);

    for (int i = 0; i < initialNumbers.size(); i++)
    {
        std::vector<int> currentNumbers({ i });
        std::vector<int> currentNumbers2;
        fillInverseVector(&currentNumbers2, &initialNumbers, &currentNumbers);

        int sum = sumIndexed(&initialNumbers, &currentNumbers2);

        combinations.push_back(Combination(currentNumbers, currentNumbers2, initialNumbers[i], sum));

        addRec(currentNumbers, &initialNumbers, &combinations);
    }

    std::sort(combinations.begin(), combinations.end());

    printf("Possibilities: %d\n", combinations.size());

    int sum = 0;
    for (int val : combinations.front().left)
    {
        printf("%d ", initialNumbers[val]);
        sum += initialNumbers[val];
    }

    printf(" sum: %d\n", sum);

    sum = 0;
    for (int val : combinations.front().right)
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
        std::vector<int> currentNumbersInv;
        currentNumbers.push_back(i);

        int sum = sumIndexed(initialValues, &currentNumbers);

        fillInverseVector(&currentNumbersInv, initialValues, &currentNumbers);
        int invSum = sumIndexed(initialValues, &currentNumbersInv);

        combinations->push_back(Combination(currentNumbers, currentNumbersInv, sum, invSum));

        addRec(currentNumbers, initialValues, combinations);
    }

}

void fillInverseVector(std::vector<int>* inverse, const std::vector<int>* initialValues, const std::vector<int>* positionsToInvert)
{
    int readPos = 0;
    for (int i = 0; i < initialValues->size(); i++)
    {
        if (readPos < positionsToInvert->size() && positionsToInvert->at(readPos) == i)
        {
            readPos++;
        }
        else
            inverse->push_back(i);
    }
}



int sumIndexed(const std::vector<int>* initialValues, const std::vector<int>* positions)
{
    int sum = 0;
    for (int num : *positions)
    {
        sum += initialValues->at(num);
    }

    return sum;
}

int sumValues(const std::vector<int>* values)
{
    int sum = 0;
    for (int num : *values)
    {
        sum += num;
    }

    return sum;
}

