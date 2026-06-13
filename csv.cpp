#include "csv.h"
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;
void saveCSV(const string& filename,const vector<Measurement>& results)
{
    ofstream file(filename);
    if(!file.is_open())
        return;
    file << "Time," << "LeftAngle," << "RightAngle," << "AverageAngle," << "HasContact" << "\n";
    for(const auto& m : results)
    {
        file << fixed << setprecision(6);
        file << m.time << ",";
        if(m.hasContact)
            file << m.leftAngle << "," << m.rightAngle << "," << m.averageAngle;
        else
            file << "NAN," << "NAN," << "NAN";
        file << "," << m.hasContact << "\n";
    }
    file.close();
}