#include "record.h"
#include "authenticator.h"
#include <boost/thread/thread.hpp>
#include <fstream>

#ifndef ENABLE_MYSQL
void save_traffic(Authenticator *auth) {
    // Write to csv file every 5 seconds
    while (true) {
        // thread sleep for 5 seconds
        boost::this_thread::sleep_for(boost::chrono::seconds(5));
        std::map<std::string, TrafficRecord> records = auth->get_traffic_records();        

        if (records.empty()) {
            continue;
        }

        std::ofstream ofs("traffic.csv");
        if (ofs.tellp() == 0) {
            ofs << "password,download,upload,time" << std::endl;
        }
        time_t now = time(nullptr);
        for (const auto &record : records) {
            ofs << record.first << ',' << record.second.download << ',' << record.second.upload << ',' << now << std::endl;
        }
        ofs.close();
    }
}
#else
void save_traffic(Authenticator *) {}
#endif // ENABLE_MYSQL