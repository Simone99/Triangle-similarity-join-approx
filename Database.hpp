#ifndef __DATABASE__
#define __DATABASE__

#include <unordered_map>
#include <vector>
#include <ostream>
#include <istream>
#include <cmath>

#define N_MAX_RECORDS 100
#define MAX_RECORD_VALUE 10.0
#define N_DIMENSIONS 2
#define GEO false // Used to process longitude and latitude coordinates

struct Point{
    std::vector<float> coordinates;

    float euclidean_distance_from(const Point& other) const{
        if(!GEO){
            float total_sum = 0.0;
            for(long unsigned int i = 0; i < this->coordinates.size(); i++){
                total_sum += pow((this->coordinates[i] - other.coordinates[i]), 2);
            }
            return sqrt(total_sum);
        }else{
            float lat1 = this->coordinates[0] * M_PI / 180;
            float lat2 = other.coordinates[0] * M_PI / 180;
            float long1 = this->coordinates[1] * M_PI / 180;
            float long2 = other.coordinates[1] * M_PI / 180;
            return 2 * 6371 * asin(sqrt(pow(sin((lat2 - lat1)/2), 2) + cos(lat1) * cos(lat2) * pow(sin((long2 - long1) / 2), 2)));
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& obj){
        long unsigned int i = 0;
        os << "(";
        for(i = 0; i < obj.coordinates.size() - 1; i++){
            os << obj.coordinates[i] << ", ";
        }
        os << obj.coordinates[i] << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Point& obj){
        float tmp = 0;
        char tmp_char;
        is >> tmp_char;
        while(is){
            is >> tmp;
            obj.coordinates.emplace_back(tmp);
            is >> tmp_char;
            if(tmp_char == ')')
                break;
        }
        return is;
    }

    friend bool operator==(const Point& l, const Point& r)
    {
        return std::tie(l.coordinates) == std::tie(r.coordinates); // keep the same order
    }

    friend bool operator!=(const Point& l, const Point& r)
    {
        return !(l == r); // keep the same order
    }
};

class Database{

    private:

        std::unordered_map<int, std::vector<Point>> data; // The key is the point color
        Database();

    public:

        Database(const int n_sets, const int d);
        const std::unordered_map<int, std::vector<Point>>& getData() const;
        friend std::ostream& operator<<(std::ostream& os, const Database& obj);
        std::vector<Database> split_points(int percentage);
        Point generate_random_point(int d);

};

#endif

