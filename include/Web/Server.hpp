#include <httplib.h>
#include <spdlog/spdlog.h>

namespace Web {

class Server {
    httplib::Server server;
    public:

    Server() {
        server.set_logger([](httplib::Request req, httplib::Response res){
            std::stringstream ss;
            ss << "Method: " << req.method << " | ";
            ss << "Path: " << req.path << " | ";
            ss << "Status: " << res.status << " | ";

            switch(((res.status + 50) / 100) * 100) {
                case 100:
                case 300:
                    spdlog::warn(ss.str());
                    break;
                case 200:
                    spdlog::info(ss.str());
                    break;
                case 400:
                case 500:
                    spdlog::error(ss.str());
            }
        });
    }
    void run(std::string host, int port) {
        spdlog::info("Running server: {}:{}", host, port);
        server.listen(host, port);
    }

    void add(std::string path, std::string content) {
        server.Get(path, [content](httplib::Request req, httplib::Response& res) {
            res.set_content(content, "text/html");
        });
    }
    void add_page(std::string path, std::ifstream file) {
        std::stringstream ss;
        ss << file.rdbuf();
        return add(path, ss.str());
    }
    template<typename F>
    void Post (std::string path, F f) {
        server.Post(path, f);
    }
};

}
