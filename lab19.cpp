#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
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

    ~Movie() {
        clearReviews();
    }

    void addReview(const string& comment) {
        double rating = (rand() % 41 + 10) / 10.0; // random 1.0–5.0
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

        if (total > 0) cout << "    > Average: " << (sum / total) << endl;
        else cout << "    > No reviews.\n";
        cout << endl;
    }

    void clearReviews() {
        Review* current = head;
        while (current) {
            Review* tmp = current;
            current = current->next;
            delete tmp;
        }
        head = nullptr;
    }
};

int main() {
    srand(time(0));

    ifstream infile("reviews.txt");
    if (!infile) {
        cerr << "Could not open reviews.txt\n";
        return 1;
    }

    vector<string> comments;
    string line;
    while (getline(infile, line)) {
        if (!line.empty()) comments.push_back(line);
    }
    infile.close();

    Movie m1("Inception");
    for (int i = 0; i < 3; i++) {
        string cmt = comments[rand() % comments.size()];
        m1.addReview(cmt);
    }

    m1.printReviews();
    return 0;
}
