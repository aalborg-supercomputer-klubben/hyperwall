#include <opencv2/videoio.hpp>
#include <spdlog/spdlog.h>

#include "Hyperwall.hpp"
#include "Sources/FileSource.hpp"
#include "Web/Server.hpp"

std::thread thread;
bool running = false;

int main(int argc, char* argv[]) {
    Web::Server server;

    server.add("/", R"(
        <!DOCTYPE html>
        <html>
            <style>
                body {
                    text-align: center;
                }
            </style>
            <body>
                <img src="https://avatars.githubusercontent.com/u/126147587?s=200&amp;v=4" width="100" height="100">
                <h1>Hyperwall Upload</h1><br>
                Available on <a href="https://github.com/aalborg-supercomputer-klubben/hyperwall">Github</a>

                <hr>
                <form id="videoUploadForm" method="POST" enctype="multipart/form-data" action="/run">
                    <label for="videoFile">Choose a video file:</label>
                    <input type="file" id="videoFile" name="videoFile" accept="video/*" required>
                    <br><br>
                    <button type="submit">Run</button>
                </form>
            </body>
        </html>
    )");
    server.Post("/run", [](httplib::Request request, httplib::Response& response){
        if(!request.has_file("videoFile")) {
            response.status = 400;
            response.set_content("No file uploaded.", "text/plain");
            return;
        }
        const auto& file = request.get_file_value("videoFile");
        spdlog::info("Got file: {}", file.filename);
        
        if (running) {
            response.status = 400;
            response.set_content("Failed, hyperwall is already running", "text/plain");
            return;
        }
        Hyperwall::FileSource source(file.content);
        Hyperwall::Settings settings;
        Hyperwall::Hyperwall hyperwall(source, settings);
        std::thread thread([&hyperwall](){
            running = true;
            hyperwall.run();
            running = false;
        });

        response.set_content(R"(
            <!DOCTYPE html>
            <html>
                <style>
                    body {
                        text-align: center;
                    }
                </style>
                <body>
                    <img src="https://avatars.githubusercontent.com/u/126147587?s=200&amp;v=4" width="100" height="100">
                    <h1>Hyperwall Upload</h1><br>
                    Available on <a href="https://github.com/aalborg-supercomputer-klubben/hyperwall">Github</a>
                    <hr>
                    Successfully uploaded video!<br>
                    <a href="/">Go back</a>
                </body>
            </html>
        )", "text/html");
    });
    server.run("0.0.0.0", 8000);
}
