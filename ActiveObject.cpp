#include "ActiveObject.hpp"
#include <iostream>
#include "Logger.hpp"

ActiveObject::ActiveObject() : running(false), nextStage(nullptr) {
    log("[ActiveObject] Created.");
}

ActiveObject::~ActiveObject() {
    stop();
}

void ActiveObject::start() {
    log("[ActiveObject] Starting worker thread.");
    running = true;
    workerThread = std::thread([this]() {
        while (running) {
            std::function<std::string()> task;
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [this] { return !tasks.empty() || !running; });
                if (!running && tasks.empty()) break;

                task = std::move(tasks.front());
                tasks.pop();
                log("[ActiveObject] Task dequeued.");
            }
            if (task) {
                std::string result = task();
                log("[ActiveObject] Task executed. Result: " + result);
                if (nextStage) {
                    nextStage->enqueue([result]() -> std::string {
                        log("[ActiveObject] Passing result to next stage.");
                        return result;
                    });
                }
            }
        }
    });
}

void ActiveObject::stop() {
    log("[ActiveObject] Stopping worker thread.");
    {
        std::lock_guard<std::mutex> lock(mtx);
        running = false;
    }
    cv.notify_all();
    if (workerThread.joinable()) {
        workerThread.join();
        log("[ActiveObject] Worker thread stopped.");
    }
}

void ActiveObject::enqueue(std::function<std::string()> task) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        tasks.push(std::move(task));
        log("[ActiveObject] Task enqueued.");
    }
    cv.notify_one();
}

void ActiveObject::setNextStage(ActiveObject* next) {
    nextStage = next;
}