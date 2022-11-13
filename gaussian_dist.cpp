#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define MAX_GEN_CAP 500

std::array<int, MAX_GEN_CAP> nums = { 0 };

#define ASSERT(x) do { \
                        if (!(x)) { \
                            std::cout << "[ERROR]\n"; \
                            exit(1); \
                        } \
                    } while(0)

void print_arr_info(int* arr, size_t size)
{
    int sum = 0;
    int ssum = 0;
    std::cout << "[";
    for (size_t i = 0; i < size; i++) {
        std::cout << arr[i] << ", ";
        sum += arr[i];
        ssum += (arr[i] * arr[i]);
    }
    std::cout << "]\n";
    float mean = sum / (float)size;
    std::cout << "[Mean]" << mean << '\n'
              << "[Sd]" << sqrtf(ssum / (float)size - mean*mean);

}

int pick_random_normal_dst(float mean, int x, int y) 
{
    int a = rand()%y - x / (y - x);
    return a;
}

void gen_samples(int *buffer, int samples, float mean, float sd, int max_titer = 100)
{
    ASSERT(sd >= 0.0f);

    std::cout << "Generating "
              << samples 
              << " samples whith mean "
              << mean 
              << " and standard deviation "
              << sd << "\n";

    float curr_sd = 0;

    for (int i = 0; i <= samples; i += 2) {
        buffer[i] = pick_random_normal_dst(mean, mean-sd, mean+sd);
        if (buffer[i] > mean)
            buffer[i+1] = mean - (buffer[i] - mean);
        else { 
            buffer[i+1] = (mean - buffer[i]) + mean; 
        }
        for (int k = 0; k < max_titer; k++) {
            curr_sd = 0.0f;

            for (int j = 0; j < i + 1; j++) {
                float dx = buffer[j] - mean;
                curr_sd += dx * dx;
            }
            curr_sd += (buffer[i + 1] - mean)*(buffer[i + 1] - mean);
            curr_sd /= samples;
            curr_sd = sqrtf(curr_sd);

            if (curr_sd <= sd - 1.5f) {
                if (buffer[i] >= mean) {
                    buffer[i] += 1;
                    buffer[i + 1] -= 1;
                } else {
                    buffer[i] -= 1;
                    buffer[i + 1] += 1;
                }
            } else if (curr_sd > sd + 1.5f){
                if (buffer[i] >= mean) {
                    buffer[i] -= 1;
                    buffer[i + 1] += 1;
                }
                else {
                    buffer[i] += 1;
                    buffer[i + 1] -= 1;
                }
            } else {
                break;
            }
        }
    }
}

int main()
{
    int samples = 250;
    gen_samples(nums.data(), samples, 69.5f, 58.0f);
    print_arr_info(nums.data(), samples);
    
    return 0;
}
