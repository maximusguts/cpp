#include <iostream>
#include <string>
using namespace std;

class Website {
    private:
        string url;
        int visitors;
    public:
        // Getter for url
        string getUrl() const {
            return url;
        }

        // Setter for url
        void setUrl(string newUrl) {
            if (newUrl.rfind("www", 0) == 0) {  // checking, if url starts with - "www"
                url = newUrl;
            } else {
                cout << "Error: URL must to have \"www\" in the start" << endl;
            }
        }

        // Getter for visitors
        int getVisitors() const {
            return visitors;
        }

        // Setter for visitors
        void setVisitors(int newVisitors) {
            if (newVisitors >= 0) {
                visitors = newVisitors;
            } else {
                cout << "Invalid number of visitors!" << endl;
            }
        }

        void displayInfo() const {
            cout << "Website URL: " << url << ", Visitors: " << visitors << endl;
        }
};

int main() {
    Website site;
    site.setUrl("www.example.com");    // normal
    cout << site.getUrl() << endl;

    site.setUrl("http://example.com"); // error
    cout << site.getUrl() << endl << endl;

    site.setVisitors(1500);            // normal
    cout << site.getVisitors() << endl;

    site.setVisitors(-300);            // error
    cout << site.getVisitors() << endl;

    site.displayInfo();

    return 0;
}
