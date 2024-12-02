#include "Pipeline.hpp"
#include "Logger.hpp"

Pipeline::Pipeline() = default;

Pipeline::~Pipeline() {
    stop();
}

void Pipeline::addTask(std::function<std::string()> task) {
    auto stage = std::make_shared<ActiveObject>();
    stage->enqueue(task);
    log("[Pipeline] Task added to stage.");

    if (!stages.empty()) {
        stages.back()->setNextStage(stage.get());
        log("[Pipeline] Set next stage for the previous stage.");
    }

    stages.push_back(stage);
    log("[Pipeline] New stage added. Total stages: " + std::to_string(stages.size()));
}

void Pipeline::start() {
    log("[Pipeline] Starting all stages...");
    for (auto& stage : stages) {
        stage->start();
        log("[Pipeline] Stage started.");
    }
}

std::string Pipeline::execute() {
    std::string sharedData;

    if (!stages.empty()) {
        log("[Pipeline] Executing pipeline...");

        // Première étape
        stages.front()->enqueue([&sharedData]() -> std::string {
            log("[Pipeline] First stage processing.");
            return sharedData;
        });

        // Dernière étape
        stages.back()->enqueue([&sharedData]() -> std::string {
            log("[Pipeline] Final stage processing.");
            return sharedData;
        });
    } else {
        log("[Pipeline] No stages to execute.");
    }

    return sharedData;
}

void Pipeline::stop() {
    log("[Pipeline] Stopping all stages...");
    for (auto& stage : stages) {
        stage->stop();
        log("[Pipeline] Stage stopped.");
    }
}