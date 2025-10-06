#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Review {
    double rating;
    string comment;
    Review* next;
};

class Movie {
private:
    string title;
    Review* head;

public:
    Movie(const string& t) : title(t), head(nullptr) {}

    void addReview(double rating, const string& comment) {
        Review* newReview = new Review{rating, comment, head};
        head = newReview;
    }

    void printReviews() const {
        cout << "Movie: " << title << endl;
        Review* current = head;
        int count = 1;
        double sum = 0;
        int total = 0;

        while (current) {
            cout << "    > Review #" << count++ << ": "
                 << fixed << setprecision(1) << current->rating
                 << " : " << current->comment << endl;
            sum += current->rating;
            total++;
            current = current->next;
        }

        if (total > 0) {
            cout << "    > Average: " << (sum / total) << endl;
        } else {
            cout << "    > No reviews.\n";
        }
        cout << endl;
    }
};

int main() {
    Movie m1("Inception");
    m1.addReview(4.5, "Great visuals");
    m1.addReview(3.8, "Solid story");
    m1.addReview(5.0, "Masterpiece");
    m1.printReviews();
    return 0;
}
