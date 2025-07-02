#include <filesystem>
#include <fstream>
#include <opencv2/videoio.hpp>
#include <spdlog/spdlog.h>

#include "Hyperwall.hpp"
#include "Sources/FileSource.hpp"
#include "Utils.hpp"
#include "Web/Server.hpp"

using namespace asck;

std::vector<std::thread> threads;
bool running;

std::string layout(std::string input) {
    std::string style = R"(
        <style>
            html {
                font-family: sans-serif;
            }
            body {
                margin-left: 5%;
                margin-right: 5%;
                text-align: center;
            }
            form {
                text-align: right;
            }
            section {
                text-align: center;
                width: 400px;
                display: inline-flex;
            }
            footer {
                position: fixed;
                bottom: 0;
                left: 0;
                width: 100%;
            }
        </style>
    )";
    return std::format(
        R"(
        <!DOCTYPE html>
        <html>
        {}
        <head>
            <title>Hyperwall</title>
            <link rel="icon" type="image/png" href="https://avatars.githubusercontent.com/u/126147587?s200&amp;v=4">
     
        </head>
        <body>
            <img style="position:fixed; left: 6%; top: 1%;" src="https://avatars.githubusercontent.com/u/126147587?s=200&amp;v=4" width="100" height="100">
            <h1>Hyperwall</h1>
            <br><br>
            <hr>
            {}
        </body>
        <footer>
            Available on <a href="https://github.com/aalborg-supercomputer-klubben/hyperwall">Github</a> | Created By: <a href="https://skade.dev">Mast3r_waf1z</a>
        </footer>
        </html>
    )", style, input);
}

int main(int argc, char* argv[]) {
    Web::Server server;

    server.add("/", layout(R"(
        <section>
            <form id="videoUploadForm" method="POST" enctype="multipart/form-data" action="/run">
                <label for="videoFile">Choose a video file: </label>
                <input type="file" id="videoFile" name="videoFile" accept="video/*" required>
                <br><br>
                <label for="dimensions">dimensions: </label>
                <input type="text" id="dimensions" name="dimensions" placeholder="2x2">
                <br><br>
                <label for="resolution">resolution: </label>
                <input type="text" id="resolution" name="resolution" placeholder="1920x1080">
                <br><br>
                <button type="submit">Run</button>
            </form>
        </section>
    )"));
    
    server.Post("/run", [](httplib::Request request, httplib::Response& response){
        if(!request.has_file("videoFile")) {
            response.status = 400;
            response.set_content("No file uploaded.", "text/plain");
            return;
        }
        std::tuple<int, int> dimensions, resolution;
        if(request.has_file("dimensions") && request.get_file_value("dimensions").content.contains("x")) {
            auto dim = request.get_file_value("dimensions");
            dimensions = splitResolution(dim.content);
        }
        else {
            spdlog::warn("No dim provided");
            dimensions = {2, 2};
        }
        if (request.has_file("resolution") && request.get_file_value("resolution").content.contains("x")) {
            auto res = request.get_file_value("resolution");
            resolution = splitResolution(res.content);
        }
        else {
            spdlog::warn("No res provided");
            resolution = {1920, 1080};
        }


        const auto& file = request.get_file_value("videoFile");
        spdlog::info("Got file: {}", file.filename);

        if (running) {
            response.status = 400;
            response.set_content("Failed, hyperwall is already running", "text/plain");
            return;
        }
        auto filename = std::format("./tmp/{}", file.filename);

        std::ofstream ofs("./tmp/" + file.filename, std::ios::binary);
        if (ofs) {
            ofs.write(file.content.data(), file.content.size());
            ofs.close();
            ofs.flush();
        }

        threads.push_back(std::thread{[&filename, dimensions, resolution](){
            running = true;
            FileSource source(filename);
            Settings settings(
                resolution
            );
            Hyperwall hyperwall(source, settings);
            hyperwall.run();
            std::filesystem::remove(filename);
            running = false;
        }});

        response.set_content(layout(R"(
            Successfully uploaded video!<br>
            <a href="/">Go back</a>
        )"), "text/html");
    });

    server.run("0.0.0.0", 8000);
}
