// Credits: https://www.kaggle.com/oxzplvifi
// Source: https://www.kaggle.com/oxzplvifi/indoor-cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
    string inpath = argv[1];
    string pathid = inpath.substr(inpath.find_last_of("/") + 1);
    pathid = pathid.substr(0, pathid.find_last_of("."));
    string tmppath = "tmp.txt";
    string outpath = argv[2];
    outpath += "/";
    outpath += argv[3];
    outpath += ".txt";
    int floor = stoi(argv[4]);
    ifstream in1;
    ofstream out1;
    string line, word, value, time, type;
    vector<string> vline;
    vector<string> types = {"TYPE_ACCELEROMETER", "TYPE_ACCELEROMETER_UNCALIBRATED",
                            "TYPE_GYROSCOPE", "TYPE_GYROSCOPE_UNCALIBRATED",
                            "TYPE_MAGNETIC_FIELD", "TYPE_MAGNETIC_FIELD_UNCALIBRATED",
                            "TYPE_ROTATION_VECTOR", "TYPE_WIFI", "TYPE_BEACON", "TYPE_WAYPOINT"};
    // I. Fix missing endline character:
    in1.open(inpath);
    out1.open(tmppath);
    getline(in1, line);
    string istest = argv[2];
    istest = istest.substr(istest.find_last_of("/") + 1);
    if (istest == "test")
    {
        time = "0";
    }
    else
    {
        time = line.substr(line.find("startTime:") + 10);
        time.erase(remove(time.begin(), time.end(), ' '), time.end());
    }
    out1 << time << endl;
    while (getline(in1, line))
    {
        if (line[0] == '#')
            continue;
        stringstream ss(line);
        ss >> time >> type;
        vline.push_back(time);
        vline.push_back(type);
        while (ss >> word)
        {
            if (find(types.begin(), types.end(), word) == types.end())
                vline.push_back(word);
            else
            {
                type = word;
                value = vline.back();
                time = value.substr(value.length() - time.length());
                vline.back() = value.substr(0, value.length() - time.length());
                for (int i{}; i < vline.size(); i++)
                    out1 << vline[i] << '\t';
                out1 << endl;
                vline.clear();
                vline.push_back(time);
                vline.push_back(type);
            }
        }
        for (int i{}; i < vline.size(); i++)
            out1 << vline[i] << '\t';
        out1 << endl;
        vline.clear();
    }
    in1.close();
    out1.close();
    // II. Fix data format:
    in1.open(tmppath);
    out1.open(outpath, ios_base::app);
    string xyz_time, x_acce, y_acce, z_acce, a_acce, x_acce_uncali, y_acce_uncali, z_acce_uncali,
        x2_acce_uncali, y2_acce_uncali, z2_acce_uncali, a_acce_uncali,
        x_gyro, y_gyro, z_gyro, a_gyro, x_gyro_uncali, y_gyro_uncali, z_gyro_uncali,
        x2_gyro_uncali, y2_gyro_uncali, z2_gyro_uncali, a_gyro_uncali,
        x_magn, y_magn, z_magn, a_magn, x_magn_uncali, y_magn_uncali, z_magn_uncali,
        x2_magn_uncali, y2_magn_uncali, z2_magn_uncali, a_magn_uncali,
        x_ahrs, y_ahrs, z_ahrs, a_ahrs,
        t1_wifi, ssid_wifi, bssid_wifi, rssid_wifi, freq_wifi, t2_wifi,
        t1_beac, id_beac, power_beac, rssi_beac, dist_beac, mac_beac, t2_beac,
        t_waypoint, x_waypoint, y_waypoint;
    long int start{};
    getline(in1, line);
    start = stol(line);
    while (getline(in1, line))
    {
        stringstream ss(line);
        while (ss >> word)
            vline.push_back(word);
        //cout<<vline[1]<<'\t'<<vline.size()<<endl;
        if (vline[1] == "TYPE_ACCELEROMETER")
        {
            time = to_string(stol(vline[0]) - start);
            xyz_time += time + " ";
            x_acce += vline[2] + " ";
            y_acce += vline[3] + " ";
            z_acce += vline[4] + " ";
            if (vline.size() == 6)
                a_acce += vline[5] + " ";
        }
        else if (vline[1] == "TYPE_ACCELEROMETER_UNCALIBRATED")
        {
            x_acce_uncali += vline[2] + " ";
            y_acce_uncali += vline[3] + " ";
            z_acce_uncali += vline[4] + " ";
            if (vline.size() == 9)
            {
                x2_acce_uncali += vline[5] + " ";
                y2_acce_uncali += vline[6] + " ";
                z2_acce_uncali += vline[7] + " ";
                a_acce_uncali += vline[8] + " ";
            }
        }
        else if (vline[1] == "TYPE_GYROSCOPE")
        {
            x_gyro += vline[2] + " ";
            y_gyro += vline[3] + " ";
            z_gyro += vline[4] + " ";
            if (vline.size() == 6)
                a_gyro += vline[5] + " ";
        }
        else if (vline[1] == "TYPE_GYROSCOPE_UNCALIBRATED")
        {
            x_gyro_uncali += vline[2] + " ";
            y_gyro_uncali += vline[3] + " ";
            z_gyro_uncali += vline[4] + " ";
            if (vline.size() == 9)
            {
                x2_gyro_uncali += vline[5] + " ";
                y2_gyro_uncali += vline[6] + " ";
                z2_gyro_uncali += vline[7] + " ";
                a_gyro_uncali += vline[8] + " ";
            }
        }
        else if (vline[1] == "TYPE_MAGNETIC_FIELD")
        {
            x_magn += vline[2] + " ";
            y_magn += vline[3] + " ";
            z_magn += vline[4] + " ";
            if (vline.size() == 6)
                a_magn += vline[5] + " ";
        }
        else if (vline[1] == "TYPE_MAGNETIC_FIELD_UNCALIBRATED")
        {
            x_magn_uncali += vline[2] + " ";
            y_magn_uncali += vline[3] + " ";
            z_magn_uncali += vline[4] + " ";
            if (vline.size() == 9)
            {
                x2_magn_uncali += vline[5] + " ";
                y2_magn_uncali += vline[6] + " ";
                z2_magn_uncali += vline[7] + " ";
                a_magn_uncali += vline[8] + " ";
            }
        }
        else if (vline[1] == "TYPE_ROTATION_VECTOR")
        {
            x_ahrs += vline[2] + " ";
            y_ahrs += vline[3] + " ";
            z_ahrs += vline[4] + " ";
            if (vline.size() == 6)
                a_ahrs += vline[5] + " ";
        }
        else if (vline[1] == "TYPE_WIFI")
        {
            time = to_string(stol(vline[0]) - start);
            t1_wifi += time + " ";
            ssid_wifi += vline[2] + " ";
            bssid_wifi += vline[3] + " ";
            rssid_wifi += vline[4] + " ";
            freq_wifi += vline[5] + " ";
            time = to_string(stol(vline[6]) - start);
            t2_wifi += time + " ";
        }
        else if (vline[1] == "TYPE_BEACON")
        {
            time = to_string(stol(vline[0]) - start);
            t1_beac += time + " ";
            id_beac += vline[2] + "_" + vline[3] + "_" + vline[4] + " ";
            power_beac += vline[5] + " ";
            rssi_beac += vline[6] + " ";
            dist_beac += vline[7] + " ";
            mac_beac += vline[8] + " ";
            if (vline.size() == 10)
            {
                time = to_string(stol(vline[9]) - start);
                t2_beac += time + " ";
            }
        }
        else if (vline[1] == "TYPE_WAYPOINT")
        {
            time = to_string(stol(vline[0]) - start);
            t_waypoint += time + " ";
            x_waypoint += vline[2] + " ";
            y_waypoint += vline[3] + " ";
        }
        vline.clear();
    }
    out1 << pathid << ',' << start << ',' << xyz_time << ',' << x_acce << ',' << y_acce << ',' << z_acce << ',' << a_acce << ',' << x_acce_uncali << ',' << y_acce_uncali << ',' << z_acce_uncali << ',' << x2_acce_uncali << ',' << y2_acce_uncali << ',' << z2_acce_uncali << ',' << a_acce_uncali << ',' << x_gyro << ',' << y_gyro << ',' << z_gyro << ',' << a_gyro << ',' << x_gyro_uncali << ',' << y_gyro_uncali << ',' << z_gyro_uncali << ',' << x2_gyro_uncali << ',' << y2_gyro_uncali << ',' << z2_gyro_uncali << ',' << a_gyro_uncali << ',' << x_magn << ',' << y_magn << ',' << z_magn << ',' << a_magn << ',' << x_magn_uncali << ',' << y_magn_uncali << ',' << z_magn_uncali << ',' << x2_magn_uncali << ',' << y2_magn_uncali << ',' << z2_magn_uncali << ',' << a_magn_uncali << ',' << x_ahrs << ',' << y_ahrs << ',' << z_ahrs << ',' << a_ahrs << ',' << t1_wifi << ',' << ssid_wifi << ',' << bssid_wifi << ',' << rssid_wifi << ',' << freq_wifi << ',' << t2_wifi << ',' << t1_beac << ',' << id_beac << ',' << power_beac << ',' << rssi_beac << ',' << dist_beac << ',' << mac_beac << ',' << t2_beac << ',' << t_waypoint << ',' << floor << ',' << x_waypoint << ',' << y_waypoint << endl;
    in1.close();
    out1.close();
    return (0);
}
