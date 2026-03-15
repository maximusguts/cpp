#include <iostream>

using namespace std;

class Plane
{
    private:
        int f_t_c_Liters;
        int f_c_Lt_Km;
        int l_w_Kg;
        float routeAB;
        float routeBC;

    public:
        Plane(int fuel_tank_capacity_Liters, int load_weight_Kg, float RouteAB, float RouteBC)
        {
            routeAB = RouteAB;
            routeBC = RouteBC;

            f_t_c_Liters = fuel_tank_capacity_Liters;

            if (load_weight_Kg < 0)
            {
                load_weight_Kg = 0;
            }

            l_w_Kg = load_weight_Kg;

            if (l_w_Kg < 500 && l_w_Kg > -1)
            {
                f_c_Lt_Km = 1;
            }
            else if (l_w_Kg < 1000)
            {
                f_c_Lt_Km = 4;
            }
            else if (l_w_Kg < 1500)
            {
                f_c_Lt_Km = 7;
            }
            else if (l_w_Kg < 2000)
            {
                f_c_Lt_Km = 9;
            }
            else if (l_w_Kg >= 2000)
            {
                f_c_Lt_Km = 0;
            }
        }

        void make_info()
        {
            float tAB_f_Lt = float(f_c_Lt_Km) * routeAB;
            float rAB_f_Lt = f_t_c_Liters - tAB_f_Lt;

            float tBC_f_Lt = float(f_c_Lt_Km) * routeBC;
            
            if (f_c_Lt_Km == 0)
            {
                cout << "You'r load weight (in Kilograms) is: " << l_w_Kg << ".That's a lot, and you will not fly.";
            }
            
            else if (tBC_f_Lt - rAB_f_Lt <= 0)
            {
                cout << "You'r load weight (in Kilograms) is: " << l_w_Kg << ". Therefore, the fuel consumption is: " << f_c_Lt_Km;
                cout << ". So, if you fill plane to " << f_t_c_Liters << " liters (full fuel tank capacity) you will fly, and spend " << tAB_f_Lt << " liters flom post A to B.";
                cout << " And when will you arrive to post B, you don't needed to fill you'r plane 1 more time,";
                cout << " because on a route BC you need a " << tBC_f_Lt << " liters in total, and " << rAB_f_Lt << " you already have,";
                cout << " so you can just fill plane only once";
            }
            
            else
            {
                cout << "You'r load weight (in Kilograms) is: " << l_w_Kg << ". Therefore, the fuel consumption is: " << f_c_Lt_Km;
                cout << ". So, if you fill plane to " << f_t_c_Liters << " liters (full fuel tank capacity) you will fly, and spend " << tAB_f_Lt << " liters flom post A to B.";
                cout << " And when will you arrive to post B, you needed to fill you'r plane 1 more time to: ";
                cout << tBC_f_Lt - rAB_f_Lt << " liters, because on a route BC you need a " << tBC_f_Lt << " liters in total, and " << rAB_f_Lt << " you already have, so ";
                cout << tBC_f_Lt - rAB_f_Lt << " liters this's a corect ansewer.";   
            }
        }
};

int main()
{
    int load_weight_Kg;
    float r_AB, r_BC;

    cout << "enter fuel capacity in liters - ";
    cin >> load_weight_Kg;
    
    cout << "\nenter length of route AB and BC - ";
    cin >> r_AB >> r_BC;

    Plane myPlane(300, load_weight_Kg, r_AB, r_BC);

    myPlane.make_info();

    return 0;
}