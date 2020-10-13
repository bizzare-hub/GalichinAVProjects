#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

class DecisiveStump {
private:
    int n_;
    int left_sum, right_sum;
    int left_square_sum, right_square_sum;
    int left_cnt, right_cnt;
    std::vector<std::pair<int, int>> values;
public:
    DecisiveStump(int n) : n_(n), left_cnt(0), right_cnt(0), left_sum(0),
                           right_sum(0), left_square_sum(0), right_square_sum(0) {
        for (int i = 0; i < n_; ++i) {
            int cur_x, cur_y;
            std::cin >> cur_x >> cur_y;

            values.emplace_back(std::make_pair(cur_x, cur_y));

            right_sum += values[i].second;
            right_square_sum += values[i].second * values[i].second;
            right_cnt += 1;
        }

        std::sort(values.begin(), values.end(), [](std::pair<int, int> lfs, std::pair<int, int> rhs) {
            return lfs.first < rhs.first;
        });
    }

    double count_a() const { return (left_cnt == 0) ? 0 : (1. / left_cnt) * left_sum; }
    double count_b() const { return (right_cnt == 0) ? 0 : (1. / right_cnt) * right_sum; }
    double count_c(int i) const { return 0.5 * (values[i].first + values[i + 1].first); }

    void UpdateSum(int i) {
        left_sum = left_sum + values[i].second;
        right_sum = right_sum - values[i].second;

        left_square_sum = left_square_sum + values[i].second * values[i].second;
        right_square_sum = right_square_sum - values[i].second * values[i].second;

        left_cnt += 1;
        right_cnt -= 1;
    }

    double MeanSquaredError() const {
        double left_mse, right_mse;

        left_mse = (left_cnt == 0) ? 0 : left_square_sum - double(left_sum * left_sum) / left_cnt;
        right_mse = (right_cnt == 0) ? 0 : right_square_sum - double(right_sum * right_sum) / right_cnt;

        return std::sqrt( (1. / n_) * (left_mse + right_mse) );
    }
};

int main() {

    int n;
    std::cin >> n;

    double a, b, c;
    double mse;
    DecisiveStump ds(n);

    for (int i = 0; i <= n - 1; ++i) {

        ds.UpdateSum(i);

        if ((i == 0) || (mse > ds.MeanSquaredError())) {
            mse = ds.MeanSquaredError();

            a = ds.count_a();
            b = ds.count_b();
            c = ds.count_c(i);
        }
    }

    std::cout << a << " " << b << " " << c << std::endl;

    return 0;
}
