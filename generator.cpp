#include "generator.hpp"

long long comb(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    long long result = 1;
    for (int i = 0; i < k; i++) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

// Округление до красивых чисел
double roundNice(double x) {
    if (x < 1)   return round(x * 10) / 10.0;
    if (x < 10)  return round(x * 2) / 2.0;
    if (x < 100) return round(x);
    return round(x / 5.0) * 5.0;
}

vector<double> create_multipliers(int rows, std::string risk, double rtp = 0.97) {
    int bins = rows + 1;

    double riskPower, compress, min_mult;

    if (risk == "low") {
        riskPower = 0.5;
        compress  = 0.85;
        min_mult  = 0.3;
    } else if (risk == "medium") {
        riskPower = 1.0;
        compress  = 0.70;
        min_mult  = 0.2;
    } else {
        riskPower = 2.0;
        compress  = 0.55;
        min_mult  = 0.1;
    }

    std::vector<double> probs(bins);
    std::vector<double> raw(bins);

    for (int k = 0; k < bins; k++) {
        probs[k] = comb(rows, k) * std::pow(0.5, rows);
        raw[k]   = std::pow(1.0 / probs[k], riskPower);
    }

    // Геометрическое среднее - для компрессии
    double logSum = 0.0;
    for (int k = 0; k < bins; k++)
        logSum += std::log(raw[k]);
    double geoMean = std::exp(logSum / bins);

    // Степенная компрессия: уменьшает разброс между мин и макс
    // compress=1.0 - исходный raw, compress=0.0 - все значения равны geoMean
    std::vector<double> compressed(bins);
    for (int k = 0; k < bins; k++)
        compressed[k] = geoMean * std::pow(raw[k] / geoMean, compress);

    // Floor: центральные ячейки не падают ниже min_mult * geoMean
    double floor_val = geoMean * min_mult;
    for (int k = 0; k < bins; k++)
        compressed[k] = std::max(compressed[k], floor_val);

    // Нормализация — точный RTP
    double expected = 0.0;
    for (int k = 0; k < bins; k++)
        expected += probs[k] * compressed[k];

    std::vector<double> multipliers(bins);
    for (int k = 0; k < bins; k++)
        multipliers[k] = compressed[k] * rtp / expected;

    // Симметрия
    for (int k = 0; k < bins / 2; k++) {
        double avg = (multipliers[k] + multipliers[rows - k]) / 2.0;
        multipliers[k] = multipliers[rows - k] = avg;
    }

    // Округление после всего
    for (auto& m : multipliers)
        m = roundNice(m);

    return multipliers;
}

vector<unique_ptr<WinBox>> create_win_boxes(int rows, std::string risk){
    vector<unique_ptr<WinBox>> win_boxes;
    int g;
    int r;
    int b;
    if (risk == "low"){
        r = 0;
        b = 220;
    }  else if (risk == "medium"){
        r = 165;
        b = 238;
    } else if (risk == "high"){
        r = 220;
        b = 0;
    }
    int box_count = rows+1;
    double y = HEIGHT/2 + (rows*(pegSpacing+1))/2-pegSpacing + sCircleR;
    double startX = WIDTH*2/3 - (box_count*pegSpacing)/2;
    vector<double> multi = create_multipliers(rows, risk);
    for (int i = 0; i < box_count; i++){
        g = 50 + (abs(box_count/2-i))/(double)box_count*205;
        win_boxes.push_back(std::move(make_unique<WinBox>(Point{startX + i*pegSpacing, y}, multi[i], al_map_rgb(r, g, b))));
    }
    return win_boxes;
}

vector<unique_ptr<Circle>> create_field(int rows){
    vector<unique_ptr<Circle>> field;
    int peg_count;
    int start_y = HEIGHT/2 - (rows*(pegSpacing+1))/2;
    int start_x;
    for (int i = 0; i <rows; i++){
        peg_count = 3+i;
        start_x = WIDTH*2/3 - ((peg_count-1)*(pegSpacing))/2;
        for (int y = 0; y < peg_count; y++){
            field.push_back(std::move(make_unique<Circle>(sCircleR, Point{start_x + y*pegSpacing, start_y + i*(pegSpacing+1)}, 0)));
        };
    };
    return field;
}